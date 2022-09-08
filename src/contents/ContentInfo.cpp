#include <contents/ContentInfo.h>
#include <utils/BigEndianMemoryStream.h>

using namespace CNUSPACKER::utils;

namespace CNUSPACKER::contents {

    std::vector<unsigned char> ContentInfo::getSHA2Hash() const {
        return SHA2Hash;
    }

    void ContentInfo::setSHA2Hash(const std::vector<unsigned char> &value) {
        SHA2Hash = value;
    }

    ContentInfo::ContentInfo(short contentCount) : ContentInfo(0, contentCount) {
    }

    ContentInfo::ContentInfo(short indexOffset, short contentCount) : indexOffset(indexOffset), contentCount(contentCount) {
    }

    std::vector<unsigned char> ContentInfo::GetAsData() {
        BigEndianMemoryStream *buffer = new BigEndianMemoryStream(2304);
        buffer->WriteBigEndian(indexOffset);
        buffer->WriteBigEndian(contentCount);

        buffer->Write(getSHA2Hash());

        delete buffer;
        return buffer->GetBuffer();
    }
} // namespace CNUSPACKER::contents