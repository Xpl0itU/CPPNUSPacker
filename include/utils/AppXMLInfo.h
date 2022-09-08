#include <string>
#include <vector>

namespace CNUSPACKER::utils {
    class AppXMLInfo {
    private:
        int64_t osVersion = 0;
        int64_t titleID = 0;
        short titleVersion = 0;
        unsigned int sdkVersion = 0;
        unsigned int appType = 0;
        short groupID = 0;
        std::vector<unsigned char> osMask = std::vector<unsigned char>(32);
        int64_t commonID = 0;

        static constexpr int version = 0;

    public:
        int64_t getOsVersion() const;
        void setOsVersion(int64_t value);
        int64_t getTitleID() const;
        void setTitleID(int64_t value);
        short getTitleVersion() const;
        void setTitleVersion(short value);
        unsigned int getSdkVersion() const;
        void setSdkVersion(unsigned int value);
        unsigned int getAppType() const;
        void setAppType(unsigned int value);
        short getGroupID() const;
        void setGroupID(short value);
        std::vector<unsigned char> getOsMask() const;
        void setOsMask(const std::vector<unsigned char> &value);
        int64_t getCommonID() const;
        void setCommonID(int64_t value);

        std::string ToString();
    };
} // namespace CNUSPACKER::utils