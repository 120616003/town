#ifndef QML_COMMON_H
#define QML_COMMON_H

#include "Logger.hpp"

namespace town {

#undef LOG_TRACE
#undef LOG_DEBUG
#undef LOG_INFO
#undef LOG_WARN
#undef LOG_ERROR
#undef LOG_CRITICAL

#define LOG_TRACE(...)    TRACE("qml", __VA_ARGS__)
#define LOG_DEBUG(...)    DEBUG("qml", __VA_ARGS__)
#define LOG_INFO(...)     INFO("qml", __VA_ARGS__)
#define LOG_WARN(...)     WARN("qml", __VA_ARGS__)
#define LOG_ERROR(...)    ERROR("qml", __VA_ARGS__)
#define LOG_CRITICAL(...) CRITICAL("qml", __VA_ARGS__)

}

#endif /* QML_COMMON_H */
