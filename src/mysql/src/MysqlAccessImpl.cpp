/*******************************************************
 * @brief: Mysql访问模块
 * @Copyright: Copyleft
 * @license: GPL
 * @birth: created by yan on 2020-12-8
 * @version: V0.0.1
 * @revision: last revised by yan on 2020-12-8
 *******************************************************/

#include "MysqlAccessImpl.h"
#include "MysqlCommon.h"

namespace town {

MysqlAccessImpl::MysqlAccessImpl()
{
	m_SqlConPtr = std::make_shared<MYSQL>();
}

MysqlAccessImpl::~MysqlAccessImpl()
{
}

int MysqlAccessImpl::Initialization(const std::string& strName, const std::string& strPasswd, const std::string& strDBName, int iPort)
{
	mysql_init(m_SqlConPtr.get());
	if(!mysql_real_connect(m_SqlConPtr.get(), "localhost", strName.c_str(), strPasswd.c_str(), strDBName.c_str(), iPort, NULL, 0)) {
		LOG_ERROR("open database:{} failed", strDBName);
		return FAILED;
	}
	LOG_DEBUG("open database:{} success", strDBName);

	m_SqlStmtPtr.reset(mysql_stmt_init(m_SqlConPtr.get()));
	if (!m_SqlStmtPtr) {
		LOG_ERROR("init failed m_SqlStmtPtr is nullptr", strDBName);
		return FAILED;
	}
	LOG_INFO("initialization success");

	return SUCCESS;
}

int MysqlAccessImpl::ExecuteSql(const std::string& strSql)
{
	if (mysql_query(m_SqlConPtr.get(), strSql.c_str())) {
		std::string strErrorMessage = mysql_error(m_SqlConPtr.get());
		LOG_ERROR("execute sql:{}, error msg:{}", strSql, strErrorMessage);
		return FAILED;
	}

	// MYSQL_RES *result = mysql_store_result(mysql); //获取离线结果，数据存放到程序内存中
	// MYSQL_ROW row;
	// while (row=mysql_fetch_row(result))//获取一行数据的结果；
	// {
	// 	char *id=row[0];//第0列的值
	// 	char *username=row[1];//第1列的值
	// 	printf("id=%s,name=%s\n",id,username);
	// }

	// mysql_free_result(result); //释放掉内存
	return 0;
}

} /* town */