/*******************************************************
 * @brief: Mysql访问模块
 * @Copyright: Copyleft
 * @license: GPL
 * @birth: created by yan on 2020-12-8
 * @version: V0.0.1
 * @revision: last revised by yan on 2020-12-8
 *******************************************************/

#ifndef MYSQL_ACCESS_IMPL_H
#define MYSQL_ACCESS_IMPL_H

#include "MysqlAccess.h"
#include "MysqlCommon.h"
#include <mysql/mysql.h>
#include <memory>
#include <string>

namespace town {

class MysqlAccessImpl : public MysqlAccess
{
public:
	MysqlAccessImpl();
	~MysqlAccessImpl();
	int Initialization(const std::string& strIp, const std::string& strName, const std::string& strPasswd, const std::string& strDBName, int iPort);
	int ExecuteSql(const std::string& strSql);
	template <typename T>
	int ExecuteSql(const std::string& strSql, std::vector<std::pair<T, std::string>>& vParam);

private:
	MYSQL* m_pSqlCon;
	MYSQL_STMT* m_pSqlStmt;
};

} /* town */

#endif /* MYSQL_ACCESS_IMPL_H */