#include "gtest/gtest.h"
#include <fstream>
#include "SimpleCustomAllocator.h"
#include "DoubleLinkList.h"

TEST(DoubleLinkList, push_back)
{
    DoubleLinkList <int> list_default;
    DoubleLinkList<int, SimpleCustomAllocator<int, 10>> list_custom;
    for (int i = 0; i < 10; ++i) {
        list_default.push_back(i);
        list_custom.push_back(i);
    }

    auto iter = list_default.begin();
    auto iter1 = list_custom.begin();
    for (;iter!= list_default.end() && iter1!= list_custom.end(); ++iter, ++iter1) {
        ASSERT_EQ(iter.node->Data, iter1.node->Data);
    }

}