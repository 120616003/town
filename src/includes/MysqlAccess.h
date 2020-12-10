/*******************************************************
 * @brief: Mysql访问模块
 * @Copyright: Copyleft
 * @license: GPL
 * @birth: created by yan on 2020-12-8
 * @version: V0.0.1
 * @revision: last revised by yan on 2020-12-8
 *******************************************************/

#ifndef MYSQL_ACCESS_H
#define MYSQL_ACCESS_H

#include <string>

namespace town {

class MysqlAccess
{
public:
	static MysqlAccess* GetInstance();
	int Initialization(const std::string& strName, const std::string& strPasswd, const std::string& strDBName, int iPort);
	int ExecuteSql(const std::string& strSql);

protected:
	MysqlAccess();
	~MysqlAccess();
};

} /* town */

#endif /* MYSQL_ACCESS_H */