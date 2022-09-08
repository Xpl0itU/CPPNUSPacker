#include <boost/align/aligned_allocator.hpp>
#include <string>
#include <vector>

template<typename T>
using aligned_vector = std::vector<T, boost::alignment::aligned_allocator<T, 32768>>;

namespace CNUSPACKER::utils {
    class HashUtil final {
    public:
        static std::vector<unsigned char> HashSHA2(std::vector<unsigned char> &data);

        static aligned_vector<unsigned char> HashSHA1(std::vector<unsigned char> data);

        static aligned_vector<unsigned char> HashSHA1(const std::string &file);
    };
} // namespace CNUSPACKER::utils