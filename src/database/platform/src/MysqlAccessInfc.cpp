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

bool MysqlAccessInfc::Initialization(const DB_INFO& db_info)
{
	MysqlAccessManage* impl = reinterpret_cast<MysqlAccessManage*>(this);
	return impl->Initialization(db_info);
}

std::pair<bool, StoreQueryResult> MysqlAccessInfc::ExecuteSql(const std::string& strSql, const SQLQueryParms& strParam)
{
	MysqlAccessManage* impl = reinterpret_cast<MysqlAccessManage*>(this);
	return impl->ExecuteSql(strSql, strParam);
}

}