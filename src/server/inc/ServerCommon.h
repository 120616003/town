#ifndef SERVER_COMMON_H
#define SERVER_COMMON_H

#include "common.h"

namespace town {

#undef LOG_DEBUG
#undef LOG_INFO
#undef LOG_WARN
#undef LOG_ERROR

#define LOG_DEBUG(...) DEBUG("  server ", __VA_ARGS__)
#define LOG_INFO(...)  INFO("  server  ", __VA_ARGS__)
#define LOG_WARN(...)  WARN("  server  ", __VA_ARGS__)
#define LOG_ERROR(...) ERROR("  server  ", __VA_ARGS__)


} /* town */

#endif /* SERVER_COMMON_H */