#ifndef MYSQL_ACCESS_IMPL_H
#define MYSQL_ACCESS_IMPL_H

#include "MysqlAccessInfc.h"

namespace town {

class MysqlAccessImpl
{
public:
    MysqlAccessImpl() {}
    ~MysqlAccessImpl() {}

    bool ConnectDb(const DB_INFO& db_info);
    std::pair<bool, StoreQueryResult> ExecuteSql(const std::string& strSql, const SQLQueryParms& strParam);
    void KeepAlive();

private:
    Connection m_MysqlCon;
    DB_INFO m_db_info;
};

} /* town */

#endif /* MYSQL_ACCESS_IMPL_H */