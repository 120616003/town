#ifndef SERVER_COMMON_H
#define SERVER_COMMON_H

#include "common.h"

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>

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

} /* town */

#endif /* SERVER_COMMON_H */