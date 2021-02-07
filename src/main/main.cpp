#include "town_config.h"
#include "MysqlAccessInfc.h"
#include "MysqlOptHandleInfc.h"
#include "ServerGatewayInfc.h"
#include "ServerEventInfc.h"

using namespace town;

const std::string strMysqlConfig = "config/MysqlConfig.json";
const std::string strServerConfig = "config/ServerConfig.json";

struct DB_INFO
{
	int db_cnt = 0;
	std::string ip;
	std::string dba;
	std::string dba_passwd;
	std::string db;
	unsigned int db_port = 0;
};

struct SERVER_INFO
{
	unsigned int server_port;
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
	catch (std::exception& e) {
		ERROR("main", "json error msg:{}", e.what());
		exit(1);
	}
	catch (...) {
		ERROR("main", "json unknow error");
		exit(1);
	}
	return info;
}

SERVER_INFO ReadServerConfig()
{
	TownJson root(strServerConfig, JSON_TYPE::FILE);
	SERVER_INFO info;
	try {
		info.server_port = root["server_port"].asInt();
	}
	catch (std::exception& e) {
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
	// 读取mysql数据库信息
	DB_INFO db_info = ReadDBConfig();
	// 读取server信息
	SERVER_INFO server_info = ReadServerConfig();

	// 初始化mysql句柄
	if (!MysqlAccessInfc::GetInstance()->Initialization(db_info.db_cnt, db_info.db, db_info.ip, db_info.dba, db_info.dba_passwd, db_info.db_port)) {
		exit(1);
	}
	// 初始化数据库业务逻辑句柄
	MysqlOptHandleInfc::GetInstance()->Initialization();
	MysqlOptHandleInfc::GetInstance()->GetOptHandle(ADD)->InitDB();
	// 消息网关初始化
	ServerGatewayInfc::GetInstance()->Initialization(MysqlOptHandleInfc::GetInstance());
	// town server 初始化
	if(ServerEventInfc::GetInstance()->Initialization(server_info.server_port, ServerGatewayInfc::GetInstance()) == -1) {
		exit(1);
	}
	// town server 开始
	ServerEventInfc::GetInstance()->StartServer();

	while (true) {
		sleep(3600);
	}
	return 0;
}