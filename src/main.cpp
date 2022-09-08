#include <iostream>
#include <settings.h>
#include <utils/XMLParser.h>

int main() {
    CNUSPACKER::utils::XMLParser *xml = new CNUSPACKER::utils::XMLParser();
    xml->LoadDocument("app.xml");
    printf("osMask: %s \n", xml->GetAppXMLInfo()->getOsMask().data());

    return 0;
}