/*******************************************************
 * @brief: Mysql访问模块
 * @Copyright: Copyleft
 * @license: GPL
 * @birth: created by yan on 2020-12-8
 * @version: V0.0.1
 * @revision: last revised by yan on 2020-12-8
 *******************************************************/

#include "MysqlAccessImpl.h"

namespace town {

MysqlAccessImpl::MysqlAccessImpl()
{
	m_SqlConPtr = std::make_shared<MYSQL>();
}

MysqlAccessImpl::~MysqlAccessImpl()
{
	mysql_stmt_close(m_SqlStmtPtr.get());
	mysql_close(m_SqlConPtr.get());
}

int MysqlAccessImpl::Initialization(const std::string& strIp, const std::string& strName, const std::string& strPasswd, const std::string& strDBName, int iPort)
{
	m_SqlConPtr.reset(mysql_init(nullptr));
	if(!mysql_real_connect(m_SqlConPtr.get(), "localhost", strName.c_str(), strPasswd.c_str(), strDBName.c_str(), iPort, NULL, 0)) {
		LOG_ERROR("open database:{} failed", strDBName);
		return FAILED;
	}
	LOG_DEBUG("open database:{} success", strDBName);

	m_SqlStmtPtr.reset(mysql_stmt_init(m_SqlConPtr.get()));
	if (!m_SqlStmtPtr) {
		LOG_ERROR("init failed, m_SqlStmtPtr is nullptr", strDBName);
		return FAILED;
	}
	LOG_INFO("initialization database:{} success", strDBName);

	return SUCCESS;
}

int MysqlAccessImpl::ExecuteSql(const std::string& strSql)
{
	std::vector<std::pair<std::string, std::string>> vParam;
	return ExecuteSql(strSql, vParam);
}

template <typename T>
int MysqlAccessImpl::ExecuteSql(const std::string& strSql, std::vector<std::pair<T, std::string>>& vParam)
{
	if (mysql_stmt_prepare(m_SqlStmtPtr.get(), strSql.c_str(), strlen(strSql.c_str()))) {
		LOG_ERROR("[{}] prepare failed", strSql);
		return FAILED;
	}

	size_t iParamLen = vParam.size();
	if (iParamLen) {
		MYSQL_BIND vSqlParam[iParamLen];
		for (size_t i = 0; i < iParamLen; i++) {
			vSqlParam[i].buffer_type = static_cast<enum_field_types>(std::atoi(vParam[i].second.c_str()));
			vSqlParam[i].buffer = &vParam[i].first;
			if (SQL_STRING == vParam[i].second) {
				vSqlParam[i].buffer_length = sizeof(vParam[i].first);
			}
		}

		if (mysql_stmt_bind_param(m_SqlStmtPtr.get(), vSqlParam)) {
			LOG_ERROR("[{}] bind param failed", strSql);
			return FAILED;
		}
	}

	if (mysql_stmt_execute(m_SqlStmtPtr.get())) {
		LOG_ERROR("[{}] execute param failed", strSql);
		return FAILED;
	}
	LOG_DEBUG("[{}] execute success", strSql);
	return 0;
}

} /* town */