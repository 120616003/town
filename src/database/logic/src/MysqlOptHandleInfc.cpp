#include "MysqlOptHandleInfc.h"
#include "MysqlOptHandle.h"

namespace town
{

MysqlOptHandleInfcPtr MysqlOptHandleInfc::GetInstance()
{
	static MysqlOptHandlePtr impl = std::make_shared<MysqlOptHandle>();
	return impl;
}

MysqlOptHandleInfc::MysqlOptHandleInfc()
{
}

MysqlOptHandleInfc::~MysqlOptHandleInfc()
{
}

void MysqlOptHandleInfc::Initialization()
{
	MysqlOptHandle* impl = reinterpret_cast<MysqlOptHandle*>(this);
	impl->Initialization();
}

MysqlOptPtr MysqlOptHandleInfc::GetOptHandle(MYSQL_OPT_TYPE eType)
{
	MysqlOptHandle* impl = reinterpret_cast<MysqlOptHandle*>(this);
	return impl->GetOptHandle(eType);
}

}