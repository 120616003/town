#ifndef MYSQL_ACCESS_MANAGE_H
#define MYSQL_ACCESS_MANAGE_H

#include "MysqlCommon.h"
#include "MysqlAccessImpl.h"
#include <atomic>

namespace town
{

using MysqlHandlePtr = std::unique_ptr<MysqlAccessImpl>;

class MysqlAccessManage
{
public:
	MysqlAccessManage* GetInstance();

    bool Initialization(int iConNum, const std::string& strDbName, const std::string& strIp, const std::string& strDbaName, const std::string& strPasswd, unsigned int uiPort = 0);
    StoreQueryResult ExecuteSql(const std::string& strSql, const SQLTypeAdapter& strParseSql = {});

private:
	MysqlHandlePtr PopMysqlHandle();
	void PushMysqlHandle(MysqlHandlePtr& mysqlAccImPtr);

private:
	MysqlAccessManage();
	~MysqlAccessManage();
	MysqlAccessManage(const MysqlAccessManage&) = delete;
	MysqlAccessManage operator = (const MysqlAccessManage&) = delete;

private:
	std::queue<MysqlHandlePtr> m_qMysqlAccImPtr;
	std::atomic_flag m_lock = ATOMIC_FLAG_INIT;
};

}

#endif /* MYSQL_ACCESS_MANAGE_H */