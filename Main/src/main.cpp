#include "lib.h"
#include <iostream>

#include "ipV4.h"
#include "IpPool.h"


int main (int, char **) {
    try
    {
        IpPool ipPool(std::move(std::cin));

        ipPool.PrintSortIp(std::move(std::cout));

        {
            std::vector<uint8_t> mask{ 1 };
            ipPool.PrintFilterIp(std::move(std::cout), mask, IpPool::SortFlag::exactMatch);
        }
        {
            std::vector<uint8_t> mask{ 46, 70 };
            ipPool.PrintFilterIp(std::move(std::cout), mask, IpPool::SortFlag::exactMatch);
        }
        {
            std::vector<uint8_t> mask{46};
            ipPool.PrintFilterIp(std::move(std::cout), mask, IpPool::SortFlag::noExactMatch);
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
