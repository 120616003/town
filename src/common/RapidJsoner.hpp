/*******************************************************
 * @brief: Json解析模块
 * @Copyright: Copyleft
 * @license: GPL
 * @birth: created by yan on 2020-12-9
 * @version: V0.0.1
 * @revision: last revised by yan on 2020-12-9
 *******************************************************/

#ifndef RAPID_JSONER_H
#define RAPID_JSONER_H

#include <memory>
#include "rapidjson/document.h"
using namespace rapidjson;

class RapidJsoner
{
public:
	RapidJsoner() {}
	RapidJsoner(std::string strJson)
	{
		m_document.Parse(strJson.c_str());
	}
	~RapidJsoner() {}

public:
	RapidJsoner operator [] (std::string key)
	{
		// auto tmp = m_document[key.c_str()];
	}

public:
	std::string GetKey(std::string key)
	{
		return m_document[key.c_str()].GetString();
	}

	std::string asString()
	{

	}
private:
	Document m_document;

};
#endif /* RAPID_JSONER_H */