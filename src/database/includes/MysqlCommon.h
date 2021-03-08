#ifndef MYSQL_COMMON_H
#define MYSQL_COMMON_H

#include "town_config.h"

namespace town {

#undef LOG_TRACE
#undef LOG_DEBUG
#undef LOG_INFO
#undef LOG_WARN
#undef LOG_ERROR
#undef LOG_CRITICAL

#define LOG_TRACE(...)    TRACE("mysql", __VA_ARGS__)
#define LOG_DEBUG(...)    DEBUG("mysql", __VA_ARGS__)
#define LOG_INFO(...)     INFO("mysql", __VA_ARGS__)
#define LOG_WARN(...)     WARN("mysql", __VA_ARGS__)
#define LOG_ERROR(...)    ERROR("mysql", __VA_ARGS__)
#define LOG_CRITICAL(...) CRITICAL("mysql", __VA_ARGS__)

const std::string create_town_database = R"(

create database if not exists town;

)";

const std::string create_user_table = R"(

create table if not exists town.user (
	id int (15) auto_increment primary key not null,

	uuid varchar(32) not null unique,

	time timestamp not null,

	email varchar(255) unique,

	phone varchar(11) unique,

	passwd varchar(20) not null,

	index index_email (email(255)),

	index index_phone (phone(11))
);

)";

const std::string create_user_info_table = R"(

create table if not exists town.user_info (
	uuid varchar(32) primary key not null,

	name varchar(20) not null unique,

	nick_name varchar(20),

	status bool default false,

	sex bit (2) default b'11',

	birthday date default "1970-1-1",

	index index_name (name(20))

) default charset = utf8;

)";

} /* town */

#endif /* MYSQL_COMMON_H */