#ifndef MYSQL_OPT_G
#define MYSQL_OPT_G

#include "MysqlCommon.h"
#include "MysqlAccessManage.h"

namespace town
{

class MysqlOpt;
using MysqlOptPtr = std::shared_ptr<MysqlOpt>;

class MysqlOpt
{
public:
	MysqlOpt() {}
	virtual ~MysqlOpt() {}
	
	void RegSqlExeHdl(MysqlInfcPtr pMysqlHandle) { m_pMysqlHandle = pMysqlHandle; }

protected:
	StoreQueryResult ExecuteSql(const std::string& strSql, const SQLTypeAdapter& strParseSql)
	{
		return m_pMysqlHandle->ExecuteSql(strSql, strParseSql);
	}

private:
	MysqlInfcPtr m_pMysqlHandle;
};

} /* town */

#endif /* MYSQL_OPT_G */