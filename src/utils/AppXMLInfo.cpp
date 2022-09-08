#include <stringFormat.h>
#include <utils/AppXMLInfo.h>
#include <utils/Utils.h>

namespace CNUSPACKER::utils {
    int64_t AppXMLInfo::getOsVersion() const {
        return osVersion;
    }

    void AppXMLInfo::setOsVersion(int64_t value) {
        osVersion = value;
    }

    int64_t AppXMLInfo::getTitleID() const {
        return titleID;
    }

    void AppXMLInfo::setTitleID(int64_t value) {
        titleID = value;
    }

    short AppXMLInfo::getTitleVersion() const {
        return titleVersion;
    }

    void AppXMLInfo::setTitleVersion(short value) {
        titleVersion = value;
    }

    unsigned int AppXMLInfo::getSdkVersion() const {
        return sdkVersion;
    }

    void AppXMLInfo::setSdkVersion(unsigned int value) {
        sdkVersion = value;
    }

    unsigned int AppXMLInfo::getAppType() const {
        return appType;
    }

    void AppXMLInfo::setAppType(unsigned int value) {
        appType = value;
    }

    short AppXMLInfo::getGroupID() const {
        return groupID;
    }

    void AppXMLInfo::setGroupID(short value) {
        groupID = value;
    }

    std::vector<unsigned char> AppXMLInfo::getOsMask() const {
        return osMask;
    }

    void AppXMLInfo::setOsMask(const std::vector<unsigned char> &value) {
        osMask = value;
    }

    int64_t AppXMLInfo::getCommonID() const {
        return commonID;
    }

    void AppXMLInfo::setCommonID(int64_t value) {
        commonID = value;
    }

    std::string AppXMLInfo::ToString() {
        return string_format("AppXMLInfo [version={%i}, OSVersion={%i}, titleID={%i}, titleVersion={%i}, ", version, getOsVersion(), getTitleID(), getTitleVersion()) + string_format("SDKVersion=%i, appType={%u}, groupID={%i}, OSMask={%X}, common_id={%i}]", getSdkVersion(), getAppType(), getGroupID(), CNUSPACKER::utils::Utils::ByteArrayToHexString(getOsMask()), getCommonID());
    }
} // namespace CNUSPACKER::utils