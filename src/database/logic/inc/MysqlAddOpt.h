#ifndef MYSQL_ADD_OPT_H
#define MYSQL_ADD_OPT_H

#include "MysqlOpt.h"

namespace town
{

class MysqlAddOpt : public MysqlOpt
{
public:
	MysqlAddOpt();
	~MysqlAddOpt();

public: // 业务
	void InitDB() override;
	std::string RegisterAcc(uint8_t* pData, std::size_t iLen) override;
	std::string LoginAcc(uint8_t* pData, std::size_t iLen, std::string& strUuid) override;

private:
	bool MailboxFormatValidation(std::string strEmail);
	bool PhoneFormatValidation(std::string strPhone);
	bool NameFormatValidation(std::string strName);
	bool PasswdFormatValidation(std::string strPasswd);
};

}

#endif /* MYSQL_ADD_OPT_H */