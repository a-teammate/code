#include "inexor/util/Logging.hpp"

namespace inexor {
namespace util {

Logging::Logging()
{
    // Queue size for async mode must be power of 2
    size_t q_size = 4096;
    // Set async mode
    spdlog::set_async_mode(q_size);
}

Logging::~Logging()
{
    spdlog::drop_all();
}

void Logging::initDefaultLoggers()
{
    for(const auto& default_logger_name : default_logger_names) {
        createAndRegisterLogger(default_logger_name.c_str());
    }
    spdlog::get("global")->debug() << "Default loggers initialized";
}

void Logging::createAndRegisterLogger(std::string logger_name)
{
    std::vector<spdlog::sink_ptr> sinks = getSinksForLogger(logger_name);
    auto logger = std::make_shared<spdlog::logger>(logger_name, begin(sinks), end(sinks));
    spdlog::register_logger(logger);
}

std::vector<spdlog::sink_ptr> Logging::getSinksForLogger(std::string logger_name)
{
    // Here we should configure which sinks are used in which logger
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
    sinks.push_back(std::make_shared<inexor::util::InexorConsoleSink>());
    sinks.push_back(std::make_shared<inexor::util::InexorCutAnsiCodesSink>(std::make_shared<spdlog::sinks::daily_file_sink_st>("inexor", "log", 23, 59)));
    return sinks;
}

void Logging::setLogLevel(std::string logger_name, std::string log_level)
{
    try {
        auto logger = spdlog::get(logger_name);
        logger->set_level(log_levels.at(log_level));
    } catch (const spdlog::spdlog_ex& ex) {
    }
}

void Logging::setLogFormat(std::string logger_name, std::string pattern)
{
    try {
        auto logger = spdlog::get(logger_name);
        logger->set_pattern(pattern);
    } catch (const spdlog::spdlog_ex& ex) {
    }
}

}
}