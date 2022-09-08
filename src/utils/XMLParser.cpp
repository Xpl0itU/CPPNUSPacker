#include <utils/XMLParser.h>

namespace CNUSPACKER::utils {

    void XMLParser::LoadDocument(const std::string &path) {
        document->LoadFile(path.c_str());
    }

    AppXMLInfo *XMLParser::GetAppXMLInfo() {
        AppXMLInfo *appxmlinfo = new AppXMLInfo();
        tinyxml2::XMLElement *appElement = document->FirstChildElement("app");
        appxmlinfo->setOsVersion(strtol(appElement->FirstChildElement("os_version")->GetText(), nullptr, 16));
        appxmlinfo->setTitleID(strtol(appElement->FirstChildElement("title_id")->GetText(), nullptr, 16));
        appxmlinfo->setTitleVersion(strtol(appElement->FirstChildElement("title_version")->GetText(), nullptr, 16));
        appxmlinfo->setSdkVersion(strtol(appElement->FirstChildElement("sdk_version")->GetText(), nullptr, 10));
        appxmlinfo->setAppType(strtol(appElement->FirstChildElement("app_type")->GetText(), nullptr, 16));
        appxmlinfo->setGroupID(strtol(appElement->FirstChildElement("group_id")->GetText(), nullptr, 16));
        unsigned char *osMaskText = (unsigned char *) (appElement->FirstChildElement("os_mask")->GetText());
        std::vector<unsigned char> osMask(osMaskText, osMaskText + strlen(osMaskText));
        appxmlinfo->setOsMask(osMask);
        appxmlinfo->setCommonID(strtol(appElement->FirstChildElement("common_id")->GetText(), nullptr, 16));

        return appxmlinfo;
    }
} // namespace CNUSPACKER::utils