#ifndef MYSQL_OPT_G
#define MYSQL_OPT_G

#include "town_config.h"
#include <string>
#include <memory>
#include <mysql++/mysql++.h>
using namespace mysqlpp;

namespace town
{

class MysqlAccessInfc;
using MysqlAccessInfcPtr = std::shared_ptr<MysqlAccessInfc>;

class MysqlOpt;
using MysqlOptPtr = std::shared_ptr<MysqlOpt>;

class MysqlOpt
{
public:
	MysqlOpt();
	virtual ~MysqlOpt();
	
	void RegSqlExeHdl(MysqlAccessInfcPtr pMysqlHandle);

public: // ADD 业务
	virtual void InitDB() {}
	virtual int RegisterUser(uint8_t* data, std::size_t len, std::string uuid) { return FAILED; }

protected:
	std::pair<bool, StoreQueryResult> ExecuteSql(const std::string& strSql, const SQLQueryParms& strParam = {});

private:
	MysqlAccessInfcPtr m_pMysqlHandle;
};

} /* town */

#endif /* MYSQL_OPT_G */