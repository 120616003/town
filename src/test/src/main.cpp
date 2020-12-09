#include <iostream>
#include <unistd.h>

#include "MysqlAccess.h"
#include "common.h"
using namespace town;

int main()
{
	MysqlAccess* mysql = MysqlAccess::GetInstance();
	mysql->Initialization("town", "1", "town", 1);
	int cnt = 0;
	while (true) {
		sleep(1);
		LOG_INFO("cnt:{}", cnt++);
	}
	return 0;
}