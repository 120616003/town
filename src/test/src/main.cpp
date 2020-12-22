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

	LOG_INFO("ip:{}", json["array"][0].asInt());
	LOG_INFO("ip:{}", json["array"][1].asInt());
	LOG_INFO("ip:{}", json["array"][2].asInt());
	LOG_INFO("ip:{}", json["array"][3].asInt());
	LOG_INFO("ip:{}", json["array"][4].asInt());
	LOG_INFO("ip:{}", json["array"][4].asInt());
	LOG_INFO("ip:{}", json["array"][4].asInt());
	

	// MysqlAccess::GetInstance()->Initialization(json["ip"].asString(), json["dba"].asString(), json["dba_passwd"].asString(), json["db"].asString(), json["db_port"].asInt());
	// MysqlAccess::GetInstance()->ExecuteSql(create_town_database);
	// MysqlAccess::GetInstance()->ExecuteSql(create_user_table);
	// MysqlAccess::GetInstance()->ExecuteSql(create_user_info_table);

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