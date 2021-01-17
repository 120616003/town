#include <iostream>
#include <unistd.h>

#include "MysqlAccess.h"
#include "ServerEvent.h"
#include "common.h"
using namespace town;
using namespace rapidjson;

int main()
{
	// Jsoner json("/home/yan/Project/town/src/config/MysqlInfo.json", Jsoner::PARSE_TYPE::FILE);
	// if (!json.ParseWhetherSuccess()) {
	// 	return 0;
	// }

	// MysqlAccess::GetInstance()->Initialization(json["ip"].asString(), json["dba"].asString(), json["dba_passwd"].asString(), json["db"].asString(), json["db_port"].asInt());
	// MysqlAccess::GetInstance()->ExecuteSql(create_town_database);
	// MysqlAccess::GetInstance()->ExecuteSql(create_user_table);
	// MysqlAccess::GetInstance()->ExecuteSql(create_user_info_table);

	ServerEvent::GetInstance()->Initialization(20000);
	ServerEvent::GetInstance()->StartServer();

	// int cnt = 0;
	// while (cnt != 10) {
	// 	LOG_INFO("cnt:{}", cnt++);
	// 	sleep(1);
	// }

	// serverevent.ClearMap(0);

	while (true) {
		// LOG_INFO("{}", Booster::GetUUID6());
		sleep(1);
	}
	return 0;
}