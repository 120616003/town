#include "MysqlAccessInfc.h"
#include "MysqlAccessManage.h"
#include <memory>

namespace town
{

MysqlAccessInfcPtr MysqlAccessInfc::GetInstance()
{
	static MysqlManagePtr impl = std::make_shared<MysqlAccessManage>();
	return impl;
}

bool MysqlAccessInfc::Initialization(int iConNum, const std::string& strDbName, const std::string& strIp, const std::string& strDbaName, const std::string& strPasswd, unsigned int uiPort)
{
	MysqlAccessManage* impl = reinterpret_cast<MysqlAccessManage*>(this);
	return impl->Initialization(iConNum, strDbName, strIp, strDbaName, strPasswd, uiPort);
}

std::pair<bool, StoreQueryResult> MysqlAccessInfc::ExecuteSql(const std::string& strSql, const SQLQueryParms& strParam)
{
	MysqlAccessManage* impl = reinterpret_cast<MysqlAccessManage*>(this);
	return impl->ExecuteSql(strSql, strParam);
}

}