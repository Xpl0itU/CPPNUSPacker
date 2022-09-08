#include <filesystem>
#include <utils/Utils.h>

namespace CNUSPACKER::utils {

    void Utils::DeleteDir(const std::string &dir) {
        std::filesystem::remove_all(dir);
    }

    int64_t Utils::Align(int64_t input, int alignment) {
        int64_t newSize = input / alignment;
        if (newSize * alignment != input) {
            newSize++;
        }

        return newSize * alignment;
    }

    std::vector<unsigned char> Utils::HexStringToByteArray(const std::string &s) {
        int outputLength = s.length() / 2;
        std::vector<unsigned char> output(outputLength);
        for (int i = 0; i < outputLength; i++) {
            output[i] = reinterpret_cast<unsigned char>(s.substr(i * 2, 2).data());
        }

        return output;
    }

    std::string Utils::ByteArrayToHexString(std::vector<unsigned char> bytes) {
        std::vector<char> c(bytes.size() * 2);
        for (int i = 0; i < bytes.size(); i++) {
            int b = bytes[i] >> 4;
            c[i * 2] = static_cast<char>(55 + b + (((b - 10) >> 31) & -7));
            b = bytes[i] & 0xF;
            c[i * 2 + 1] = static_cast<char>(55 + b + (((b - 10) >> 31) & -7));
        }

        return std::string(c.data());
    }

    std::vector<unsigned char> Utils::CopyOfRange(std::vector<unsigned char> &src, int start, int end) {
        int len = end - start;
        std::vector<unsigned char> dest(len);
        std::copy_n(src.begin() + start, len, dest.begin());

        return dest;
    }
} // namespace CNUSPACKER::utils