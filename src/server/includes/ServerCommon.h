#ifndef SERVER_COMMON_H
#define SERVER_COMMON_H

#include "common.h"

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

#undef LOG_DEBUG
#undef LOG_INFO
#undef LOG_WARN
#undef LOG_ERROR

#define LOG_DEBUG(...) DEBUG("  server ", __VA_ARGS__)
#define LOG_INFO(...)  INFO("  server  ", __VA_ARGS__)
#define LOG_WARN(...)  WARN("  server  ", __VA_ARGS__)
#define LOG_ERROR(...) ERROR("  server  ", __VA_ARGS__)

class ClientHandle;
typedef std::shared_ptr<ClientHandle> CliHanPtr;
typedef std::unordered_map<std::string, CliHanPtr> UMCliHanPtr;
typedef std::vector<UMCliHanPtr> VUMCliHanPtr;

class ServerEvent;
typedef std::shared_ptr<ServerEvent> SerEvnPtr;

class ServerGateway;
typedef std::unique_ptr<ServerGateway> SerGatPtr;

struct MSG_INFO{
	std::size_t msg_len = 0;
	enum MSG_TYPE : uint32_t {
		MESS_REGISTER = 0,
		MESS_LOGIN = 1
	} msg_type = MESS_REGISTER;
	std::size_t msg_crc = 0;
};

} /* town */

#endif /* SERVER_COMMON_H */