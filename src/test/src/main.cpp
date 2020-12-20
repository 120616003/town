#include <iostream>
#include <unistd.h>

#include "MysqlAccess.h"
#include "ServerEvent.h"
#include "common.h"
using namespace town;

int main()
{
	Jsoner json("/home/yan/Project/town/src/config/MysqlInfo.json", Jsoner::PARSE_TYPE::FILE);
	if (!json.ParseWhetherSuccess()) {
		return 0;
	}

	MysqlAccess::GetInstance()->Initialization(json["ip"].GetValue(), json["dba"].GetValue(), json["dba_passwd"].GetValue(), json["db"].GetValue(), std::atoi(json["db_port"].GetValue().c_str()));
	MysqlAccess::GetInstance()->ExecuteSql(create_town_database);
	MysqlAccess::GetInstance()->ExecuteSql(create_user_table);
	MysqlAccess::GetInstance()->ExecuteSql(create_user_info_table);

	// ServerEvent serverevent;
	// serverevent.ServerInit(20000);
	// serverevent.ServerStart();

	// int cnt = 0;
	// while (cnt != 10) {
	// 	LOG_INFO("cnt:{}", cnt++);
	// 	sleep(1);
	// }

	// serverevent.ClearMap(0);

	while (true) {
		sleep(3600);
	}
	return 0;
}