#pragma once

#include <string>

namespace CNUSPACKER {
    class Settings final {
    public:
        static constexpr short groupid_code = 0x0000;
        static constexpr short groupid_meta = 0x0400;

        static constexpr short fstflags_code = 0x0000;
        static constexpr short fstflags_meta = 0x0040;
        static constexpr short fstflags_content = 0x0400;

        static const std::string encryptWithFile;

        static const std::string defaultEncryptionKey;
        static const std::string defaultEncryptWithKey;

        static const std::string pathToAppXml;

        static const std::string tmpDir;
    };
} // namespace CNUSPACKER