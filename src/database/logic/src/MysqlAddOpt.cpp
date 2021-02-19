#include "MysqlAddOpt.h"
#include "MysqlCommon.h"
#include "Booster.hpp"
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

std::string MysqlAddOpt::RegisterUser(uint8_t* data, std::size_t len)
{
	acc_register ar, ar_res;
	if (!ar.ParseFromArray(data, len)) {
		LOG_ERROR("protobuf parse failed");
		ar_res.set_err_type(common_enum::ERR_PROTOBUF_PARSE);
		return ar_res.SerializeAsString();
	}

	SQLQueryParms strParms;
	// 检测当前账号是否存在
	std::string sql = R"(select id from user where %0:wheref = %1q:what)";
	if (ar.type() == common_enum::ACC_EMAIL) {
		// 验证邮箱格式是否正确
		std::wstring str = Booster::StringToWString(ar.email());
		std::wregex reg(L"^[A-Za-z0-9\u4e00-\u9fa5]{1,200}@[a-zA-Z0-9_-]{1,20}(\\.[a-zA-Z0-9_-]{1,5}){1,7}$");
		if (!std::regex_match(str, reg)) {
			LOG_ERROR("email type error:{}", ar.email());
			ar_res.set_err_type(common_enum::ERR_EMAI_TYPE);
			return ar_res.SerializeAsString();
		}
		strParms << "email" << ar.email();
	}
	else if (ar.type() == common_enum::ACC_PHONE) {
		// 验证手机号格式是否正确
		std::wstring str = Booster::StringToWString(ar.phone());
		std::wregex reg(L"^[0-9]{11}$");
		if (!std::regex_match(str, reg)) {
			LOG_ERROR("phone type error:{}", ar.phone());
			ar_res.set_err_type(common_enum::ERR_PHONE_TYPE);
			return ar_res.SerializeAsString();
		}
		strParms << "phone" << ar.phone();
	}
	else {
		LOG_ERROR("register user type error, type:{}", ar.type());
		ar_res.set_err_type(common_enum::ERR_ACC_TYPE_NO_EXIST);
		return ar_res.SerializeAsString();
	}

	std::pair<bool, StoreQueryResult> res = ExecuteSql(sql, strParms);
	if (!res.first) {
		LOG_ERROR("execute sql error");
		ar_res.set_err_type(common_enum::ERR_EXECUTE_SQL);
		return ar_res.SerializeAsString();
	}
	if (res.second.size()) {
		LOG_DEBUG("acc exists, size:{}, id:{}", res.second.size(), res.second[0]["id"]);
		ar_res.set_err_type(ConvertErrType(ar.type(), true));
		return ar_res.SerializeAsString();
	}

	// 验证密码格式是否正确
	std::wregex reg(L"^[A-Za-z0-9\\+\\-\\*/_@\\$]{8,20}$");
	std::wstring str = Booster::StringToWString(ar.passwd());
	if (!std::regex_match(str, reg)) {
		LOG_ERROR("passwd type error:{}", ar.passwd());
		ar_res.set_err_type(common_enum::ERR_PASSWD_TYPE);
		return ar_res.SerializeAsString();
	}
	
	sql = R"(
		insert into user (uuid, time, email, phone, passwd) 
		values (%0q:uuid, NULL, %1q:email, %2q:phone, %3q:passwd)
	)";
	strParms.clear();
	strParms << Booster::GetUUID() << ar.email() << ar.phone() << ar.passwd();
	res = ExecuteSql(sql, strParms);
	if (!res.first) {
		LOG_ERROR("execute sql error");
		ar_res.set_err_type(common_enum::ERR_EXECUTE_SQL);
		return ar_res.SerializeAsString();
	}

	ar_res.set_err_type(common_enum::ERR_NONE);
	return ar_res.SerializeAsString();
}

}