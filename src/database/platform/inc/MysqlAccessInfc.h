#ifndef MYSQL_INFC_H
#define MYSQL_INFC_H

#include <string>
#include <memory>
#include <mysql++/mysql++.h>
using namespace mysqlpp;

namespace town
{

struct DB_INFO
{
	int db_cnt = 0;
	std::string ip;
	std::string dba;
	std::string dba_passwd;
	std::string db;
	unsigned int db_port = 0;
};

class MysqlAccessInfc;
using MysqlAccessInfcPtr = std::shared_ptr<MysqlAccessInfc>;

class MysqlAccessInfc
{
public:
	static MysqlAccessInfcPtr GetInstance();

	bool Initialization(const DB_INFO& db_info);
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