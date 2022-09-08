#include <array>
#include <bit>
#include <cstddef>
#include <iterator>
#include <ranges>
#include <sstream>
#include <utils/BigEndianMemoryStream.h>

char *buffer;
FILE *memory;
size_t size;

template<std::integral T>
constexpr T byteswap(T value) noexcept {
    static_assert(std::has_unique_object_representations_v<T>,
                  "T may not have padding bits");
    auto value_representation = std::bit_cast<std::array<std::byte, sizeof(T)>>(value);
    std::reverse(value_representation);
    return std::bit_cast<T>(value_representation);
}

namespace CNUSPACKER::utils {

    BigEndianMemoryStream::BigEndianMemoryStream(int capacity) {
        buffer = (char *) malloc(capacity);
        memory = open_memstream(&buffer, &size);
    }

    void BigEndianMemoryStream::WriteBigEndian(short value) {
        std::vector<unsigned char> shortBytes = {static_cast<unsigned char>(value)};

        fwrite(shortBytes.data(), shortBytes.size() / 2, 1, memory);
    }

    void BigEndianMemoryStream::WriteBigEndian(int value) {
        std::vector<unsigned char> intBytes = {static_cast<unsigned char>(value)};

        fwrite(intBytes.data(), intBytes.size() / 2, 1, memory);
    }

    void BigEndianMemoryStream::WriteBigEndian(unsigned int value) {
        std::vector<unsigned char> uintBytes = {static_cast<unsigned char>(value)};

        fwrite(uintBytes.data(), uintBytes.size() / 2, 1, memory);
    }

    void BigEndianMemoryStream::WriteBigEndian(int64_t value) {
        std::vector<unsigned char> longBytes = {static_cast<unsigned char>(value)};

        fwrite(longBytes.data(), longBytes.size() / 2, 1, memory);
    }

    void BigEndianMemoryStream::Write(std::vector<unsigned char> value) {
        fwrite(value.data(), value.size() / 2, 1, memory);
    }

    std::vector<unsigned char> BigEndianMemoryStream::GetBuffer() {
        return std::vector<unsigned char>(buffer, buffer + size);
    }
} // namespace CNUSPACKER::utils