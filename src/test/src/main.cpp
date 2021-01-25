
#include "MysqlAccessImpl.h"
#include "ServerEvent.h"

#include "town_config.h"

#undef LOG_TRACE
#undef LOG_DEBUG
#undef LOG_INFO
#undef LOG_WARN
#undef LOG_ERROR
#undef LOG_CRITICAL

#define LOG_TRACE(...) TRACE("main", __VA_ARGS__)
#define LOG_DEBUG(...) DEBUG("main", __VA_ARGS__)
#define LOG_INFO(...)  INFO("main", __VA_ARGS__)
#define LOG_WARN(...)  WARN("main", __VA_ARGS__)
#define LOG_ERROR(...) ERROR("main", __VA_ARGS__)
#define LOG_CRITICAL(...) CRITICAL("main", __VA_ARGS__)

using namespace town;

int main()
{
	// JsonParse json("config/MysqlConfig.json", JsonParse::PARSE_TYPE::FILE);
	// if (!json.ParseWhetherSuccess()) {
	// 	return 0;
	// }

	// TownJson root("config/LogConfig.json", JSON_TYPE::FILE);
	// LOG_INFO("LogName:{}", root["LogType"][0]["LogName"].asString());
	

	// try {
		// JsonParse tmp2("123");
		// json["dba"] = tmp2;
		// std::string tmp1 = json["dd"].asString();
		// LOG_INFO("json:{}", json.AsString());

		
		// LOG_INFO("res:{}", tmp2.AsString());		
		// LOG_INFO("tmp1:{}", tmp1);
	// }
	// catch (std::exception& e) {
		// LOG_WARN("{}", e.what());
	// }
	// catch (...) {
	    // LOG_WARN("unknow error!!!");
	// }

	// MysqlAccessImpl impl;
	// impl.ConnectDb(json["db"].asString().c_str(), json["ip"].asString().c_str(), json["dba"].asString().c_str(), json["dba_passwd"].asString().c_str(), json["db_port"].asInt());

	// const std::string exe = R"(

	// select id from user where id = %0q:what;

	// )";

	// SQLTypeAdapter strParseSql("3");
	// StoreQueryResult res = impl.ExecuteSql(exe, strParseSql);

	// try {
	// 	for (int i = 0; i < res.num_rows(); i++) {
	// 		LOG_INFO("id:{}", res[i]["id"]);
	// 	}
	// }
	// catch (std::exception& e) {
	// 	LOG_WARN("{}", e.what());
	// }
	// catch (...) {
	//     LOG_WARN("unknow error!!!");
	// }




	// ServerEvent::GetInstance()->Initialization(20000);
	// ServerEvent::GetInstance()->StartServer();

	while (true) {
		sleep(3600);
	}
	return 0;
}