/*******************************************************
 * @brief: Log输出模块
 * @Copyright: Copyleft
 * @license: GPL
 * @birth: created by yan on 2020-12-9
 * @version: V0.0.1
 * @revision: last revised by yan on 2020-12-9
 *******************************************************/

#ifndef LOGGER_H
#define LOGGER_H

#include "config.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <map>
#include <string>
#include <memory>

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

    uint8_t GetLevel()
    {
        return m_iLoglevel;
    }

    uint8_t SetLevel(uint8_t iLoglevel)
    {
        m_iLoglevel = iLoglevel;
    }

private:
    Logger() {}

#ifdef FILELOG
    std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> m_pPublicLogger = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("./log.txt", 1024 * 1024 * 40, 100);
#else
    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> m_pPublicLogger = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
#endif /* FILELOG */

    std::map<std::string,std::shared_ptr<spdlog::logger>> m_mapLogger;
    std::mutex m_mutex;
    uint8_t m_iLoglevel = 0;
}; /* Logger */

#define TRACE(module,...) \
do { \
    if (Logger::GetInstance()->GetLevel() <= 0) { \
        Logger::GetInstance()->RegisterModule(module); \
        SPDLOG_LOGGER_TRACE(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

#define DEBUG(module,...) \
do { \
    if (Logger::GetInstance()->GetLevel() <= 1) { \
        Logger::GetInstance()->RegisterModule(module); \
        SPDLOG_LOGGER_DEBUG(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

#define INFO(module,...) \
do { \
    if (Logger::GetInstance()->GetLevel() <= 2) { \
        Logger::GetInstance()->RegisterModule(module); \
        SPDLOG_LOGGER_INFO(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

#define WARN(module,...) \
do { \
    if (Logger::GetInstance()->GetLevel() <= 3) { \
        Logger::GetInstance()->RegisterModule(module); \
        SPDLOG_LOGGER_WARN(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

#define ERROR(module,...) \
do { \
    if (Logger::GetInstance()->GetLevel() <= 4) { \
        Logger::GetInstance()->RegisterModule(module); \
        SPDLOG_LOGGER_ERROR(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

#define CRITICAL(module,...) \
do { \
    if (Logger::GetInstance()->GetLevel() <= 5) { \
        Logger::GetInstance()->RegisterModule(module); \
        SPDLOG_CRITICAL(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

} /* town */

#endif /* LOGGER_H */