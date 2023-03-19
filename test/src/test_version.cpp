#include "lib.h"
#include "ipV4.h"
#include "IpPool.h"
#include "gtest/gtest.h"
#include <fstream>


TEST(ipV4, ToString)
{
    std::string data = "100.222.50.1";

    ipV4 ip(data);

    ASSERT_EQ(ip.ToString(), data);
}

TEST(ipV4, isValid)
{
    std::string dataValid = "100.222.50.1";
    std::string dataInValid = "100.555.50.1";

    ipV4 ip1(dataValid);
    ipV4 ip2(dataInValid);

    ASSERT_EQ(ip1.isValid(), true);
    ASSERT_EQ(ip2.isValid(), false);
}

TEST(ipV4, Contains)
{
    std::string data = "100.222.50.1";

    ipV4 ip1(data);

    std::vector<uint8_t> mask1{100};
    std::vector<uint8_t> mask2{100,222};
    std::vector<uint8_t> mask3{222,50};

    ASSERT_EQ(ip1.Contains(mask1), 0);
    ASSERT_EQ(ip1.Contains(mask2), 0);
    ASSERT_EQ(ip1.Contains(mask3), 1);

}

TEST(IpPool, GetSortIp)
{

    IpPool pool(std::move(std::ifstream("ip_filter.tsv")));
    std::vector<std::string> data1 = {
            "1.231.69.33",
            "1.87.203.225",
            "1.70.44.170",
            "1.29.168.152",
            "1.1.234.8"};


    auto result = pool.GetFilterIp({1},IpPool::SortFlag::exactMatch);

    ASSERT_EQ(result, data1);
}

