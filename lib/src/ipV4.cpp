#include "ipV4.h"
#include "stringTools.h"

ipV4::ipV4(std::string_view ip):
        m_ip(0),
        m_isValid(true)

{
    auto mainData = split(ip, '.');

    if (mainData.size() != 4)
        m_isValid = false;

    std::size_t pos = 0;
    for (std::string_view item: mainData) {
        int a = std::stoi(item.data(), &pos);
        if (pos != item.length()) {
            m_isValid = false;
            break;
        }
        m_ip.emplace_back(static_cast<uint8_t>(a));
    }
}

unsigned long long ipV4::operator()() const  {

    unsigned long long result = 0;
    unsigned long long coef = static_cast<unsigned long long>(1e9);

    for(const auto& item :m_ip)
    {
        result += item * coef;
        coef /=1000;
    }

    return result;
}

bool ipV4::isValid() const{
    return m_isValid;
}

int ipV4::Contains(std::vector<uint8_t> mask) const {
    int result = -1;

    auto r = std::search(m_ip.begin(), m_ip.end(), std::default_searcher(mask.begin(), mask.end()));

    if(r != m_ip.end())
        result = std::distance(m_ip.begin(),r);

    return result;
}

std::string ipV4::ToString() const {
    std::string result;

    for(const auto& item : m_ip)
    {
        if(!result.empty())
            result+=".";

        result+=std::to_string(item);
    }

    return result;
}
const bool operator<(const ipV4& lIp, const ipV4& rIp) {
    return lIp() < rIp();
}

const bool operator==(const ipV4 &lIp, const ipV4 &rIp) {
    return lIp() == rIp();
}

 const bool operator>(const ipV4 &lIp, const ipV4 &rIp) {
    return lIp() > rIp();
}


