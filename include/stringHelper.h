#include <algorithm>
#include <cctype>
#include <exception>
#include <sstream>
#include <string>
#include <vector>

class StringHelper {
public:
    static std::string toLower(std::string source) {
        std::transform(source.cbegin(), source.cend(), source.begin(), [](unsigned char c) { return std::tolower(c); });
        return source;
    }

    static std::string toUpper(std::string source) {
        std::transform(source.cbegin(), source.cend(), source.begin(), [](unsigned char c) { return std::toupper(c); });
        return source;
    }

    static std::string trimStart(std::string source, const std::string &trimChars = " \t\n\r\v\f") {
        return source.erase(0, source.find_first_not_of(trimChars));
    }

    static std::string trimEnd(std::string source, const std::string &trimChars = " \t\n\r\v\f") {
        return source.erase(source.find_last_not_of(trimChars) + 1);
    }

    static std::string trim(std::string source, const std::string &trimChars = " \t\n\r\v\f") {
        return trimStart(trimEnd(source, trimChars), trimChars);
    }

    static std::string replace(std::string source, const std::string &find, const std::string &replace) {
        std::size_t pos = 0;
        while ((pos = source.find(find, pos)) != std::string::npos) {
            source.replace(pos, find.length(), replace);
            pos += replace.length();
        }
        return source;
    }


    static bool startsWith(const std::string &source, const std::string &value) {
        if (source.length() < value.length())
            return false;
        else
            return source.compare(0, value.length(), value) == 0;
    }

    static bool endsWith(const std::string &source, const std::string &value) {
        if (source.length() < value.length())
            return false;
        else
            return source.compare(source.length() - value.length(), value.length(), value) == 0;
    }

    static std::vector<std::string> split(const std::string &source, char delimiter) {
        std::vector<std::string> output;
        std::istringstream ss(source);
        std::string nextItem;

        while (std::getline(ss, nextItem, delimiter)) {
            output.push_back(nextItem);
        }

        return output;
    }

    template<typename T>
    static std::string toString(const T &subject) {
        std::ostringstream ss;
        ss << subject;
        return ss.str();
    }

    template<typename T>
    static T fromString(const std::string &subject) {
        std::istringstream ss(subject);
        T target;
        ss >> target;
        return target;
    }

    static bool isEmptyOrWhiteSpace(const std::string &source) {
        if (source.length() == 0)
            return true;
        else {
            for (std::size_t index = 0; index < source.length(); index++) {
                if (!std::isspace(source[index]))
                    return false;
            }

            return true;
        }
    }

    template<typename T>
    static std::string formatSimple(const std::string &input, T arg0) {
        std::ostringstream ss;
        std::size_t lastCloseBrace = std::string::npos;
        std::size_t openBrace = std::string::npos;
        while ((openBrace = input.find('{', openBrace + 1)) != std::string::npos) {
            if (openBrace + 1 < input.length()) {
                if (input[openBrace + 1] == '{') {
                    openBrace++;
                    continue;
                }

                std::size_t closeBrace = input.find('}', openBrace + 1);
                if (closeBrace != std::string::npos) {
                    ss << input.substr(lastCloseBrace + 1, openBrace - lastCloseBrace - 1);
                    lastCloseBrace = closeBrace;

                    std::string index = trim(input.substr(openBrace + 1, closeBrace - openBrace - 1));
                    if (index == "0")
                        ss << arg0;
                    else
                        throw std::runtime_error("Only simple positional format specifiers are handled by the 'formatSimple' helper method.");
                }
            }
        }

        if (lastCloseBrace + 1 < input.length())
            ss << input.substr(lastCloseBrace + 1);

        return ss.str();
    }

    template<typename T1, typename T2>
    static std::string formatSimple(const std::string &input, T1 arg0, T2 arg1) {
        std::ostringstream ss;
        std::size_t lastCloseBrace = std::string::npos;
        std::size_t openBrace = std::string::npos;
        while ((openBrace = input.find('{', openBrace + 1)) != std::string::npos) {
            if (openBrace + 1 < input.length()) {
                if (input[openBrace + 1] == '{') {
                    openBrace++;
                    continue;
                }

                std::size_t closeBrace = input.find('}', openBrace + 1);
                if (closeBrace != std::string::npos) {
                    ss << input.substr(lastCloseBrace + 1, openBrace - lastCloseBrace - 1);
                    lastCloseBrace = closeBrace;

                    std::string index = trim(input.substr(openBrace + 1, closeBrace - openBrace - 1));
                    if (index == "0")
                        ss << arg0;
                    else if (index == "1")
                        ss << arg1;
                    else
                        throw std::runtime_error("Only simple positional format specifiers are handled by the 'formatSimple' helper method.");
                }
            }
        }

        if (lastCloseBrace + 1 < input.length())
            ss << input.substr(lastCloseBrace + 1);

        return ss.str();
    }

    template<typename T1, typename T2, typename T3>
    static std::string formatSimple(const std::string &input, T1 arg0, T2 arg1, T3 arg2) {
        std::ostringstream ss;
        std::size_t lastCloseBrace = std::string::npos;
        std::size_t openBrace = std::string::npos;
        while ((openBrace = input.find('{', openBrace + 1)) != std::string::npos) {
            if (openBrace + 1 < input.length()) {
                if (input[openBrace + 1] == '{') {
                    openBrace++;
                    continue;
                }

                std::size_t closeBrace = input.find('}', openBrace + 1);
                if (closeBrace != std::string::npos) {
                    ss << input.substr(lastCloseBrace + 1, openBrace - lastCloseBrace - 1);
                    lastCloseBrace = closeBrace;

                    std::string index = trim(input.substr(openBrace + 1, closeBrace - openBrace - 1));
                    if (index == "0")
                        ss << arg0;
                    else if (index == "1")
                        ss << arg1;
                    else if (index == "2")
                        ss << arg2;
                    else
                        throw std::runtime_error("Only simple positional format specifiers are handled by the 'formatSimple' helper method.");
                }
            }
        }

        if (lastCloseBrace + 1 < input.length())
            ss << input.substr(lastCloseBrace + 1);

        return ss.str();
    }
};