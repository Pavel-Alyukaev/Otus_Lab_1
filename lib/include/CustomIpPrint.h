#include <list>
#include <vector>
#include <tuple>
#include <string>
#include <sstream>


/// \brief function to print custom ip where ip is integral type
/// \tparam T type of ip
/// \param ip custom ip address
/// \param buf ip address output buffer
/// \return
template <typename T>
typename std::enable_if_t<std::is_integral<T>::value> Print(const T& ip, std::string& buf){
    unsigned size = sizeof(T);
    std::stringstream sstr;
    for (int i = size; i > 0; --i)
    {
        sstr<<((ip>>(i-1)*8) & 0xff);
        if(i > 1)
            sstr<< ".";
    }
    buf = sstr.str();
}

/// \brief auxiliary structure for checking whether an argument is a string
/// \tparam T type of ip
template<typename T>
struct is_string : std::false_type {};

/// \brief auxiliary structure for checking whether an argument is a list
template<>
struct is_string<std::string> : std::true_type {};

/// \brief function to print custom ip where ip is string
/// \tparam T type of ip
/// \param ip custom ip address
/// \param buf ip address output buffer
/// \return
template <typename T>
typename std::enable_if_t<is_string<T>::value> Print(const T& ip, std::string& buf){
    buf = ip;
}

/// \brief auxiliary structure for checking whether an argument is a linear container
/// \tparam T type of ip
template<typename T>
struct is_linear_container : std::false_type {};

/// \brief auxiliary structure for checking whether an argument is a list
template<typename... Args>
struct is_linear_container<std::list<Args...>> : std::true_type {};

/// \brief auxiliary structure for checking whether an argument is a vector
template<typename... Args>
struct is_linear_container<std::vector<Args...>> : std::true_type {};

/// \brief function to print custom ip where ip is linear container
/// \tparam T type of ip
/// \param ip custom ip address
/// \param buf ip address output buffer
/// \return
template <typename T>
typename std::enable_if_t<is_linear_container<T>::value> Print(const T& ip, std::string& buf){
    std::stringstream sstr;
    for (const auto& iteem : ip) {
        sstr << iteem;
        if (&iteem != &ip.back())
            sstr << ".";
    }
    buf = sstr.str();
}

/// \brief  auxiliary structure for checking whether an argument is a tuple
/// \tparam T type of tuple first element
/// \tparam Args  types of tuple elements
template <typename T, typename... Args>
struct all_args_is_t;
/// \brief  auxiliary structure for checking whether an argument is a tuple
/// \tparam T type of tuple element
template <typename T>
struct all_args_is_t<T> : public std::true_type {};
/// \brief auxiliary structure for checking whether an argument is a tuple with elements of different types
/// \tparam T type of tuple first element
/// \tparam U type of tuple second element
/// \tparam Args types of tuple elements
template <typename T, typename U, typename...Args>
struct all_args_is_t<T, U, Args...> : public std::false_type {};
/// \brief auxiliary structure for checking whether an argument is a tuple with elements of equal types
/// \tparam T type of tuple first element
/// \tparam Args types of tuple elements
template <typename T, typename...Args>
struct all_args_is_t<T, T, Args...> : public all_args_is_t<T, Args...> {};

/// \brief auxiliary structure for the output of the all elements of the tuple
/// \tparam T type of tuple first element
/// \tparam curPos position of the current element
/// \tparam size number of elements in the tuple
template< typename T, size_t curPos, size_t size>
struct format_tuple {
    static void printCurValue(const T& value, std::stringstream& sstr) {
        sstr << std::get<curPos>(value) << ".";
        format_tuple<T, curPos + 1, size>::printCurValue(value, sstr);
    }
};
/// \brief auxiliary structure for the output of the last element of the tuple
/// \tparam T type of tuple first element
/// \tparam curPos position of the current element
template< typename T, size_t curPos>
struct format_tuple<T, curPos, curPos> {
    static void printCurValue(const T& value, std::stringstream& sstr) {
        sstr << std::get<curPos>(value);
    }
};

/// \brief function to print custom ip where ip is tuple
/// \tparam T type of ip
/// \param ip custom ip address
/// \param buf ip address output buffer
/// \return
template <typename... Args>
typename std::enable_if<all_args_is_t< Args...>::value>::type Print(const std::tuple<Args...>& ip, std::string& buf) {
    constexpr int size = std::tuple_size<std::tuple<Args...>>::value ;
    std::stringstream sstr;
    format_tuple<std::tuple<Args...>, 0, size - 1>::printCurValue(ip, sstr);
    buf = sstr.str();
}

/// \brief auxiliary function for ip address output
/// \tparam T type of ip
/// \param ip custom ip address
template <typename T>
void Print(const T& ip){
    std::string buf;
    Print(ip, buf);
    std::cout<<buf<<std::endl;
}