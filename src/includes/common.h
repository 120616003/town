#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <string>
#include <map>

#include "Logger.hpp"
#include "Jsoner.hpp"

namespace town
{

#undef LOG_DEBUG
#undef LOG_INFO
#undef LOG_WARN
#undef LOG_ERROR

#define LOG_DEBUG(...) DEBUG("  common ", __VA_ARGS__)
#define LOG_INFO(...)  INFO("  common ", __VA_ARGS__)
#define LOG_WARN(...)  WARN("  common ", __VA_ARGS__)
#define LOG_ERROR(...) ERROR("  common ", __VA_ARGS__)

#define SUCCESS 0
#define FAILED -1

} /* town */

#endif /* COMMON_H */