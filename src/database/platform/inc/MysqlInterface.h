#ifndef MYSQL_INTERFACE_H
#define MYSQL_INTERFACE_H

#include <mysql++/mysql++.h>
#include <string>
#include <memory>
using namespace mysqlpp;

namespace town
{

class MysqlInterface;
using MysqlInfcPtr = std::shared_ptr<MysqlInterface>;

class MysqlInterface
{
public:
	static MysqlInfcPtr GetInstance();

	bool Initialization(int iConNum, const std::string& strDbName, const std::string& strIp, const std::string& strDbaName, const std::string& strPasswd, unsigned int uiPort);
	StoreQueryResult ExecuteSql(const std::string& strSql, const SQLTypeAdapter& strParseSql = {});

protected:
	MysqlInterface() {}
	~MysqlInterface() {}

private:
	MysqlInterface(const MysqlInterface&) = delete;
	MysqlInterface& operator = (const MysqlInterface&) = delete;
};

}

#endif /* MYSQL_INTERFACE_H */