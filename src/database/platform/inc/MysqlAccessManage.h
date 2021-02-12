#ifndef MYSQL_ACCESS_MANAGE_H
#define MYSQL_ACCESS_MANAGE_H

#include "MysqlCommon.h"
#include "MysqlAccessImpl.h"

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

	bool Initialization(const DB_INFO& db_info);
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