#include "MysqlInterface.h"
#include "MysqlAccessManage.h"
#include <memory>

namespace town
{

MysqlInfcPtr MysqlInterface::GetInstance()
{
	static MysqlManagePtr impl = std::make_shared<MysqlAccessManage>();
	return impl;
}

bool MysqlInterface::Initialization(int iConNum, const std::string& strDbName, const std::string& strIp, const std::string& strDbaName, const std::string& strPasswd, unsigned int uiPort)
{
	MysqlAccessManage* impl = reinterpret_cast<MysqlAccessManage*>(this);
	return impl->Initialization(iConNum, strDbName, strIp, strDbaName, strPasswd, uiPort);
}

StoreQueryResult MysqlInterface::ExecuteSql(const std::string& strSql, const SQLTypeAdapter& strParseSql)
{
	MysqlAccessManage* impl = reinterpret_cast<MysqlAccessManage*>(this);
	return impl->ExecuteSql(strSql, strParseSql);
}

}