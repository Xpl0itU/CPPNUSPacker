#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace CNUSPACKER::utils {
    class BigEndianMemoryStream {
    public:
        BigEndianMemoryStream(int capacity);

        void WriteBigEndian(short value);

        void WriteBigEndian(int value);

        void WriteBigEndian(unsigned int value);

        void WriteBigEndian(int64_t value);

        void Write(std::vector<unsigned char> value);

        std::vector<unsigned char> GetBuffer();
    };
} // namespace CNUSPACKER::utils