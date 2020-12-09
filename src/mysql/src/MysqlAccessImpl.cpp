/*******************************************************
 * @brief: Mysql访问模块
 * @Copyright: Copyleft
 * @license: GPL
 * @birth: created by yan on 2020-12-8
 * @version: V0.0.1
 * @revision: last revised by yan on 2020-12-8
 *******************************************************/

#include "MysqlAccessImpl.h"
#include "MysqlCommon.h"

namespace town {

MysqlAccessImpl::MysqlAccessImpl()
{
	m_SqlConPtr = std::make_unique<MYSQL>();
}

MysqlAccessImpl::~MysqlAccessImpl()
{
}

int MysqlAccessImpl::Initialization(const std::string& strName, const std::string& strPasswd, const std::string& strDBName, int iPort)
{
	mysql_init(m_SqlConPtr.get());
	if(!mysql_real_connect(m_SqlConPtr.get(), "localhost", strName.c_str(), strPasswd.c_str(), strDBName.c_str(), iPort, NULL, 0)) {
		LOG_ERROR("open database:{} failed", strDBName);
		return FAILED;
	}
	LOG_INFO("open database:{} success", strDBName);
	return SUCCESS;
}

} /* town */