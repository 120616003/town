#include "MysqlOpt.h"
#include "MysqlAccessInfc.h"

namespace town
{

MysqlOpt::MysqlOpt()
{
}

MysqlOpt::~MysqlOpt()
{
}

void MysqlOpt::RegSqlExeHdl(MysqlAccessInfcPtr pMysqlHandle)
{
	m_pMysqlHandle = pMysqlHandle;
}

std::pair<bool, StoreQueryResult> MysqlOpt::ExecuteSql(const std::string& strSql, const SQLQueryParms& strParam)
{
	return m_pMysqlHandle->ExecuteSql(strSql, strParam);
}

common_enum::ERROR_CODE MysqlOpt::ConvertErrType(common_enum::ACC_TYPE eType, bool bExist)
{
	common_enum::ERROR_CODE err_type;
	if (bExist) {
		if (common_enum::ACC_EMAIL == eType) {
			err_type = common_enum::ERR_EMAIL_EXIST;
		}
		else if (common_enum::ACC_PHONE == eType) {
			err_type = common_enum::ERR_PHONE_EXIST;
		}
		else if (common_enum::ACC_NAME == eType) {
			err_type = common_enum::ERR_NAME_EXIST;
		}
		else {
			err_type = common_enum::ERR_ACC_TYPE_NO_EXIST;	
		}
	}
	else {
		if (common_enum::ACC_EMAIL == eType) {
			err_type = common_enum::ERR_EMAIL_NO_EXIST;
		}
		else if (common_enum::ACC_PHONE == eType) {
			err_type = common_enum::ERR_PHONE_NO_EXIST;
		}
		else if (common_enum::ACC_NAME == eType) {
			err_type = common_enum::ERR_NAME_NO_EXIST;
		}
		else {
			err_type = common_enum::ERR_ACC_TYPE_NO_EXIST;	
		}
	}
	return err_type;
}

}