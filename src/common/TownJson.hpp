#ifndef TOWN_JSON_H
#define TOWN_JSON_H

#include <string>
#include <vector>
#include <jsoncpp/json/json.h>
using namespace Json;

namespace town
{

enum class JSON_TYPE : uint8_t
{
    STRING = 0,
    FILE = 1
};

class TownJson
{
public:
    TownJson() {}
    TownJson(std::string strJson, JSON_TYPE eType = JSON_TYPE::STRING)
    {
        if (eType == JSON_TYPE::FILE) {
            strJson = ReadFile(strJson);
        }

        Reader rJson(Features::all());
        if (!rJson.parse(strJson, m_value)) {
            throw std::runtime_error("this json:\n" + strJson + "\nparse error");
        }
    }

    TownJson (const TownJson& rhs)
    {
        this->m_value = rhs.m_value;
    }

    TownJson (const Value& rhs)
    {
        this->m_value = rhs;
    }

    Value& operator [] (uint32_t uiIndex)
    {
        return m_value[uiIndex];
    }

    Value& operator [] (std::string strKey)
    {
        return m_value[strKey];
    }

    TownJson& operator = (const TownJson& rhs)
    {
        if (this != &rhs) {
            this->m_value = rhs.m_value;
        }
        return *this;
    }

    Value& operator = (Value& rhs)
    {
        return rhs;
    }

    bool Parse(std::string strJson, JSON_TYPE eType = JSON_TYPE::STRING)
    {
        if (eType == JSON_TYPE::FILE) {
            strJson = ReadFile(strJson);
        }

        Reader rJson(Features::all());
        if (!rJson.parse(strJson, m_value)) {
            throw std::runtime_error("this json:\n" + strJson + "\nparse error");
        }
    }

private:
    std::string ReadFile(const std::string& strPath)
    {
        std::fstream file(strPath, std::ios::in);
        if (!file.is_open()) {
            return "";
        }

        file.seekg(0, std::ios::end);
        size_t length = file.tellg();
        std::string strJson(length, 0);
        file.seekg(0, std::ios::beg);
        file.read(&strJson[0], length);

        if (strJson.empty()) {
            return "";
        }
        return strJson;
    }

private:
    Value m_value;
};

} /* town */

#endif /* TOWN_JSON_H */