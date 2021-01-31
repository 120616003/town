#include "MysqlAccessImpl.h"
#include "MysqlCommon.h"

namespace town {

bool MysqlAccessImpl::ConnectDb(const std::string& strDbName, const std::string& strIp, const std::string& strDbaName, const std::string& strPasswd, unsigned int uiPort)
{
	return m_MysqlCon.connect(strDbName.c_str(), strIp.c_str(), strDbaName.c_str(), strPasswd.c_str(), uiPort);
}

std::pair<bool, StoreQueryResult> MysqlAccessImpl::ExecuteSql(const std::string& strSql, const SQLQueryParms& strParam)
{
	Query query(&m_MysqlCon, true, strSql.c_str());
	StoreQueryResult res;
	try {
		if (strParam.size()) {
			query.parse();
			res = query.store(*(const_cast<SQLQueryParms*>(&strParam)));
		}
		else {
			res = query.store();
		}
	}
	catch (std::exception e) {
		LOG_WARN("[{}] is error, detail:{}", e.what());
	}
	catch (...) {
		LOG_WARN("[{}] is unknow error");
	}

	if (query.errnum()) {
		LOG_WARN("sql execute falied, error msg:{}, error num:{}", query.error(), query.errnum());
	}
	return {query.errnum() == 0, res};
}

} /* town */