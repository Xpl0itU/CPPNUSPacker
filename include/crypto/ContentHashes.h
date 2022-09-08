#include <algorithm>
#include <contents/ContentInfo.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <stringHelper.h>
#include <unordered_map>
#include <utils/HashUtils.h>
#include <utils/Utils.h>
#include <vector>

using namespace CNUSPACKER::contents;
using namespace CNUSPACKER::utils;

namespace CNUSPACKER::crypto {
    class ContentHashes {
    public:
        aligned_vector<unsigned char> TMDHash;
        ContentHashes(const std::string &file, bool hashed);
        std::vector<unsigned char> GetHashForBlock(int block);
        void SaveH3ToFile(const std::string &h3Path);

    private:
        std::unordered_map<int, std::vector<unsigned char>> h0Hashes = std::unordered_map<int, std::vector<unsigned char>>();
        std::unordered_map<int, std::vector<unsigned char>> h1Hashes = std::unordered_map<int, std::vector<unsigned char>>();
        std::unordered_map<int, std::vector<unsigned char>> h2Hashes = std::unordered_map<int, std::vector<unsigned char>>();
        std::unordered_map<int, std::vector<unsigned char>> h3Hashes = std::unordered_map<int, std::vector<unsigned char>>();
        int blockCount = 0;
        void CalculateOtherHashes(int hashLevel, std::unordered_map<int, std::vector<unsigned char>> &inHashes, std::unordered_map<int, std::vector<unsigned char>> &outHashes);
        void CalculateH0Hashes(const std::string &file);
        std::vector<unsigned char> GetH3Hashes();
    };
} // namespace CNUSPACKER::crypto