#include <iostream>
#include <map>
#include <vector>
#include "SimpleCustomAllocator.h"

int main(int, char *[]) {
    auto m = std::map<
            int,
            int,
            std::less<int>,
            SimpleCustomAllocator<
                    std::pair<
                            const int, int>, 10>>{};

    for (int i = 0; i < 10; ++i) {
        m[i] = i;
    }

    return 0;
}
