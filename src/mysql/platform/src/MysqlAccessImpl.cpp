#include "MysqlAccessImpl.h"
#include "MysqlCommon.h"

namespace town {

bool MysqlAccessImpl::ConnectDb(const std::string& strDbName, const std::string& strIp, const std::string& strDbaName, const std::string& strPasswd, unsigned int uiPort)
{
	return m_MysqlCon.connect(strDbName.c_str(), strIp.c_str(), strDbaName.c_str(), strPasswd.c_str(), uiPort);
}

StoreQueryResult MysqlAccessImpl::ExecuteSql(const std::string& strSql, const SQLTypeAdapter& strParseSql)
{
	Query query(&m_MysqlCon, true, strSql.c_str());
	query.parse();
	if (strParseSql.size()) {
		return query.store(strParseSql);
	}
	return query.store();
}

} /* town */