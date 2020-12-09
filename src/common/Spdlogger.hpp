/*******************************************************
 * @brief: Log输出模块
 * @Copyright: Copyleft
 * @license: GPL
 * @birth: created by yan on 2020-12-9
 * @version: V0.0.1
 * @revision: last revised by yan on 2020-12-9
 *******************************************************/

#ifndef SPD_LOGGER_H
#define SPD_LOGGER_H

#include "config.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <map>
#include <string>
#include <memory>

namespace town {

class Spdlogger
{
public:
    static Spdlogger* GetInstance()
    {
        static Spdlogger logger;
        return &logger;
    }

    void RegisterModule(const std::string& module)
    {
        std::lock_guard<std::mutex> lck(m_mutex);
        if (m_mapLogger.find(module) == m_mapLogger.end()) {
            m_mapLogger[module] = std::make_shared<spdlog::logger>(module, m_pPublicLogger);
            m_mapLogger[module]->flush_on(spdlog::level::debug); 
            m_mapLogger[module]->set_level(spdlog::level::debug);
            spdlog::set_default_logger(m_mapLogger[module]);
        }
    }

    std::shared_ptr<spdlog::logger> GetModuleLogger(const std::string& module)
    {
        std::lock_guard<std::mutex> lck(m_mutex);
        return m_mapLogger[module];
    }

private:
    Spdlogger() {}
#ifdef FILELOG
    std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> m_pPublicLogger = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("./log.txt", 1024 * 1024 * 40, 100);
#else
    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> m_pPublicLogger = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
#endif /* FILELOG */

    std::map<std::string,std::shared_ptr<spdlog::logger>> m_mapLogger;
    std::mutex m_mutex;
}; /* Spdlogger */

#define INFO(module,...) \
do { \
    Spdlogger::GetInstance()->RegisterModule(module); \
    SPDLOG_LOGGER_INFO(Spdlogger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
} while(0)

#define WARN(module,...) \
do { \
    Spdlogger::GetInstance()->RegisterModule(module); \
    SPDLOG_LOGGER_WARN(Spdlogger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
} while(0)

#define ERROR(module,...) \
do { \
    Spdlogger::GetInstance()->RegisterModule(module); \
    SPDLOG_LOGGER_ERROR(Spdlogger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
} while(0)

#define DEBUG(module,...) \
do { \
    Spdlogger::GetInstance()->RegisterModule(module); \
    SPDLOG_LOGGER_DEBUG(Spdlogger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
} while(0)

#define LOG_INFO(...)  INFO("  test   ", __VA_ARGS__)
#define LOG_WARN(...)  WARN("  test   ", __VA_ARGS__)
#define LOG_ERROR(...) ERROR("  test   ", __VA_ARGS__)
#define LOG_DEBUG(...) DEBUG("  test   ", __VA_ARGS__)

} /* town */

#endif /* SPD_LOGGER_H */