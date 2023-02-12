#ifndef ALLOCATOR_SIMPLECUSTOMALLOCATOR_H
#define ALLOCATOR_SIMPLECUSTOMALLOCATOR_H

#include "pretty.h"

template<typename T, size_t count>
class SimpleCustomAllocator {
public:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;

    SimpleCustomAllocator() = default;

    ~SimpleCustomAllocator() = default;

    template<typename U>
    SimpleCustomAllocator(const SimpleCustomAllocator<U, count> &) {}

    template<typename U>
    struct rebind {
        using other = SimpleCustomAllocator<U, count>;
    };

    T *allocate(size_t n) {
        if (m_curElement + n > count + 1)
            throw std::bad_alloc();

        if (m_buffPtr == nullptr) {
            std::cout << "Attempt to allocate memory to " << count << " elements" << std::endl;
            m_buffPtr = reinterpret_cast<T*>(std::malloc((count + 1) * sizeof(T)));
            if (m_buffPtr == nullptr)
                throw std::bad_alloc();
            //return m_buffPtr;
        }

        pointer curPtr = m_buffPtr + m_curElement;
        m_curElement += n;
        return curPtr;
    }

    void deallocate(T *p, size_t n) {
        //std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        m_curElement -= n;
        if (p == nullptr || m_curElement != 0 || m_buffPtr == nullptr) {
            return;
        }
        free(m_buffPtr);
        m_buffPtr = nullptr;
        std::cout << "Deallocate all buffer" << std::endl;
    }

    template<typename U, typename... Args>
    void construct(U *p, Args &&...args) {
        new(p) U(std::forward<Args>(args)...);
    };

    template<typename U>
    void destroy(U *p) {
        p->~U();
    }


private:
    size_t m_curElement = 0;
    pointer m_buffPtr = nullptr;

};


#endif //ALLOCATOR_SIMPLECUSTOMALLOCATOR_H
