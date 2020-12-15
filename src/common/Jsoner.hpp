/*******************************************************
 * @brief: Json解析模块
 * @Copyright: Copyleft
 * @license: GPL
 * @birth: created by yan on 2020-12-9
 * @version: V0.0.1
 * @revision: last revised by yan on 2020-12-9
 *******************************************************/

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

	std::string GetValue()
	{
		if (0 == m_strKeyVec.size()) {
			return "";
		}

		if (m_document.HasMember(m_strKeyVec[0].c_str())) {
			return GetValue(m_document[m_strKeyVec[0].c_str()], std::vector<std::string>(m_strKeyVec.begin() + 1, m_strKeyVec.end()));
		}

		LOG_WARN("[{}] key not exists", m_strKeyVec[0]);
		m_strKeyVec.clear();
		return "";
	}

	std::string GetValue(const std::initializer_list<std::string>& strKeyList)
	{
		if (0 == strKeyList.size()) {
			return "";
		}

		std::vector<std::string> strKeyVec;
		std::copy(strKeyList.begin(), strKeyList.end(), std::back_inserter(strKeyVec));
		if (m_document.HasMember(strKeyVec[0].c_str())) {
			return GetValue(m_document[strKeyVec[0].c_str()], std::vector<std::string>(strKeyVec.begin() + 1, strKeyVec.end()));
		}

		LOG_WARN("[{}] key not exists", strKeyVec[0]);
		return "";
	}

	std::string GetValue(const Value& value, const std::vector<std::string>& strKeyVec)
	{
		if (0 == strKeyVec.size()) {
			m_strKeyVec.clear();
			return value.GetString();
		}
		if (value.HasMember(strKeyVec[0].c_str())) { 
			if (1 == strKeyVec.size())  {
				m_strKeyVec.clear();
				return value[strKeyVec[0].c_str()].GetString();
			}
			return GetValue(value[strKeyVec[0].c_str()], std::vector<std::string>(strKeyVec.begin() + 1, strKeyVec.end()));
		}
		LOG_WARN("[{}] key not exists", strKeyVec[0]);
		m_strKeyVec.clear();
		return "";
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
	std::vector<std::string> m_strKeyVec;
};

} /* town */

#endif /* JSONER_H */