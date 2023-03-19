#ifndef HELLOWORLD_IPPOOL_H
#define HELLOWORLD_IPPOOL_H


#include "ipV4.h"

class IpPool {

public:
    enum class SortFlag
    {
        exactMatch,
        noExactMatch
    };

    explicit IpPool(std::istream&& stream);

    std::vector<std::string> GetSortIp();
    std::vector<std::string> GetFilterIp(std::vector<uint8_t>, SortFlag);

    void PrintSortIp(std::ostream &&stream);
    void PrintFilterIp(std::ostream&& stream, std::vector<uint8_t>, SortFlag);

private:
    std::vector<ipV4> m_pool;
};


#endif //HELLOWORLD_IPPOOL_H
