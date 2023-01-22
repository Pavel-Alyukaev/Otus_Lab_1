#ifndef HELLOWORLD_IPV4_H
#define HELLOWORLD_IPV4_H
#include <vector>
#include <bitset>

class ipV4 {

public:
    explicit  ipV4(std::string_view ip);

    unsigned long long operator()() const;

    bool isValid() const;

    int Contains(std::vector<uint8_t> mask) const;

    std::string ToString() const;

    friend const bool operator<(const ipV4& lIp, const ipV4& rIp);
    friend const bool operator==(const ipV4& lIp, const ipV4& rIp);
    friend const bool operator>(const ipV4& lIp, const ipV4& rIp);
private:
    std::vector<uint8_t> m_ip;
     bool m_isValid;
};

inline const bool operator<(const ipV4& lIp, const ipV4& rIp) {
    return lIp() < rIp();
}

inline const bool operator==(const ipV4 &lIp, const ipV4 &rIp) {
    return lIp() == rIp();
}

inline const bool operator>(const ipV4 &lIp, const ipV4 &rIp) {
    return lIp() > rIp();
}


#endif //HELLOWORLD_IPV4_H
