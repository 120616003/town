#include "MysqlAccessManage.h"
#include <thread>

namespace town
{

bool MysqlAccessManage::Initialization(const DB_INFO& db_info)
{
	for (int i = 0; i < db_info.db_cnt; i++) {
		MysqlImplPtr impl = std::make_unique<MysqlAccessImpl>();
		if (!impl->ConnectDb(db_info)) {
			LOG_WARN("data:{} base connect failed", i);
			return false;
		}

		auto mysql = std::thread(&MysqlAccessImpl::KeepAlive, impl.get()); // 数据库心跳线程
		std::string thread_name = "mysql_KA" + std::to_string(i);
		pthread_setname_np(mysql.native_handle(), thread_name.c_str());
		mysql.detach();

		m_qMysqlAccImPtr.push(std::move(impl));
	}
	return true;
}

std::pair<bool, StoreQueryResult> MysqlAccessManage::ExecuteSql(const std::string& strSql, const SQLQueryParms& strParam)
{
	MysqlImplPtr mysqlAccImPtr = PopMysqlHandle();
	std::pair<bool, StoreQueryResult> res = mysqlAccImPtr->ExecuteSql(strSql, strParam);
	PushMysqlHandle(mysqlAccImPtr);
	return res;
}

MysqlImplPtr MysqlAccessManage::PopMysqlHandle()
{
	while (m_qMysqlAccImPtr.empty() || m_lock.test_and_set(std::memory_order_acquire));
	MysqlImplPtr mysqlAccImPtr = std::move(m_qMysqlAccImPtr.front());
	m_qMysqlAccImPtr.pop();
	m_lock.clear(std::memory_order_release);
	return mysqlAccImPtr;
}

void MysqlAccessManage::PushMysqlHandle(MysqlImplPtr& mysqlAccImPtr)
{
	while (m_lock.test_and_set(std::memory_order_acquire));
	m_qMysqlAccImPtr.push(std::move(mysqlAccImPtr));
	m_lock.clear(std::memory_order_release);
}

}