#include "MysqlAccessImpl.h"
#include "ServerEvent.h"


#include "common.h"
using namespace town;

int main()
{
	Jsoner json("/home/yan/Project/town/src/config/MysqlInfo.json", Jsoner::PARSE_TYPE::FILE);
	if (!json.ParseWhetherSuccess()) {
		return 0;
	}

	MysqlAccessImpl impl;
	impl.ConnectDb(json["db"].asString().c_str(), json["ip"].asString().c_str(), json["dba"].asString().c_str(), json["dba_passwd"].asString().c_str(), json["db_port"].asInt());

	const std::string exe = R"(

	select id from user where id = %0q:what;

	)";

	SQLTypeAdapter strParseSql("3");
	StoreQueryResult res = impl.ExecuteSql(exe, strParseSql);

	try {
		for (int i = 0; i < res.num_rows(); i++) {
			LOG_INFO("id:{}", res[i]["id"]);
		}
	}
	catch (std::exception& e) {
		LOG_WARN("{}", e.what());
	}
	catch (...) {
	    LOG_WARN("unknow error!!!");
	}




	// ServerEvent::GetInstance()->Initialization(20000);
	// ServerEvent::GetInstance()->StartServer();

	while (true) {
		sleep(3600);
	}
	return 0;
}