#include "MysqlOptHandle.h"
#include "MysqlCommon.h"
#include "MysqlAccessInfc.h"

namespace town
{

MysqlOptHandle::MysqlOptHandle()
{

}

MysqlOptHandle::~MysqlOptHandle()
{
	m_mMysqlOptPtr.clear();
}

void MysqlOptHandle::Initialization()
{
	MysqlOptPtr pMysqlAddPtr = std::make_shared<MysqlAddOpt>();
	pMysqlAddPtr->RegSqlExeHdl(MysqlAccessInfc::GetInstance());
	m_mMysqlOptPtr[ADD] = pMysqlAddPtr;

	MysqlOptPtr pMysqlChangePtr = std::make_shared<MysqlChangeOpt>();
	pMysqlAddPtr->RegSqlExeHdl(MysqlAccessInfc::GetInstance());
	m_mMysqlOptPtr[CHANGE] = pMysqlAddPtr;

	MysqlOptPtr pMysqlDeletePtr = std::make_shared<MysqlDeleteOpt>();
	pMysqlAddPtr->RegSqlExeHdl(MysqlAccessInfc::GetInstance());
	m_mMysqlOptPtr[DELETE] = pMysqlAddPtr;

	MysqlOptPtr pMysqlSearchPtr = std::make_shared<MysqlSearchOpt>();
	pMysqlAddPtr->RegSqlExeHdl(MysqlAccessInfc::GetInstance());
	m_mMysqlOptPtr[SEARCH] = pMysqlAddPtr;
}

MysqlOptPtr MysqlOptHandle::GetOptHandle(MYSQL_OPT_TYPE eType)
{
	if (m_mMysqlOptPtr.find(eType) == m_mMysqlOptPtr.end()) {
		LOG_CRITICAL("eType:{} does not exist", eType);
		exit(1);
	}
	return m_mMysqlOptPtr[eType];
}

}