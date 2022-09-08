#include <crypto/ContentHashes.h>

using namespace CNUSPACKER::contents;
using namespace CNUSPACKER::utils;

namespace CNUSPACKER::crypto {

    ContentHashes::ContentHashes(const std::string &file, bool hashed) {
        if (hashed) {
            CalculateH0Hashes(file);
            CalculateOtherHashes(1, h0Hashes, h1Hashes);
            CalculateOtherHashes(2, h1Hashes, h2Hashes);
            CalculateOtherHashes(3, h2Hashes, h3Hashes);
            TMDHash = HashUtil::HashSHA1(GetH3Hashes());
        } else {
            TMDHash = HashUtil::HashSHA1(file);
        }
    }

    void ContentHashes::CalculateOtherHashes(int hashLevel, std::unordered_map<int, std::vector<unsigned char>> &inHashes, std::unordered_map<int, std::vector<unsigned char>> &outHashes) {
        int hash_level_pow = 1 << (4 * hashLevel);

        int hashesCount = (blockCount / hash_level_pow) + 1;
        for (int new_block = 0; new_block < hashesCount; new_block++) {
            std::vector<unsigned char> cur_hashes(16 * 20);
            for (int i = new_block * 16; i < (new_block * 16) + 16; i++) {
                if (inHashes.find(i) != inHashes.end()) {
                    std::copy_n(inHashes[i].begin(), 20, cur_hashes.begin() + (i % 16) * 20);
                }
            }
            outHashes.emplace(new_block, HashUtil::HashSHA1(cur_hashes));

            if (new_block % 100 == 0) {
                std::cout << StringHelper::formatSimple("\rcalculating h{0}: {1}%", hashLevel, 100 * new_block / hashesCount);
            }
        }
        std::cout << StringHelper::formatSimple("\rcalculating h{0}: done", hashLevel) << std::endl;
    }

    void ContentHashes::CalculateH0Hashes(const std::string &file) {
        {
            FileStream input = FileStream(file, FileMode::Open);

            constexpr int bufferSize = 0xFC00;

            std::vector<unsigned char> buffer(bufferSize);
            int total_blocks = static_cast<int>(input.Length / bufferSize) + 1;
            for (int block = 0; block < total_blocks; block++) {
                input.Read(buffer, 0, bufferSize);

                h0Hashes.emplace(block, HashUtil::HashSHA1(buffer));

                if (block % 100 == 0) {
                    std::cout << StringHelper::formatSimple("\rcalculating h0: {0}%", 100 * block / total_blocks);
                }
            }
            std::cout << "\rcalculating h0: done" << std::endl;
            blockCount = total_blocks;
        }
    }

    std::vector<unsigned char> ContentHashes::GetHashForBlock(int block) {
        if (block > blockCount) {
            throw std::runtime_error("This shouldn't happen.");
        }

        MemoryStream *hashes = new MemoryStream(0x400);
        int h0_hash_start = (block / 16) * 16;
        for (int i = 0; i < 16; i++) {
            int index = h0_hash_start + i;
            if (h0Hashes.find(index) != h0Hashes.end()) {
                hashes->Write(h0Hashes[index]);
            } else {
                hashes->Seek(20, SeekOrigin::Current);
            }
        }

        int h1_hash_start = (block / 256) * 16;
        for (int i = 0; i < 16; i++) {
            int index = h1_hash_start + i;
            if (h1Hashes.find(index) != h1Hashes.end()) {
                hashes->Write(h1Hashes[index]);
            } else {
                hashes->Seek(20, SeekOrigin::Current);
            }
        }

        int h2_hash_start = (block / 4096) * 16;
        for (int i = 0; i < 16; i++) {
            int index = h2_hash_start + i;
            if (h2Hashes.find(index) != h2Hashes.end()) {
                hashes->Write(h2Hashes[index]);
            } else {
                hashes->Seek(20, SeekOrigin::Current);
            }
        }

        delete hashes;
        return hashes->GetBuffer();
    }

    std::vector<unsigned char> ContentHashes::GetH3Hashes() {
        MemoryStream *buffer = new MemoryStream(h3Hashes.size() * 20);
        for (int i = 0; i < h3Hashes.size(); i++) {
            buffer->Write(h3Hashes[i]);
        }

        delete buffer;
        return buffer->GetBuffer();
    }

    void ContentHashes::SaveH3ToFile(const std::string &h3Path) {
        if (h3Hashes.size() > 0) {
            {
                FileStream fos = FileStream(h3Path, FileMode::Create);

                fos.Write(GetH3Hashes());
            }
        }
    }
} // namespace CNUSPACKER::crypto