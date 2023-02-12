//
// Created by Apostol on 29.01.2023.
//

#ifndef ALLOCATOR_DOUBLELINKLIST_H
#define ALLOCATOR_DOUBLELINKLIST_H

template<typename T>
struct Node
{
    T Data;
    Node* Next;
    Node* Prev;
    template<typename ...Args>
    Node(Args &&...args) :  Data(std::forward<Args>(args)...),Next(nullptr), Prev(nullptr){}
};

template<typename T, typename Alloc = std::allocator<T>>
class DoubleLinkList {
public:
    DoubleLinkList():m_head(nullptr){}
    DoubleLinkList(const DoubleLinkList &src):m_head(src.m_head){}
    DoubleLinkList(DoubleLinkList &&src):m_head(src.m_head){
        src.m_head= nullptr;
    }
    template <typename A>
    DoubleLinkList(const DoubleLinkList<T,A> &src):m_head(src.m_head){
        Copy(src);
    }

// iterators
    template <typename U>
    struct ListIterator {
        using pointer = const U*;
        using reference = const U&;

        using self = ListIterator<U>;
        Node<T>* node;

        ListIterator() : node(nullptr) {};

        ListIterator(Node<U>* pNode) : node(pNode) {};

        reference operator*() const {
            return node->Data;
        }

        pointer operator->() const {
            return &(node->Data);
        }

        self& operator++() {
            if (node == nullptr) {
                return *this;
            }
            else {
                node = node->Next;
            }
            return *this;
        }

        self& operator--() {
            if (node == nullptr) {
                return *this;
            }
            else {
                node = node->Prev;
            }
            return *this;
        }

        bool operator==(const self& rhs) const {
            return node == rhs.node;
        }

        bool operator!=(const self& rhs) const {
            return node != rhs.node;
        }
    };



    DoubleLinkList::ListIterator<T> begin() const noexcept {
        return ListIterator<T>(m_head);
    }

    DoubleLinkList::ListIterator<T> end() noexcept {
        return ListIterator<T>();
    }

    DoubleLinkList::ListIterator<T> rbegin() const noexcept {
        return ListIterator<T>(m_end);
    }

    DoubleLinkList::ListIterator<T> rend() noexcept {
        return ListIterator<T>();
    }

    template <typename ...Args>
    void push_back(Args &&...args) {
        Node<T> *new_node = m_alloc.allocate(1);
        m_alloc.construct(new_node, std::forward<Args>(args)...);
        if (m_head == nullptr) {
            m_head = new_node;
            m_end = new_node;
        }
        else {
            m_end->Next = new_node;
            new_node->Prev = m_end;
            m_end = new_node;
        }
    }


private:

    template <typename A>
    void Copy(const DoubleLinkList<T, A> &src) {
        Node<T>* curNode = src.cbegin().cbegin();
        while (curNode != nullptr) {
            this->push_back(curNode->Data);
            curNode = curNode->Next;
        }
    }


private:
    Node<T>* m_head;
    Node<T>* m_end;

    using Allocator = typename  Alloc::template rebind< Node<T> >::other;
    Allocator m_alloc;
};


#endif //ALLOCATOR_DOUBLELINKLIST_H
