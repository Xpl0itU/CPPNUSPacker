#include <algorithm>
#include <string>
#include <vector>

namespace CNUSPACKER::utils {
    class Utils final {
    public:
        static void DeleteDir(const std::string &dir);

        static int64_t Align(int64_t input, int alignment);

        static std::vector<unsigned char> HexStringToByteArray(const std::string &s);

        static std::string ByteArrayToHexString(std::vector<unsigned char> bytes);

        static std::vector<unsigned char> CopyOfRange(std::vector<unsigned char> &src, int start, int end);
    };
} // namespace CNUSPACKER::utils