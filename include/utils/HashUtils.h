#include <string>
#include <vector>

namespace CNUSPACKER::utils {
    class HashUtil final {
    public:
        static std::vector<unsigned char> HashSHA2(std::vector<unsigned char> &data);

        static std::vector<unsigned char> HashSHA1(std::vector<unsigned char> &data);

        static std::vector<unsigned char> HashSHA1(const std::string &file);
    };
} // namespace CNUSPACKER::utils