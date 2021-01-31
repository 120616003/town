#ifndef MYSQL_INFC_H
#define MYSQL_INFC_H

#include <string>
#include <memory>
#include <mysql++/mysql++.h>
using namespace mysqlpp;

namespace town
{

class MysqlAccessInfc;
using MysqlAccessInfcPtr = std::shared_ptr<MysqlAccessInfc>;

class MysqlAccessInfc
{
public:
	static MysqlAccessInfcPtr GetInstance();

	bool Initialization(int iConNum, const std::string& strDbName, const std::string& strIp, const std::string& strDbaName, const std::string& strPasswd, unsigned int uiPort);
	std::pair<bool, StoreQueryResult> ExecuteSql(const std::string& strSql, const SQLQueryParms& strParam = {});

protected:
	MysqlAccessInfc() {}
	~MysqlAccessInfc() {}

private:
	MysqlAccessInfc(const MysqlAccessInfc&) = delete;
	MysqlAccessInfc& operator = (const MysqlAccessInfc&) = delete;
};

}

#endif /* MYSQL_INFC_H */