#ifndef MYSQL_ACCESS_MANAGE_H
#define MYSQL_ACCESS_MANAGE_H

#include "MysqlCommon.h"
#include "MysqlAccessImpl.h"
#include "MysqlAccessInfc.h"

namespace town
{

class MysqlAccessManage;
using MysqlManagePtr = std::shared_ptr<MysqlAccessManage>;
using MysqlImplPtr = std::unique_ptr<MysqlAccessImpl>;

class MysqlAccessManage : public MysqlAccessInfc
{
public:
	MysqlAccessManage() {}
	~MysqlAccessManage() {}

	bool Initialization(int iConNum, const std::string& strDbName, const std::string& strIp, const std::string& strDbaName, const std::string& strPasswd, unsigned int uiPort);
	std::pair<bool, StoreQueryResult> ExecuteSql(const std::string& strSql, const SQLQueryParms& strParam);

private:
	MysqlImplPtr PopMysqlHandle();
	void PushMysqlHandle(MysqlImplPtr& mysqlAccImPtr);

private:
	MysqlAccessManage(const MysqlAccessManage&) = delete;
	MysqlAccessManage& operator = (const MysqlAccessManage&) = delete;

private:
	std::queue<MysqlImplPtr> m_qMysqlAccImPtr;
	std::atomic_flag m_lock = ATOMIC_FLAG_INIT;
};

}

#endif /* MYSQL_ACCESS_MANAGE_H */