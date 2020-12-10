#ifndef MYSQL_COMMON_H
#define MYSQL_COMMON_H

#include "common.h"

#undef LOG_DEBUG
#undef LOG_INFO
#undef LOG_WARN
#undef LOG_ERROR

#define LOG_DEBUG(...) DEBUG("  mysql  ", __VA_ARGS__)
#define LOG_INFO(...)  INFO("  mysql  ", __VA_ARGS__)
#define LOG_WARN(...)  WARN("  mysql  ", __VA_ARGS__)
#define LOG_ERROR(...) ERROR("  mysql  ", __VA_ARGS__)

#endif /* MYSQL_COMMON_H */