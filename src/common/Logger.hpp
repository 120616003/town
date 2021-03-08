#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <atomic>
#include <thread>
#include <unistd.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "TownJson.hpp"

#include <errno.h>
#include <sys/inotify.h>
#include <sys/select.h>
#include <cstring>

const std::string strLogConfig = "config/LogConfig.json";

namespace town {

class Logger
{
public:
    static Logger* GetInstance()
    {
        static Logger logger;
        return &logger;
    }

    void RegisterModule(const std::string& module)
    {
        if (m_umapLogger.find(module) == m_umapLogger.end()) {
            m_umapLogger[module] = std::make_shared<spdlog::logger>(module, m_pPublicLogger);
            m_umapLogger[module]->flush_on(spdlog::level::trace); 
            m_umapLogger[module]->set_level(spdlog::level::trace);
            spdlog::set_default_logger(m_umapLogger[module]);
        }
    }

    std::shared_ptr<spdlog::logger> GetModuleLogger(const std::string& module)
    {
        return m_umapLogger[m_vumapKeyValue[m_log_index % 2][module]];
    }

    bool IsModule(const std::string& module)
    {
        return m_vumapKeyValue[m_log_index % 2].find(module) != m_vumapKeyValue[m_log_index % 2].end();
    }

    uint8_t GetLogLevel()
    {
        return m_iLoglevel;
    }

    void SetLogLevel(uint8_t iLoglevel)
    {
        m_iLoglevel = iLoglevel;
    }

    void ReadLogInfo()
    {
        TownJson root;
        if (root.Parse(strLogConfig, JSON_TYPE::FILE) && 
            root["LogType"].isArray() &&
            root["LogType"].size()) {
            static int8_t complement = 0;
            size_t len = root["LogType"].size();
            TownJson data = root["LogType"];
            m_vumapKeyValue[(m_log_index + complement) % 2].clear();
            for (size_t i = 0; i < len; ++i) {
                if (data[i]["LogSwitch"].isBool() && 
                    data[i]["LogSwitch"].asBool() &&
                    data[i]["LogName"].isString() &&
                    data[i]["LogName"].asString().size()) {

                    std::string strValue = data[i]["LogName"].asString();
                    int iSuffixLen = 10 - strValue.size();
                    m_vumapKeyValue[(m_log_index + complement) % 2][strValue] = strValue;
                    for (int j = 0; j < iSuffixLen; ++j) {
                        m_vumapKeyValue[(m_log_index + complement) % 2][strValue] += " ";
                    }
                }
            }
            for (auto pair : m_vumapKeyValue[(m_log_index + complement) % 2]) {
                RegisterModule(pair.second);
            }
            SetLogLevel(static_cast<uint8_t>(root["LogLevel"].asUInt()));
            if (!complement) {
                ++complement;
            }
            else {
                ++m_log_index;
            }
        }
    }

private:
    Logger()
    {
        m_vumapKeyValue.resize(2);
        ReadLogInfo();
        auto loginfo = std::thread([this] () {

            int fd = inotify_init();
            if (fd < 0) {
                throw "inotify init failed";
            }
            int wd = inotify_add_watch(fd, "config", IN_MODIFY | IN_CREATE);

            fd_set fds;
            int len = sizeof(struct inotify_event) + 16;
            char buffer[len];

            while (true) {
                FD_ZERO(&fds);
                FD_SET(fd, &fds);

                int retval = select(fd + 1, &fds, nullptr, nullptr, nullptr);
                if (retval == -1) {
                    SPDLOG_ERROR("select error:{}", strerror(errno));
                    continue;
                }

                if (FD_ISSET(fd, &fds)) {
                    int length = read(fd, buffer, len);
                    if (length < 0) {
                        SPDLOG_ERROR("read error:{}", strerror(errno));
                        continue;
                    }

                    struct inotify_event* event = reinterpret_cast<struct inotify_event*>(&buffer[0]);;
                    if ((event->mask & IN_MODIFY || event->mask & IN_CREATE) && std::string(event->name) == "LogConfig.json") {
                        static clock_t record = 0;
                        clock_t current = time(nullptr);
                        if (current - record >= 1) {
                            record = current;
                            this->ReadLogInfo();
                        }
                    }
                }
            }
            inotify_rm_watch(fd, wd);
        });
        pthread_setname_np(loginfo.native_handle(), "loginfo");
        loginfo.detach();
    }

#ifdef FILELOG
    std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> m_pPublicLogger = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("./log.txt", 1024 * 1024 * 40, 100);
#else
    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> m_pPublicLogger = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
#endif /* FILELOG */

    std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> m_umapLogger;
    std::vector<std::unordered_map<std::string, std::string>> m_vumapKeyValue;
    uint8_t m_iLoglevel = SPDLOG_LEVEL_TRACE;
    std::atomic_uint64_t m_log_index;
}; /* Logger */

#define TRACE(module,...) \
do { \
    if (Logger::GetInstance()->GetLogLevel() <= SPDLOG_LEVEL_TRACE && Logger::GetInstance()->IsModule(module)) { \
        SPDLOG_LOGGER_TRACE(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

#define DEBUG(module,...) \
do { \
    if (Logger::GetInstance()->GetLogLevel() <= SPDLOG_LEVEL_DEBUG && Logger::GetInstance()->IsModule(module)) { \
        SPDLOG_LOGGER_DEBUG(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

#define INFO(module,...) \
do { \
    if (Logger::GetInstance()->GetLogLevel() <= SPDLOG_LEVEL_INFO && Logger::GetInstance()->IsModule(module)) { \
        SPDLOG_LOGGER_INFO(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

#define WARN(module,...) \
do { \
    if (Logger::GetInstance()->GetLogLevel() <= SPDLOG_LEVEL_WARN && Logger::GetInstance()->IsModule(module)) { \
        SPDLOG_LOGGER_WARN(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

#define ERROR(module,...) \
do { \
    if (Logger::GetInstance()->GetLogLevel() <= SPDLOG_LEVEL_ERROR && Logger::GetInstance()->IsModule(module)) { \
        SPDLOG_LOGGER_ERROR(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

#define CRITICAL(module,...) \
do { \
    if (Logger::GetInstance()->GetLogLevel() <= SPDLOG_LEVEL_CRITICAL && Logger::GetInstance()->IsModule(module)) { \
        SPDLOG_LOGGER_CRITICAL(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

} /* town */

#endif /* LOGGER_H */