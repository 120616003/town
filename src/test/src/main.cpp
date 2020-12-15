#include <iostream>
#include <unistd.h>

#include "MysqlAccess.h"
#include "common.h"
using namespace town;

const std::string create_user_table = R"(create table if not exists user (
	id int auto_increment primary key not null,
	account_number int not null,
	password varchar(20)
);)";



int main()
{
	Jsoner json("/home/yan/Project/town/src/config/MysqlInfo.json", Jsoner::PARSE_TYPE::FILE);
	if (!json.ParseWhetherSuccess()) {
		return 0;
	}

	MysqlAccess::GetInstance()->Initialization(json["ip"].GetValue(), json["dba"].GetValue(), json["dba_passwd"].GetValue(), json["db"].GetValue(), std::atoi(json["db_port"].GetValue().c_str()));
	MysqlAccess::GetInstance()->ExecuteSql(create_user_table);

	// int cnt = 0;
	// while (true) {
	// 	LOG_INFO("cnt:{}", cnt++);
	// 	sleep(1);
	// }
	return 0;
}