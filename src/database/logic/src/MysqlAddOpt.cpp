#include "MysqlAddOpt.h"
#include "MysqlCommon.h"
#include <regex>

namespace town
{

MysqlAddOpt::MysqlAddOpt()
{
}

MysqlAddOpt::~MysqlAddOpt()
{
}

void MysqlAddOpt::InitDB()
{
	ExecuteSql(create_user_table);
	ExecuteSql(create_user_info_table);
}

int MysqlAddOpt::RegisterUser(uint8_t* data, std::size_t len, std::string uuid)
{
	acc_register ar;
	ar.ParseFromArray(data, len);

	SQLQueryParms strParms;
	std::string sql = R"(select id from user where %0:wheref = %1q:what)";
	if (ar.type() == common_enum::ACC_EMAIL) {
		strParms << "acc_email" << ar.email();
	}
	else if (ar.type() == common_enum::ACC_PHONE) {
		strParms << "acc_phone" << ar.phone();
	}
	else if (ar.type() == common_enum::ACC_NAME) {
		strParms << "acc_name" << ar.name();
	}
	else {
		LOG_ERROR("register user type error, type:{}", ar.type());
		return FAILED;
	}

	std::pair<bool, StoreQueryResult> res = ExecuteSql(sql, strParms);
	if (!res.first) {
		LOG_WARN("sql error");
		return FAILED;
	}
	if (res.second.size()) {
		LOG_WARN("acc exists, size:{}, id:{}", res.second.size(), res.second[0]["id"]);
		return FAILED;
	}
	
	sql = R"(
		insert into user (uuid, time, acc_email, acc_phone, acc_name, password) 
		values (%0q:uuid, NULL, %1q:acc_email, %2q:acc_phone, %3q:acc_name, %4q:password)
	)";
	strParms.clear();
	strParms << uuid << ar.email() << ar.phone() << ar.name() << ar.passwd();
	res = ExecuteSql(sql, strParms);
	if (!res.first) {
		LOG_WARN("sql error");
		return FAILED;
	}

	return SUCCESS;
}

}