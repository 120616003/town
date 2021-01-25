#ifndef MYSQL_ACCESS_MANAGE_H
#define MYSQL_ACCESS_MANAGE_H

#include "MysqlCommon.h"
#include "MysqlAccessImpl.h"

namespace town
{

class MysqlAccessManage
{
public:
	MysqlAccessManage* GetInstance();

    bool Initialization(int iConNum, const std::string& strDbName, const std::string& strIp, const std::string& strDbaName, const std::string& strPasswd, unsigned int uiPort = 0);
    StoreQueryResult ExecuteSql(const std::string& strSql, const SQLTypeAdapter& strParseSql = {});

private:
	MysqlAccessManage();
	~MysqlAccessManage();
	MysqlAccessManage(const MysqlAccessManage&) = delete;
	MysqlAccessManage operator = (const MysqlAccessManage&) = delete;

private:
	std::vector<std::unique_ptr<MysqlAccessImpl>> m_vupMysqlAccIm;
};

}

#endif /* MYSQL_ACCESS_MANAGE_H */