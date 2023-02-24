#include <iostream>
#include "CustomIpPrint.h"


int main(int, char *[]) {
    Print( int8_t{-1} ); // 255
    Print( int16_t{0} ); // 0.0
    Print( int32_t{2130706433} ); // 127.0.0.1
    Print( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
    Print( std::string{"Hello, World!"} ); // Hello, World!
    Print( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    Print( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
    Print( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
    return 0;
}
