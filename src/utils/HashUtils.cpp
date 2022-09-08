#include <sys/stat.h>
#include <utils/HashUtils.h>

#include <openssl/evp.h>

static inline bool getHash(const void *data, size_t data_len, void *hash, const EVP_MD *type) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    bool ret = false;

    if (ctx) {
        if (EVP_DigestInit(ctx, type) == 1) {
            if (EVP_DigestUpdate(ctx, data, data_len) == 1)
                ret = EVP_DigestFinal(ctx, hash, NULL) == 1;
        }

        EVP_MD_CTX_free(ctx);
    }

    return ret;
}

bool getSHA256(const void *data, size_t data_len, void *hash) {
    return getHash(data, data_len, hash, EVP_sha256());
}

bool getSHA1(const void *data, size_t data_len, void *hash) {
    return getHash(data, data_len, hash, EVP_sha1());
}

int32_t loadFile(const char *fPath, void **buf) {
    int ret = 0;
    FILE *file = fopen(fPath, "rb");
    if (file != nullptr) {
        struct stat st;
        stat(fPath, &st);
        int size = st.st_size;

        *buf = (void *) malloc(size);
        if (*buf != nullptr) {
            if (fread(*buf, size, 1, file) == 1)
                ret = size;
            else
                free(*buf);
        }
        fclose(file);
    }
    return ret;
}

namespace CNUSPACKER::utils {
    std::vector<unsigned char> HashUtil::HashSHA2(std::vector<unsigned char> &data) {
        std::vector<unsigned char> hash;
        getSHA256(data.data(), data.size(), hash.data());
        return hash;
    }

    std::vector<unsigned char> HashUtil::HashSHA1(std::vector<unsigned char> &data) {
        std::vector<unsigned char> hash;
        getSHA1(data.data(), data.size(), hash.data());
        return hash;
    }

    std::vector<unsigned char> HashUtil::HashSHA1(const std::string &file) {
        std::vector<unsigned char> data;
        std::vector<unsigned char> hash;
        unsigned char *stuff = data.data();
        loadFile(file.c_str(), &stuff);
        getSHA1(stuff, sizeof(stuff), hash.data());
        return hash;
    }
} // namespace CNUSPACKER::utils
