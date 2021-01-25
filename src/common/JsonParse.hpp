#ifndef JSONPARSE_H
#define JSONPARSE_H

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <fstream>
#include <iostream>
#include <tuple>

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

    JsonParse(const std::string& strJson, PARSE_TYPE eParseType)
    {
        if (PARSE_TYPE::STRING == eParseType) {
            m_document.Parse(strJson.c_str());
            return;
        }
        m_document.Parse(ReadFile(strJson).c_str());
    }

    JsonParse(const JsonParse& rhs)
    {
        m_document.CopyFrom(rhs.GetValue(), rhs.m_document.GetAllocator());
        if (rhs.m_queue.size() != 0) {
            std::tuple<const Value&, int, std::vector<std::string>> t = rhs.m_queue.front();
            m_ArrayIndex = std::get<1>(t);
            m_strKeyVec = std::get<2>(t);
            std::tuple<Value&, int, std::vector<std::string>> tt = {GetValue(), std::get<1>(t), std::get<2>(t)};
            m_queue.push(tt);
        }
    }

    void Parse(const std::string& strJson, PARSE_TYPE eParseType)
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

public: // 拷贝
    JsonParse& operator = (const JsonParse& rhs)
    {
        if (this != &rhs) {
            // if (m_document.GetType() == rhs.m_document.GetType())
            if (m_strKeyVec.size()) {
                Value& value = GetValue();
                if (value.GetType() == rhs.m_document.GetType()) {
                    std::cout << "type sync\n";
                    Value vv;
                    vv.CopyFrom(rhs.m_document, rhs.m_document.GetAllocator());
                    value = vv;
                }
            }
            else {
                m_document.CopyFrom(rhs.GetValue(), rhs.m_document.GetAllocator());
                if (rhs.m_queue.size() != 0) {
                    std::tuple<Value&, int, std::vector<std::string>> t = rhs.m_queue.front();
                    m_ArrayIndex = std::get<1>(t);
                    m_strKeyVec = std::get<2>(t);
                    std::tuple<Value&, int, std::vector<std::string>> tt = {GetValue(), std::get<1>(t), std::get<2>(t)};
                    m_queue.push(tt);
                }
            }
        }
        return *this;
    }

    void operator () (const std::string& strJson, PARSE_TYPE eParseType)
    {
        if (PARSE_TYPE::STRING == eParseType) {
            m_document.Parse(strJson.c_str());
            return;
        }
        m_document.Parse(ReadFile(strJson).c_str());
    }

public: // 隐式转换
    JsonParse(const std::string& value)
    {
        m_document.SetString(value.c_str(), value.size());
    }
    // void operator = (const std::string& rhs)
    // {
    //     if (this != &rhs) {
    //         m_document.CopyFrom(rhs.GetValue(), rhs.m_document.GetAllocator());
    //         if (rhs.m_queue.size() != 0) {
    //             std::tuple<const Value&, int, std::vector<std::string>> t = rhs.m_queue.front();
    //             m_ArrayIndex = std::get<1>(t);
    //             m_strKeyVec = std::get<2>(t);
    //             m_queue.push({GetValue(), std::get<1>(t), std::get<2>(t)});
    //         }
    //     }
    //     return *this;
    // }
public: // 生成字符串
    std::string AsString()
    {
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        m_document.Accept(writer);
        return buffer.GetString();
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
        std::tuple<Value&, int, std::vector<std::string>> tt = {GetValue(), i, m_strKeyVec};
        m_queue.push(tt);
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
            std::tuple<const Value&, int, std::vector<std::string>> t = m_queue.front();
            m_queue.pop();
            if (std::get<0>(t).HasMember(m_strKeyVec[0].c_str())) {
                return GetValue(std::get<0>(t)[m_strKeyVec[0].c_str()], std::vector<std::string>(m_strKeyVec.begin() + 1, m_strKeyVec.end()));
            }
            else {
                throw std::runtime_error("key:[" + m_strKeyVec[0] + "] not exist");
            }
        }
        else if (m_queue.size() && !m_strKeyVec.size()) {
            std::tuple<const Value&, int, std::vector<std::string>> t = m_queue.front();
            m_queue.pop();
            return GetValue(std::get<0>(t), {});
        }
        else if (!m_strKeyVec.size()) {
            return GetValue(m_document, {});
        }
        else if (m_document.HasMember(m_strKeyVec[0].c_str())) {
            return GetValue(m_document[m_strKeyVec[0].c_str()], std::vector<std::string>(m_strKeyVec.begin() + 1, m_strKeyVec.end()));
        }
        else {
            throw std::runtime_error("key:[" + m_strKeyVec[0] + "] not exist");
        }
    }

    Value& GetValue()
    {
        if (m_queue.size() && m_strKeyVec.size()) {
            std::tuple<Value&, int, std::vector<std::string>> t = m_queue.front();
            m_queue.pop();
            if (std::get<0>(t).HasMember(m_strKeyVec[0].c_str())) {
                Value& value = std::get<0>(t)[m_strKeyVec[0].c_str()];
                return GetValue(value, std::vector<std::string>(m_strKeyVec.begin() + 1, m_strKeyVec.end()));
            }
            else {
                throw std::runtime_error("key:[" + m_strKeyVec[0] + "] not exist");
            }
        }
        else if (m_queue.size() && !m_strKeyVec.size()) {
            std::tuple<Value&, int, std::vector<std::string>> t = m_queue.front();
            m_queue.pop();
            Value& value = std::get<0>(t);
            return GetValue(value, {});
        }
        else if (!m_strKeyVec.size()) {
            return GetValue(m_document, {});
        }
        else if (m_document.HasMember(m_strKeyVec[0].c_str())) {
            Value& value = m_document[m_strKeyVec[0].c_str()];
            return GetValue(value, std::vector<std::string>(m_strKeyVec.begin() + 1, m_strKeyVec.end()));
        }
        else {
            throw std::runtime_error("key:[" + m_strKeyVec[0] + "] not exist");
        }
    }

    const Value& GetValue(const Value& value, const std::vector<std::string>& strKeyVec) const
    {
        if (0 == strKeyVec.size()) {
            m_strKeyVec.clear();
            if (m_ArrayIndex != -1) {
                int index = m_ArrayIndex;
                m_ArrayIndex = -1;
                return value[index];
            }
            return value;
        }

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

    Value& GetValue(Value& value, const std::vector<std::string>& strKeyVec)
    {
        if (0 == strKeyVec.size()) {
            m_strKeyVec.clear();
            if (m_ArrayIndex != -1) {
                int index = m_ArrayIndex;
                m_ArrayIndex = -1;
                return value[index];
            }
            return value;
        }

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
    mutable Document m_document;
    mutable std::queue<std::tuple<Value&, int, std::vector<std::string>>> m_queue;
    mutable std::vector<std::string> m_strKeyVec;
    mutable int m_ArrayIndex = -1;
};

} /* town */

#endif /* JSONPARSE_H */