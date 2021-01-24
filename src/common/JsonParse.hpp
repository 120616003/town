#ifndef JSONPARSE_H
#define JSONPARSE_H

#include "rapidjson/document.h"
#include <fstream>
#include <iostream>

using namespace rapidjson;

namespace town {

class JsonParse
{
public:
    enum class PARSE_TYPE : uint8_t
    {
        STRING = 0,
        FILE = 1
    };

public: // 解析
    JsonParse() {}

    JsonParse(const std::string& strJson, PARSE_TYPE eParseType = PARSE_TYPE::STRING)
    {
        if (PARSE_TYPE::STRING == eParseType) {
            m_document.Parse(strJson.c_str());
            return;
        }
        m_document.Parse(ReadFile(strJson).c_str());
    }

    void operator () (const std::string& strJson, PARSE_TYPE eParseType = PARSE_TYPE::STRING)
    {
        if (PARSE_TYPE::STRING == eParseType) {
            m_document.Parse(strJson.c_str());
            return;
        }
        m_document.Parse(ReadFile(strJson).c_str());
    }

    void Parse(const std::string& strJson, PARSE_TYPE eParseType = PARSE_TYPE::STRING)
    {
        if (PARSE_TYPE::STRING == eParseType) {
            m_document.Parse(strJson.c_str());
            return;
        }
        m_document.Parse(ReadFile(strJson).c_str());
    }

    void ParseString(const std::string& strJson)
    {
        m_document.Parse(strJson.c_str());
    }

    void ParseFile(const std::string& strJson)
    {
        m_document.Parse(ReadFile(strJson).c_str());
    }

    bool ParseWhetherSuccess()
    {
        return !m_document.HasParseError();
    }

public: // 取值
    JsonParse& operator[] (const std::string& strKey)
    {
        m_strKeyVec.push_back(strKey);
        return *this;
    }

    JsonParse& operator[] (size_t i)
    {
        m_ArrayIndex = i;
        const Value* value = &GetValue();
        std::cout << "address:" << value << std::endl;
        m_queue.push({i,value});
        return *this;
    }

    bool asBool() const
    {
        return GetValue().GetBool();
    }

    int8_t asInt8() const
    {
        return static_cast<int8_t>(GetValue().GetInt());
    }

    uint8_t asUInt8() const
    {
        return static_cast<uint8_t>(GetValue().GetUint());
    }

    int16_t asInt16() const
    {
        return static_cast<int16_t>(GetValue().GetInt());
    }

    uint16_t asUInt16() const
    {
        return static_cast<uint16_t>(GetValue().GetUint());
    }

    int32_t asInt() const
    {
        return GetValue().GetInt();
    }

    int32_t asInt32() const
    {
        return GetValue().GetInt();
    }

    uint32_t asUInt32() const
    {
        return GetValue().GetUint();
    }

    int64_t asInt64() const
    {
        return GetValue().GetInt64();
    }

    uint64_t asUInt64() const
    {
        return GetValue().GetUint64();
    }

    float asFloat() const
    {
        return GetValue().GetFloat();
    }

    double asDouble() const
    {
        return GetValue().GetDouble();
    }

    std::string asString() const
    {
        return GetValue().GetString();
    }

    size_t size() const
    {
        const Value* value = &GetValue();
        std::cout << "address size:" << value << std::endl;
        return GetValue().GetArray().Size();
    }

public: // 类型判断
    bool isNull()
    {
        const Value* value;
        GetValue(value);
        if (value) {
            return value->IsNull();
        }
        return false;
    }

    bool isBool()
    {
        const Value* value;
        GetValue(value);
        if (value) {
            return value->IsBool();
        }
        return false;
    }

    bool isNumber()
    {
        const Value* value;
        GetValue(value);
        if (value) {
            return value->IsNumber();
        }
        return false;
    }

    bool isInt32()
    {
        const Value* value;
        GetValue(value);
        if (value) {
            return value->IsInt();
        }
        return false;
    }

    bool isUInt32()
    {
        const Value* value;
        GetValue(value);
        if (value) {
            return value->IsUint();
        }
        return false;
    }

    bool isInt64()
    {
        const Value* value;
        GetValue(value);
        if (value) {
            return value->IsInt64();
        }
        return false;
    }

    bool isUInt64()
    {
        const Value* value;
        GetValue(value);
        if (value) {
            return value->IsUint64();
        }
        return false;
    }

    bool isDouble()
    {
        const Value* value;
        GetValue(value);
        if (value) {
            return value->IsDouble();
        }
        return false;
    }

    bool isString()
    {
        const Value* value;
        GetValue(value);
        if (value) {
            return value->IsString();
        }
        return false;
    }

    bool isArray()
    {
        const Value* value;
        GetValue(value);
        if (value) {
            return value->IsArray();
        }
        return false;
    }

    bool isObject()
    {
        const Value* value;
        GetValue(value);
        if (value) {
            return value->IsObject();
        }
        return false;
    }

private: // 私有函数
    void GetValue(const Value*& value)
    {
        try {
            value = &GetValue();
        }
        catch (...) {
            value = nullptr;
        }
    }

    const Value& GetValue() const
    {
        if (m_queue.size() && m_strKeyVec.size()) {
            std::cout  << "m_queue.size() && m_strKeyVec.size()\n";
            std::pair<int, const Value*> pair = m_queue.front();
            m_queue.pop();
            if ((*pair.second)[pair.first].HasMember(m_strKeyVec[0].c_str())) {
                std::cout  << "(*pair.second)[pair.first].HasMember(m_strKeyVec[0].c_str())\n";
                return GetValue((*pair.second)[pair.first][m_strKeyVec[0].c_str()], std::vector<std::string>(m_strKeyVec.begin() + 1, m_strKeyVec.end()));
            }
            else {
                throw std::runtime_error("key:[" + m_strKeyVec[0] + "] not exist");
            }

        }
        else if (m_queue.size() && !m_strKeyVec.size()) {
            std::cout  << "m_queue.size() && !m_strKeyVec.size()\n";
            std::pair<int, const Value*> pair = m_queue.front();
            m_queue.pop();
            return GetValue((*pair.second)[pair.first], {});
        }
        else if (m_document.HasMember(m_strKeyVec[0].c_str())) {
            std::cout  << "m_document.HasMember(m_strKeyVec[0].c_str()):" << m_strKeyVec.size() << std::endl;
            return GetValue(m_document[m_strKeyVec[0].c_str()], std::vector<std::string>(m_strKeyVec.begin() + 1, m_strKeyVec.end()));
        }
        else {
            throw std::runtime_error("key:[" + m_strKeyVec[0] + "] not exist");
        }
    }

    const Value& GetValue(const Value& value, const std::vector<std::string>& strKeyVec) const
    {
        std::cout  << "GetValue0\n";
        if (0 == strKeyVec.size()) {
            m_strKeyVec.clear();
            std::cout  << "GetValue1\n";
            if (m_ArrayIndex != -1) {
                std::cout  << "GetValue2\n";
                int index = m_ArrayIndex;
                m_ArrayIndex = -1;
                return value[index];
            }
            std::cout  << "GetValue3\n";
            return value;
        }
        std::cout  << "GetValue3\n";
        if (value.HasMember(strKeyVec[0].c_str())) {
            if (1 == strKeyVec.size())  {
                m_strKeyVec.clear();
                return value[strKeyVec[0].c_str()];
            }
            return GetValue(value[strKeyVec[0].c_str()], std::vector<std::string>(strKeyVec.begin() + 1, strKeyVec.end()));
        }
        else {
            throw std::runtime_error("key:[" + strKeyVec[0] + "] not exist");
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
        return std::move(strJson);
    }

private:
    Document m_document;
    mutable std::queue<std::pair<int, const Value*>> m_queue;
    mutable std::vector<std::string> m_strKeyVec;
    mutable int m_ArrayIndex = -1;
};

} /* town */

#endif /* JSONPARSE_H */