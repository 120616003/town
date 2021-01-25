#ifndef LOGGER_H
#define LOGGER_H

#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "JsonParse.hpp"
const std::string strLogConfig = "/home/yan/Project/town/src/config/LogConfig.json";
#include <iostream>

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
        return m_umapLogger[m_umapKeyValue[module]];
    }

    uint8_t GetLogLevel()
    {
        return m_iLoglevel;
    }

    void SetLogLevel(uint8_t iLoglevel)
    {
        m_iLoglevel = iLoglevel;
    }

private:
    Logger()
    {
        // m_root.Parse(strLogConfig, JsonParse::PARSE_TYPE::FILE);
        // size_t len = m_root["LogType"].size();
        // JsonParse tmp = m_root["LogType"];
        // for (size_t i = 0; i < len; i++) {
        //     // if (m_root["LogType"][i]["LogSwitch"].asBool()) {
        //         // std::cout << m_root["LogType"][i]["LogName"].asString() << std::endl;
        //         // m_umapKeyValue[m_root["LogType"][i]] = m_root["LogType"][i].asString() + std::string(10 - m_root["LogType"][i].asString().size(), " ");
        //     // }
        //     size_t len2 = tmp[i]["test"].size();
        //     std::cout << "len2:" << len2 << std::endl;
        //     for (size_t j = 0; j < len2; j++) {
        //         JsonParse tmp2 = tmp[i]["test"];
        //         std::cout << tmp2.size() << std::endl;
        //     }
        // }
        m_umapKeyValue["mysql"]  = "mysql  ";
        m_umapKeyValue["redis"]  = "redis  ";
        m_umapKeyValue["server"] = "server ";
        m_umapKeyValue["main"]   = "main   ";
        for (auto pair : m_umapKeyValue) {
            RegisterModule(pair.second);
        }
    }

#ifdef FILELOG
    std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> m_pPublicLogger = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("./log.txt", 1024 * 1024 * 40, 100);
#else
    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> m_pPublicLogger = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
#endif /* FILELOG */

    std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> m_umapLogger;
    std::unordered_map<std::string, std::string> m_umapKeyValue;
    uint8_t m_iLoglevel = SPDLOG_LEVEL_TRACE;
    JsonParse m_root;
}; /* Logger */

#define TRACE(module,...) \
do { \
    if (Logger::GetInstance()->GetLogLevel() <= SPDLOG_LEVEL_TRACE) { \
        SPDLOG_LOGGER_TRACE(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

#define DEBUG(module,...) \
do { \
    if (Logger::GetInstance()->GetLogLevel() <= SPDLOG_LEVEL_DEBUG) { \
        SPDLOG_LOGGER_DEBUG(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

#define INFO(module,...) \
do { \
    if (Logger::GetInstance()->GetLogLevel() <= SPDLOG_LEVEL_INFO) { \
        SPDLOG_LOGGER_INFO(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

#define WARN(module,...) \
do { \
    if (Logger::GetInstance()->GetLogLevel() <= SPDLOG_LEVEL_WARN) { \
        SPDLOG_LOGGER_WARN(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

#define ERROR(module,...) \
do { \
    if (Logger::GetInstance()->GetLogLevel() <= SPDLOG_LEVEL_ERROR) { \
        SPDLOG_LOGGER_ERROR(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

#define CRITICAL(module,...) \
do { \
    if (Logger::GetInstance()->GetLogLevel() <= SPDLOG_LEVEL_CRITICAL) { \
        SPDLOG_CRITICAL(Logger::GetInstance()->GetModuleLogger(module), __VA_ARGS__); \
    } \
} while(0)

} /* town */

#endif /* LOGGER_H */