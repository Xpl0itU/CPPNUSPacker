#include <vector>

//using namespace CNUSPACKER::utils;

namespace CNUSPACKER::contents {
    class ContentInfo {
    public:
        static constexpr int staticDataSize = 0x24;
        std::vector<unsigned char> getSHA2Hash() const;
        void setSHA2Hash(const std::vector<unsigned char> &value);

        ContentInfo(short contentCount);

        std::vector<unsigned char> GetAsData();

    private:
        std::vector<unsigned char> SHA2Hash;

        const short indexOffset;
        const short contentCount;

        ContentInfo(short indexOffset, short contentCount);
    };
} // namespace CNUSPACKER::contents