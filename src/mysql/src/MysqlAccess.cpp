#include "MysqlAccess.h"
#include "MysqlAccessImpl.h"

namespace town {

MysqlAccess::MysqlAccess()
{
}

MysqlAccess::~MysqlAccess()
{
}

MysqlAccess* MysqlAccess::GetInstance()
{
	static MysqlAccessImpl ins;
	return &ins;
}

int MysqlAccess::Initialization(const std::string& strIp, const std::string& strName, const std::string& strPasswd, const std::string& strDBName, int iPort)
{
	MysqlAccessImpl* impl = reinterpret_cast<MysqlAccessImpl*>(this);
	return impl->Initialization(strIp, strName, strPasswd, strDBName, iPort);
}

int MysqlAccess::ExecuteSql(const std::string& strSql)
{
	MysqlAccessImpl* impl = reinterpret_cast<MysqlAccessImpl*>(this);
	return impl->ExecuteSql(strSql);
}

template <typename T>
int MysqlAccess::ExecuteSql(const std::string& strSql, std::vector<std::pair<T, std::string>>& vParam)
{
	MysqlAccessImpl* impl = reinterpret_cast<MysqlAccessImpl*>(this);
	return impl->ExecuteSql(strSql, vParam);
}

} /* town */