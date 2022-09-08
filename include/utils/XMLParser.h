#include <iostream>
#include <string>
#include <tinyxml2.h>
#include <utils/AppXMLInfo.h>
#include <vector>

namespace CNUSPACKER::utils {
    class XMLParser {
    private:
        tinyxml2::XMLDocument *document = new tinyxml2::XMLDocument();

    public:
        virtual ~XMLParser() {
            delete document;
        }

        void LoadDocument(const std::string &path);

        AppXMLInfo *GetAppXMLInfo();
    };
} // namespace CNUSPACKER::utils