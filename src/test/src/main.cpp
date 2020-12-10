#include <iostream>
#include <unistd.h>

#include "MysqlAccess.h"
#include "common.h"
using namespace town;

const std::string CREATE_USER_TABLE = R"(create table if not exists user (
	id int auto_increment primary key not null,
	account_number int not null,
	password varchar(20)
);)";

int main()
{
	auto mysql = MysqlAccess::GetInstance();
	mysql->Initialization("town", "1", "town", 1);
	// mysql->ExecuteSql(CREATE_USER_TABLE);
	int cnt = 0;
	while (true) {
		LOG_INFO("cnt:{}", cnt++);
		sleep(1);
	}
	return 0;
}