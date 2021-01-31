#include "MysqlOpt.h"
#include "MysqlAccessInfc.h"

namespace town
{

MysqlOpt::MysqlOpt()
{
}

MysqlOpt::~MysqlOpt()
{
}

void MysqlOpt::RegSqlExeHdl(MysqlAccessInfcPtr pMysqlHandle)
{
	m_pMysqlHandle = pMysqlHandle;
}

std::pair<bool, StoreQueryResult> MysqlOpt::ExecuteSql(const std::string& strSql, const SQLQueryParms& strParam)
{
	return m_pMysqlHandle->ExecuteSql(strSql, strParam);
}

}