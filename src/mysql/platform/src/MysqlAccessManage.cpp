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
	m_vupMysqlAccIm.resize(iConNum);
	for (int i = 0; i < iConNum; i++) {
		if (!m_vupMysqlAccIm[i]->ConnectDb(strDbName.c_str(), strIp.c_str(), strDbaName.c_str(), strPasswd.c_str(), uiPort)) {
			LOG_WARN("data:{} base connect failed", i);
			return false;
		}
	}
	return true;
}

// StoreQueryResult MysqlAccessManage::ExecuteSql(const std::string& strSql, const SQLTypeAdapter& strParseSql)
// {

// }

}