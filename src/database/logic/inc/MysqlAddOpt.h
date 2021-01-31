#ifndef MYSQL_ADD_OPT_H
#define MYSQL_ADD_OPT_H

#include "MysqlOpt.h"
#include "user.pb.h"

namespace town
{

class MysqlAddOpt : public MysqlOpt
{
public:
	MysqlAddOpt();
	~MysqlAddOpt();

public: // 业务
	void InitDB() override;
	int RegisterUser(uint8_t* data, std::size_t len, std::string uuid) override;

private:

};

}

#endif /* MYSQL_ADD_OPT_H */