#include <iostream>
#include <map>
#include <vector>
#include "SimpleCustomAllocator.h"
#include "DoubleLinkList.h"

unsigned int factorial(int i)
{
    return i == 0 ? 1 : i * factorial(i - 1);
}

template<typename T>
void CustomPrint(std::string header, T& map)
{
    std::cout<<header <<std::endl;

    for (const auto& [key, value] : map){
        std::cout<<key<< " "<< value<<std::endl;
    }
}

template<typename T>
void CustomPrintList(std::string header, T& list)
{
    std::cout<<header <<std::endl;

    for (const auto& value : list){
        std::cout<<value<< " ";
    }
    std::cout<<std::endl;
}

int main(int, char *[]) {
    std::map<int, int> m1;

     std::map<
            const int,
            int,
            std::less<int>,
            SimpleCustomAllocator<
                    std::pair<const int, int>, 10>> m2;

    for (int i = 0; i < 10; ++i) {
        m1.insert(std::pair<const int, int>(i,factorial(i)));
        m2.insert(std::pair<const int, int>(i,factorial(i)));
    }

    CustomPrint("map", m1);
    CustomPrint("map with allocator", m2);


    DoubleLinkList <int> list_default;
    DoubleLinkList<int, SimpleCustomAllocator<int, 10>> list_custom;
    for (int i = 0; i < 10; ++i) {
        list_default.push_back(i);
        list_custom.push_back(i);
    }

    CustomPrintList("List without allocator",list_default);
    CustomPrintList("List with allocator",list_custom);

    return 0;
}
