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

} /* town */

#endif /* MYSQL_COMMON_H */