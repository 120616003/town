#include "town_config.h"
#include "MysqlOptHandleInfc.h"

using namespace town;

const std::string strMysqlConfig = "config/MysqlConfig.json";

struct DB_INFO
{
	int db_cnt;
	std::string ip;
	std::string dba;
	std::string dba_passwd;
	std::string db;
	unsigned int db_port;
};

DB_INFO ReadDBConfig()
{
	TownJson root(strMysqlConfig, JSON_TYPE::FILE);
	DB_INFO info;
	try {
		info.db_cnt = root["db_cnt"].asInt();
		info.ip = root["ip"].asString();
		info.dba = root["dba"].asString();
		info.dba_passwd = root["dba_passwd"].asString();
		info.db = root["db"].asString();
		info.db_port = root["db_port"].asInt();
	}
	catch (std::exception e) {
		ERROR("main", "json error msg:{}", e.what());
		exit(1);
	}
	catch (...) {
		ERROR("main", "json unknow error");
		exit(1);
	}
	return info;
}

int main()
{
	DB_INFO info = ReadDBConfig();
	if (!MysqlInterface::GetInstance()->Initialization(info.db_cnt, info.db, info.ip, info.dba, info.dba_passwd, info.db_port)) {
		exit(1);
	}
	MysqlOptHandleInfc::GetInstance()->Initialization();

	// ServerEvent::GetInstance()->Initialization(20000);
	// ServerEvent::GetInstance()->StartServer();

	while (true) {
		sleep(3600);
	}
	return 0;
}