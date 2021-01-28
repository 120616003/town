#include "MysqlAccessManage.h"

namespace town
{

MysqlAccessManage* MysqlAccessManage::GetInstance()
{
	static MysqlAccessManage mysqlManage;
	return &mysqlManage;
}

MysqlAccessManage::MysqlAccessManage()
{
}

MysqlAccessManage::~MysqlAccessManage()
{
}

bool MysqlAccessManage::Initialization(int iConNum, const std::string& strDbName, const std::string& strIp, const std::string& strDbaName, const std::string& strPasswd, unsigned int uiPort)
{
	for (int i = 0; i < iConNum; i++) {
		MysqlHandlePtr impl = std::make_unique<MysqlAccessImpl>();
		if (!impl->ConnectDb(strDbName.c_str(), strIp.c_str(), strDbaName.c_str(), strPasswd.c_str(), uiPort)) {
			LOG_WARN("data:{} base connect failed", i);
			return false;
		}
		m_qMysqlAccImPtr.push(std::move(impl));
	}
	return true;
}

StoreQueryResult MysqlAccessManage::ExecuteSql(const std::string& strSql, const SQLTypeAdapter& strParseSql)
{
	MysqlHandlePtr mysqlAccImPtr = PopMysqlHandle();
	StoreQueryResult res = mysqlAccImPtr->ExecuteSql(strSql, strParseSql);
	PushMysqlHandle(mysqlAccImPtr);
	return StoreQueryResult();
}

MysqlHandlePtr MysqlAccessManage::PopMysqlHandle()
{
	while (m_lock.test_and_set(std::memory_order_acquire));
	MysqlHandlePtr mysqlAccImPtr = std::move(m_qMysqlAccImPtr.front());
	m_qMysqlAccImPtr.pop();
	m_lock.clear(std::memory_order_release);
	return mysqlAccImPtr;
}

void MysqlAccessManage::PushMysqlHandle(MysqlHandlePtr& mysqlAccImPtr)
{
	while (m_lock.test_and_set(std::memory_order_acquire));
	m_qMysqlAccImPtr.push(std::move(mysqlAccImPtr));
	m_lock.clear(std::memory_order_release);
}

}