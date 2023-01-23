#include "IpPool.h"
#include "stringTools.h"

IpPool::IpPool(std::istream &&stream) {

    std::string line;
    std::getline(stream, line) ;
    for (; !line.empty() ;)
    {
        std::vector<std::string> v = split(line, '\t');
        m_pool.emplace_back(v.at(0));
        std::getline(stream, line) ;
    }
}

std::vector<std::string> IpPool::GetSortIp() {
    std::sort(m_pool.begin(), m_pool.end(), [](const ipV4& a, const ipV4& b){return a > b;});
    std::vector<std::string> result;
    for (const auto & item: m_pool) {
        if(item.isValid())
            result.emplace_back(item.ToString());
    }
    return result;
}

std::vector<std::string> IpPool::GetFilterIp(std::vector<uint8_t> mask, IpPool::SortFlag flag) {

    auto pred = [&flag, &mask](const ipV4& a){

        auto ds = a.Contains(mask);
        bool result = false;

        if((flag==IpPool::SortFlag::exactMatch && ds == 0) ||
                (flag==IpPool::SortFlag::noExactMatch && ds > -1))
            result = true;

        return result;
    };

    std::vector<ipV4> res;
    std::copy_if(m_pool.begin(), m_pool.end(),std::back_inserter(res),pred);

    std::sort(res.begin(), res.end(), [](const ipV4& a, const ipV4& b){
        return a<b;
    });
    std::vector<std::string> result;
    for (const auto & item: res) {
        if(item.isValid())
            result.emplace_back(item.ToString());
    }
    return result;
}

void IpPool::PrintSortIp(std::ostream &&stream) {

    auto tmp = GetSortIp();
    for (const auto& item: tmp) {
        stream<<item<<std::endl;
    }
}

void IpPool::PrintFilterIp(std::ostream &&stream, std::vector<uint8_t> mask, IpPool::SortFlag flag) {
    auto tmp = GetFilterIp( mask,  flag);
    for (const auto& item: tmp) {
        stream<<item<<std::endl;
    }
}
