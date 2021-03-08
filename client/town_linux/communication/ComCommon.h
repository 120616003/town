#ifndef COM_COMMON_H
#define COM_COMMON_H

#include "Logger.hpp"

namespace town {

#undef LOG_TRACE
#undef LOG_DEBUG
#undef LOG_INFO
#undef LOG_WARN
#undef LOG_ERROR
#undef LOG_CRITICAL

#define LOG_TRACE(...)    TRACE("communi", __VA_ARGS__)
#define LOG_DEBUG(...)    DEBUG("communi", __VA_ARGS__)
#define LOG_INFO(...)     INFO("communi", __VA_ARGS__)
#define LOG_WARN(...)     WARN("communi", __VA_ARGS__)
#define LOG_ERROR(...)    ERROR("communi", __VA_ARGS__)
#define LOG_CRITICAL(...) CRITICAL("communi", __VA_ARGS__)

enum MSG_TYPE : uint32_t {
    MESS_REGISTER = 0,
    MESS_LOGIN = 1
};

struct MSG_INFO {
    std::size_t msg_len = 0;
    MSG_TYPE msg_type = MESS_REGISTER;
    std::size_t msg_crc = 0;
};

}

#endif /* COM_COMMON_H */
