#ifndef MYSQL_ACCESS_IMPL_H
#define MYSQL_ACCESS_IMPL_H

#include <mysql++/mysql++.h>
#include <string>
using namespace mysqlpp;

namespace town {

class MysqlAccessImpl
{
public:
    MysqlAccessImpl() {}
    ~MysqlAccessImpl() {}

    bool ConnectDb(const std::string& strDbName, const std::string& strIp, const std::string& strDbaName, const std::string& strPasswd, unsigned int uiPort = 0);
    std::pair<bool, StoreQueryResult> ExecuteSql(const std::string& strSql, const SQLQueryParms& strParam);

private:
    Connection m_MysqlCon;

};

} /* town */

#endif /* MYSQL_ACCESS_IMPL_H */