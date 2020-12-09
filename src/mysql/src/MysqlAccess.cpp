/*******************************************************
 * @brief: Mysql访问模块
 * @Copyright: Copyleft
 * @license: GPL
 * @birth: created by yan on 2020-12-8
 * @version: V0.0.1
 * @revision: last revised by yan on 2020-12-8
 *******************************************************/

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

int MysqlAccess::Initialization(const std::string& strName, const std::string& strPasswd, const std::string& strDBName, int iPort)
{
	MysqlAccessImpl* impl = reinterpret_cast<MysqlAccessImpl*>(this);
	return impl->Initialization(strName, strPasswd, strDBName, iPort);
}

} /* town */