#ifndef TOWN_JSON_H
#define TOWN_JSON_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <string>
#include <vector>
#include <fstream>
#include <QDebug>

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

        QJsonParseError flag;
        QJsonDocument  root = QJsonDocument::fromJson(strJson.c_str(), &flag); // 字符串格式化为JSON
        m_object = root.object();
        if(flag.error != QJsonParseError::NoError)
        {
            throw "json parse error";
        }
    }

    TownJson (const TownJson& rhs)
    {
        this->m_object = rhs.m_object;
    }

    TownJson (const QJsonObject& rhs)
    {
        this->m_object = rhs;
    }

    TownJson& operator = (const TownJson& rhs)
    {
        if (this != &rhs) {
            this->m_object = rhs.m_object;
        }
        return *this;
    }

    QJsonObject& operator = (QJsonObject& rhs)
    {
        m_object = rhs;
        return m_object;
    }

    QJsonValue operator [] (const std::string key)
    {
        return m_object.value(key.c_str());
    }

    bool Parse(std::string strJson, JSON_TYPE eType = JSON_TYPE::STRING)
    {
        if (eType == JSON_TYPE::FILE) {
            strJson = ReadFile(strJson);
        }

        QJsonParseError flag;
        QJsonDocument  root = QJsonDocument::fromJson(strJson.c_str(), &flag); // 字符串格式化为JSON
        m_object = root.object();
        if(flag.error != QJsonParseError::NoError)
        {
            return false;
        }
        return true;
    }

private:
    std::string ReadFile(const std::string& strPath)
    {
        std::fstream file(strPath.c_str(), std::ios::in);
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
    QJsonObject m_object;
};

} /* town */

#endif /* TOWN_JSON_H */
