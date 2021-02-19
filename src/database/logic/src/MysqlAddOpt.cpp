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

std::string MysqlAddOpt::RegisterAcc(uint8_t* pData, std::size_t iLen)
{
	acc_register ar, ar_res;
	if (!ar.ParseFromArray(pData, iLen)) {
		LOG_ERROR("protobuf parse failed");
		ar_res.set_err_type(common_enum::ERR_PROTOBUF_PARSE);
		return ar_res.SerializeAsString();
	}

	SQLQueryParms strParms;
	if (ar.type() == common_enum::ACC_EMAIL) {
		// 验证邮箱格式是否正确
		if (!MailboxFormatValidation(ar.email())) {
			LOG_ERROR("email type error:{}", ar.email());
			ar_res.set_err_type(common_enum::ERR_EMAI_TYPE);
			return ar_res.SerializeAsString();
		}
		strParms << "email" << ar.email();
	}
	else if (ar.type() == common_enum::ACC_PHONE) {
		// 验证手机号格式是否正确
		if (!PhoneFormatValidation(ar.phone())) {
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

	// 检测当前账号是否存在
	std::string sql = R"(select id from user where %0:wheref = %1q:what)";
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
	if (!PasswdFormatValidation(ar.passwd())) {
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

std::string MysqlAddOpt::LoginAcc(uint8_t* pData, std::size_t iLen, std::string& strUuid)
{
	acc_login al, al_res;
	if (!al.ParseFromArray(pData, iLen)) {
		LOG_ERROR("protobuf parse failed");
		al_res.set_err_type(common_enum::ERR_PROTOBUF_PARSE);
		return al_res.SerializeAsString();
	}

	SQLQueryParms strParms;
	if (al.type() == common_enum::ACC_EMAIL) {
		// 验证邮箱格式是否正确
		if (!MailboxFormatValidation(al.email())) {
			LOG_ERROR("email type error:{}", al.email());
			al_res.set_err_type(common_enum::ERR_EMAI_TYPE);
			return al_res.SerializeAsString();
		}
		strParms << "email" << al.email();
	}
	else if (al.type() == common_enum::ACC_PHONE) {
		// 验证手机号格式是否正确
		if (!PhoneFormatValidation(al.phone())) {
			LOG_ERROR("phone type error:{}", al.phone());
			al_res.set_err_type(common_enum::ERR_PHONE_TYPE);
			return al_res.SerializeAsString();
		}
		strParms << "phone" << al.phone();
	}
	else if (al.type() == common_enum::ACC_NAME) {
		// 验证手机号格式是否正确
		if (!PhoneFormatValidation(al.name())) {
			LOG_ERROR("name type error:{}", al.name());
			al_res.set_err_type(common_enum::ERR_PHONE_TYPE);
			return al_res.SerializeAsString();
		}
		strParms << "name" << al.name();
	}
	else {
		LOG_ERROR("register user type error, type:{}", al.type());
		al_res.set_err_type(common_enum::ERR_ACC_TYPE_NO_EXIST);
		return al_res.SerializeAsString();
	}

	// 检测当前账号是否存
	std::string sql = R"(select id from user where %0:wheref = %1q:what)";
	std::pair<bool, StoreQueryResult> res = ExecuteSql(sql, strParms);
	if (!res.first) {
		LOG_ERROR("execute sql error");
		al_res.set_err_type(common_enum::ERR_EXECUTE_SQL);
		return al_res.SerializeAsString();
	}
	if (!res.second.size()) {
		LOG_DEBUG("acc no exists");
		al_res.set_err_type(ConvertErrType(al.type(), false));
		return al_res.SerializeAsString();
	}

	// 验证密码格式是否正确
	if (!PasswdFormatValidation(al.passwd())) {
		LOG_DEBUG("passwd type error:{}", al.passwd());
		al_res.set_err_type(common_enum::ERR_PASSWD_TYPE);
		return al_res.SerializeAsString();
	}

	sql = R"(select uuid from user where %0:wheref = %1q:what and %2:wheref = %3q:what)";
	strParms << "passwd" << al.passwd();
	res = ExecuteSql(sql, strParms);
	if (!res.first) {
		LOG_ERROR("execute sql error");
		al_res.set_err_type(common_enum::ERR_EXECUTE_SQL);
		return al_res.SerializeAsString();
	}
	if (!res.second.size()) {
		LOG_DEBUG("passwd error:{}", al.passwd());
		al_res.set_err_type(common_enum::ERR_PASSWD);
		return al_res.SerializeAsString();
	}

	al_res.set_err_type(common_enum::ERR_NONE);
	al_res.set_uuid(res.second[0]["uuid"]);
	strUuid = res.second[0]["uuid"].c_str();
	return al_res.SerializeAsString();
}

bool MysqlAddOpt::MailboxFormatValidation(std::string strEmail)
{
	std::wstring str = Booster::StringToWString(strEmail);
	std::wregex reg(L"^[A-Za-z0-9\u4e00-\u9fa5]{1,200}@[a-zA-Z0-9_-]{1,20}(\\.[a-zA-Z0-9_-]{1,5}){1,7}$");
	return std::regex_match(str, reg);
}

bool MysqlAddOpt::PhoneFormatValidation(std::string strPhone)
{
	std::wstring str = Booster::StringToWString(strPhone);
	std::wregex reg(L"^[0-9]{11}$");
	return std::regex_match(str, reg);
}

bool MysqlAddOpt::NameFormatValidation(std::string strName)
{
	std::wstring str = Booster::StringToWString(strName);
	std::wregex reg(L"^[\\w]{2,10}");
	return std::regex_match(str, reg);
}

bool MysqlAddOpt::PasswdFormatValidation(std::string strPasswd)
{
	std::wstring str = Booster::StringToWString(strPasswd);
	std::wregex reg(L"^[A-Za-z0-9\\+\\-\\*/_@\\$]{8,20}$");
	return std::regex_match(str, reg);
}

}