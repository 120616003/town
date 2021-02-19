#ifndef SERVER_COMMON_H
#define SERVER_COMMON_H

#include "town_config.h"

#include <event2/bufferevent.h>
#include <event2/bufferevent_struct.h>
#include <event2/util.h> // evutil_socket_t
#include <event2/listener.h>

#include "user.pb.h"

using namespace std::chrono_literals;

struct event_config;
struct event_base;
struct evconnlistener;
struct bufferevent;

namespace town {

#undef LOG_TRACE
#undef LOG_DEBUG
#undef LOG_INFO
#undef LOG_WARN
#undef LOG_ERROR
#undef LOG_CRITICAL

#define LOG_TRACE(...) TRACE("server", __VA_ARGS__)
#define LOG_DEBUG(...) DEBUG("server", __VA_ARGS__)
#define LOG_INFO(...)  INFO("server", __VA_ARGS__)
#define LOG_WARN(...)  WARN("server", __VA_ARGS__)
#define LOG_ERROR(...) ERROR("server", __VA_ARGS__)
#define LOG_CRITICAL(...) CRITICAL("server", __VA_ARGS__)

class ClientHandle;
typedef std::shared_ptr<ClientHandle> CliHanPtr;
typedef std::unordered_map<std::string, CliHanPtr> UMCliHanPtr;
typedef std::vector<UMCliHanPtr> VUMCliHanPtr;

enum MSG_TYPE : uint32_t {
	MESS_REGISTER = 10001,
	MESS_LOGIN = 10002,
	MESS_FRIEND_LIST = 10003
};

const std::map<MSG_TYPE, std::string> convert_msg_type = {
	{MESS_REGISTER, "mess_register"}, 
	{MESS_LOGIN, "mess_login"}
};

struct MSG_INFO {
	std::size_t msg_len = 0;
	MSG_TYPE msg_type = MESS_REGISTER;
	std::size_t msg_crc = 0;
};

struct MSG_DATA {
	bufferevent* bev = nullptr;
	MSG_INFO info {};
	std::unique_ptr<uint8_t[]> data = nullptr;
};

} /* town */

#endif /* SERVER_COMMON_H */