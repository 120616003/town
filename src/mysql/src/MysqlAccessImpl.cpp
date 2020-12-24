#include "MysqlAccessImpl.h"

namespace town {

MysqlAccessImpl::MysqlAccessImpl()
{
}

MysqlAccessImpl::~MysqlAccessImpl()
{
	mysql_stmt_close(m_pSqlStmt);
	mysql_close(m_pSqlCon);
}

int MysqlAccessImpl::Initialization(const std::string& strIp, const std::string& strName, const std::string& strPasswd, const std::string& strDBName, int iPort)
{
	m_pSqlCon = mysql_init(nullptr);
	if(!mysql_real_connect(m_pSqlCon, "localhost", strName.c_str(), strPasswd.c_str(), nullptr, iPort, nullptr, 0)) {
		LOG_ERROR("open database:{} failed", strDBName);
		return FAILED;
	}
	LOG_DEBUG("open database:{} success", strDBName);

	m_pSqlStmt = mysql_stmt_init(m_pSqlCon);
	if (!m_pSqlStmt) {
		LOG_ERROR("init failed, m_pSqlStmt is nullptr", strDBName);
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
	if (mysql_stmt_prepare(m_pSqlStmt, strSql.c_str(), strlen(strSql.c_str()))) {
		LOG_ERROR("[{}] prepare failed", strSql);
		return FAILED;
	}

	size_t iParamLen = vParam.size();
	if (0 != iParamLen) {
		MYSQL_BIND vSqlParam[iParamLen];
		for (size_t i = 0; i < iParamLen; i++) {
			vSqlParam[i].buffer_type = static_cast<enum_field_types>(std::atoi(vParam[i].second.c_str()));
			vSqlParam[i].buffer = &vParam[i].first;
			if (SQL_STRING == vParam[i].second) {
				vSqlParam[i].buffer_length = sizeof(vParam[i].first);
			}
		}

		if (mysql_stmt_bind_param(m_pSqlStmt, vSqlParam)) {
			LOG_ERROR("[{}] bind param failed", strSql);
			return FAILED;
		}
	}

	if (mysql_stmt_execute(m_pSqlStmt)) {
		LOG_ERROR("[{}] execute param failed", strSql);
		return FAILED;
	}
	LOG_DEBUG("[{}] execute success", strSql);
	return 0;
}

} /* town */