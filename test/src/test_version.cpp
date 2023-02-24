#include "gtest/gtest.h"
#include "CustomIpPrint.h"

TEST(CustomIpPrint, Print)
{
    std::string buf;
    Print( int8_t{-1} ,buf); // 255
    ASSERT_EQ(buf, "255");
    Print( int16_t{0} , buf); // 0.0
    ASSERT_EQ(buf, "0.0");
    Print( int32_t{2130706433} , buf); // 127.0.0.1
    ASSERT_EQ(buf, "127.0.0.1");
    Print( int64_t{8875824491850138409} , buf);// 123.45.67.89.101.112.131.41
    ASSERT_EQ(buf, "123.45.67.89.101.112.131.41");
    Print( std::string{"Hello, World!"} , buf); // Hello, World!
    ASSERT_EQ(buf, "Hello, World!");
    Print( std::vector<int>{100, 200, 300, 400} , buf); // 100.200.300.400
    ASSERT_EQ(buf, "100.200.300.400");
    Print( std::list<short>{400, 300, 200, 100} , buf); // 400.300.200.100
    ASSERT_EQ(buf, "400.300.200.100");
    Print( std::make_tuple(123, 456, 789, 0) ,buf); // 123.456.789.0
    ASSERT_EQ(buf, "123.456.789.0");
}