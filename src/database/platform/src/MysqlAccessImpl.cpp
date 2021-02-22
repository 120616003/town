#include "MysqlAccessImpl.h"
#include "MysqlCommon.h"

namespace town {

bool MysqlAccessImpl::ConnectDb(const DB_INFO& db_info)
{
	m_db_info = db_info;
	return m_MysqlCon.connect(m_db_info.db.c_str(), m_db_info.ip.c_str(), m_db_info.dba.c_str(), m_db_info.dba_passwd.c_str(), m_db_info.db_port);
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
	catch (std::exception& e) {
		LOG_ERROR("[{}] is error, detail:{}", e.what());
	}
	catch (...) {
		LOG_ERROR("[{}] is unknow error");
	}

	if (query.errnum()) {
		LOG_ERROR("sql execute falied, error msg:{}, error num:{}", query.error(), query.errnum());
	}
	return {query.errnum() == 0, res};
}

void MysqlAccessImpl::KeepAlive()
{
	while(true) {
		if (!m_MysqlCon.ping()) {
			m_MysqlCon.connect(m_db_info.db.c_str(), m_db_info.ip.c_str(), m_db_info.dba.c_str(), m_db_info.dba_passwd.c_str(), m_db_info.db_port);
		}
		Booster::Timer(3600, 0, 0);
	}
}

} /* town */