#ifndef SERVER_COMMON_H
#define SERVER_COMMON_H

#include "common.h"

#include <memory>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

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

struct Msg_Info{
	std::size_t msg_len = 0;
	enum msg_type : uint32_t {
		MESS_REGISTER = 0,
		MESS_LOGIN = 1
	} msg_type = MESS_REGISTER;
	std::size_t msg_crc = 0;
};

} /* town */

#endif /* SERVER_COMMON_H */