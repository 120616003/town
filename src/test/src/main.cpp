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
	Jsoner json("/home/yan/Project/town/src/config/MysqlInfo.json", Jsoner::PARSE_TYPE::FILE);
	if (!json.ParseWhetherSuccess()) {
		return 0;
	}
	auto mysql = MysqlAccess::GetInstance();
	mysql->Initialization(json.GetValue({"ip"}), json.GetValue({"dba"}), json.GetValue({"dba_passwd"}), json.GetValue({"db"}), std::atoi(json.GetValue({"db_port"}).c_str()));
	mysql->ExecuteSql(CREATE_USER_TABLE);

	int cnt = 0;
	while (true) {
		LOG_INFO("cnt:{}", cnt++);
		sleep(1);
	}
	return 0;
}