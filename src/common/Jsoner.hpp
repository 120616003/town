#ifndef JSONER_H
#define JSONER_H

#include "Logger.hpp"
#include "config.h"
#include "rapidjson/document.h"
using namespace rapidjson;

namespace town {

#undef LOG_DEBUG
#undef LOG_INFO
#undef LOG_WARN
#undef LOG_ERROR

#define LOG_DEBUG(...) DEBUG("  json  ", __VA_ARGS__)
#define LOG_INFO(...)  INFO("  json  ", __VA_ARGS__)
#define LOG_WARN(...)  WARN("  json  ", __VA_ARGS__)
#define LOG_ERROR(...) ERROR("  json  ", __VA_ARGS__)

class Jsoner
{
public:
	enum class PARSE_TYPE : uint8_t
	{
		STRING = 0,
		FILE = 1
	};

public: // 解析
	Jsoner() {}

	Jsoner(const std::string& strJson, PARSE_TYPE eParseType = PARSE_TYPE::STRING)
	{
		if (PARSE_TYPE::STRING == eParseType) {
			m_document.Parse(strJson.c_str());
			return;
		}
		m_document.Parse(ReadFile(strJson).c_str());
	}

	Jsoner(const Jsoner& rhs)
	{
		// rhs.m_value = GetValue();
		// m_strKeyVec

	}

	void operator () (const std::string& strJson, PARSE_TYPE eParseType = PARSE_TYPE::STRING)
	{
		if (PARSE_TYPE::STRING == eParseType) {
			m_document.Parse(strJson.c_str());
			return;
		}
		m_document.Parse(ReadFile(strJson).c_str());
	}

	void Pares(const std::string& strJson, PARSE_TYPE eParseType = PARSE_TYPE::STRING)
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
	Jsoner& operator[] (const std::string& strKey)
	{
		m_strKeyVec.push_back(strKey);
		return *this;
	}

	Jsoner& operator[] (size_t i)
	{
		m_ArrayIndex = i;
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
	bool isNull() const
	{
		return GetValue().IsNull();
	}

	bool isBool() const
	{
		return GetValue().IsBool();
	}

	bool isNumber() const
	{
		return GetValue().IsNumber();
	}

	bool isInt32() const
	{
		return GetValue().IsInt();
	}

	bool isUInt32() const
	{
		return GetValue().IsUint();
	}

	bool isInt64() const
	{
		return GetValue().IsInt64();
	}

	bool isUInt64() const
	{
		return GetValue().IsUint64();
	}

	bool isDouble() const
	{
		return GetValue().IsDouble();
	}

	bool isString() const
	{
		return GetValue().IsString();
	}

	bool isArray() const
	{
		return GetValue().IsArray();
	}

	bool isObject() const
	{
		return GetValue().IsObject();
	}

private: // 私有函数
	const Value& GetValue() const
	{
		if (m_document.HasMember(m_strKeyVec[0].c_str())) {
			return GetValue(m_document[m_strKeyVec[0].c_str()], std::vector<std::string>(m_strKeyVec.begin() + 1, m_strKeyVec.end()));
		}

		LOG_WARN("[{}] key not exists", m_strKeyVec[0]);
		exit(1);
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

		LOG_WARN("[{}] key not exists", strKeyVec[0]);
		exit(1);
	}

private:
	std::string ReadFile(const std::string& strPath)
	{
		std::fstream file(strPath, std::ios::in);
		if (!file.is_open()) {
			LOG_WARN("[{}] file incorrect", strPath);
			return "";
		}

		file.seekg(0, std::ios::end);
		size_t length = file.tellg();
		std::string strJson(length, 0);
		file.seekg(0, std::ios::beg);
		file.read(&strJson[0], length);

		if (strJson.empty()) {
			LOG_WARN("[{}] file incorrect, file is empty", strPath);
			return "";
		}
		return std::move(strJson);
	}

private:
	Document m_document;
	Value m_value;
	mutable std::vector<std::string> m_strKeyVec;
	mutable int m_ArrayIndex = -1;
};

#undef LOG_DEBUG
#undef LOG_INFO
#undef LOG_WARN
#undef LOG_ERROR

} /* town */

#endif /* JSONER_H */