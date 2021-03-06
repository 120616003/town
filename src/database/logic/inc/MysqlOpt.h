#ifndef MYSQL_OPT_G
#define MYSQL_OPT_G

#include "town_config.h"
#include "user.pb.h"
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
	virtual std::string RegisterAcc(uint8_t* pData, std::size_t iLen) { return ""; }
	virtual std::string LoginAcc(uint8_t* pData, std::size_t iLen, std::string& strUuid) { return ""; }

protected:
	std::pair<bool, StoreQueryResult> ExecuteSql(const std::string& strSql, const SQLQueryParms& strParam = {});
	common_enum::ERROR_CODE ConvertErrType(common_enum::ACC_TYPE eType, bool bExist);

private:
	MysqlAccessInfcPtr m_pMysqlHandle;
};

} /* town */

#endif /* MYSQL_OPT_G */