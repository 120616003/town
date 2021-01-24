#ifndef MYSQL_COMMON_H
#define MYSQL_COMMON_H

#include "common.h"

namespace town {

#undef LOG_DEBUG
#undef LOG_INFO
#undef LOG_WARN
#undef LOG_ERROR

#define LOG_DEBUG(...) DEBUG("  mysql  ", __VA_ARGS__)
#define LOG_INFO(...)  INFO("  mysql  ", __VA_ARGS__)
#define LOG_WARN(...)  WARN("  mysql  ", __VA_ARGS__)
#define LOG_ERROR(...) ERROR("  mysql  ", __VA_ARGS__)

const std::string create_town_database = R"(

create database if not exists town;

)";

const std::string create_user_table = R"(

create table if not exists town.user (
	id int (15) auto_increment primary key not null,
	uuid varchar (32) not null,
	time timestamp not null,
	acc_email varchar (30),
	acc_phone varchar (11),
	acc_name varchar (30),
	password varchar (20) not null
);

)";

const std::string create_user_info_table = R"(

create table if not exists town.user_info (
	uuid varchar(32) primary key not null,
	status bool not null,
	age int2 not null,
	sex bit (2) not null
);

)";

} /* town */

#endif /* MYSQL_COMMON_H */