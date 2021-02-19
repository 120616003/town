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
	std::string RegisterUser(uint8_t* data, std::size_t len) override;

private:

};

}

#endif /* MYSQL_ADD_OPT_H */