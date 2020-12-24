#ifndef MYSQL_DEFINE_H
#define MYSQL_DEFINE_H

namespace town
{

const std::string SQL_DECIMAL = "0";
const std::string SQL_TINY = "1";
const std::string SQL_SHORT = "2";
const std::string SQL_LONG = "3";
const std::string SQL_FLOAT = "4";
const std::string SQL_DOUBLE = "5";
const std::string SQL_NULL = "6";
const std::string SQL_TIMESTAMP = "7";
const std::string SQL_LONGLONG = "8";
const std::string SQL_INT24 = "9";
const std::string SQL_DATE = "10";
const std::string SQL_TIME = "11";
const std::string SQL_DATETIME = "12";
const std::string SQL_YEAR = "13";
const std::string SQL_NEWDATE = "14";
const std::string SQL_VARCHAR = "15";
const std::string SQL_BIT = "16";
const std::string SQL_TIMESTAMP2 = "17";
const std::string SQL_DATETIME2 = "18";
const std::string SQL_TIME2 = "19";
const std::string SQL_TYPED_ARRAY = "20";
const std::string SQL_INVALID = "243";
const std::string SQL_BOOL = "244";
const std::string SQL_JSON = "245";
const std::string SQL_NEWDECIMAL = "246";
const std::string SQL_ENUM = "247";
const std::string SQL_SET = "248";
const std::string SQL_TINY_BLOB = "249";
const std::string SQL_MEDIUM_BLOB = "250";
const std::string SQL_LONG_BLOB = "251";
const std::string SQL_BLOB = "252";
const std::string SQL_VAR_STRING = "253";
const std::string SQL_STRING = "254";
const std::string SQL_GEOMETRY = "255";

const std::string create_town_database = R"(

create database if not exists town;

)";

const std::string create_user_table = R"(

create table if not exists town.user (
	id int (15) auto_increment primary key not null,
	uuid varchar (32) not null,
	data_time datetime not null,
	account_name varchar (20) not null,
	password varchar (20) not null
);

)";

const std::string create_user_info_table = R"(

create table if not exists town.user_info (
	uuid varchar(30) primary key not null,
	account_number int not null,
	password varchar(20)
);

)";

} /* town */

#endif /* MYSQL_DEFINE_H */