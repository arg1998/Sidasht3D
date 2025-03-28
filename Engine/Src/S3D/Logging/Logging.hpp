#pragma once

#include "S3D/Definitions.hpp"
#if defined(S3D_RELEASE_PROFILING_BUILD)
    #include <S3D/Profiler/Profiler.hpp>
#endif

#include <ctime>
#include <fmt/base.h>
#include <fmt/color.h>
#include <fmt/chrono.h>
#include <fmt/ranges.h>

#if defined(S3D_PLATFORM_WINDOWS)
    #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
    #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

enum LogLevel : u32 {
    S3D_LOG_LEVEL_DEBUG,
    S3D_LOG_LEVEL_INFO,
    S3D_LOG_LEVEL_WARNING,
    S3D_LOG_LEVEL_ERROR,
    S3D_LOG_LEVEL_FATAL,
    __S3D_LOG_LEVEL_COUNT
};

static const fmt::text_style __fmtColors[]{
    fmt::fg(fmt::color::gray),
    fmt::fg(fmt::color::blue),
    fmt::fg(fmt::color::yellow),
    fmt::fg(fmt::color::orange),
    fmt::fg(fmt::color::red)};

static const u32 __tracyColors[LogLevel::__S3D_LOG_LEVEL_COUNT]{
    static_cast<u32>(fmt::color::gray),
    static_cast<u32>(fmt::color::blue),
    static_cast<u32>(fmt::color::yellow),
    static_cast<u32>(fmt::color::orange),
    static_cast<u32>(fmt::color::red)};

static const char* __logIndicators[] = {
    "[D]",  // Debug
    "[I]",  // Info
    "[W]",  // Warning
    "[E]",  // Error
    "[F]"   // Fatal
};

std::string __GetLogTimestamp() {
    using namespace std::chrono;

    const auto now = system_clock::now();
    const auto now_time = system_clock::to_time_t(now);
    const auto now_ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::tm local_time{};

    #if defined(S3D_PLATFORM_WINDOWS)
        localtime_s(&local_time, &now_time);  // for windows
    #else
        localtime_r(&now_time, &local_time);  // for unix-based os
    #endif

    return std::move(fmt::format("{:%H:%M:%S}.{:03}", local_time, now_ms.count()));
}

template <typename... Args>
void __PRIVATE_LOG(LogLevel logLevel, const char* file, int line, fmt::format_string<Args...>&& message, Args&&... args) {
    std::string timestamp = std::move(__GetLogTimestamp());
    std::string formatted_message = std::move(fmt::format(std::move(message), std::forward<Args>(args)...));
    std::string formatted_log = std::move(fmt::format("{} {} >>> {} <{}:{}>", timestamp, __logIndicators[static_cast<int>(logLevel)], formatted_message, file, line));

    fmt::print(__fmtColors[static_cast<int>(logLevel)], "{}\n", formatted_log);

    #if defined(S3D_RELEASE_PROFILING_BUILD)
        TracyMessageC(formatted_log.c_str(), formatted_log.size(), __tracyColors[static_cast<int>(logLevel)]);
    #endif
}

#define LOG_DEBUG(msg, ...) __PRIVATE_LOG(LogLevel::S3D_LOG_LEVEL_DEBUG, __FILENAME__, __LINE__, msg, ##__VA_ARGS__)
#define LOG_INFO(msg, ...) __PRIVATE_LOG(LogLevel::S3D_LOG_LEVEL_INFO, __FILENAME__, __LINE__, msg, ##__VA_ARGS__)
#define LOG_WARNING(msg, ...) __PRIVATE_LOG(LogLevel::S3D_LOG_LEVEL_WARNING, __FILENAME__, __LINE__, msg, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...) __PRIVATE_LOG(LogLevel::S3D_LOG_LEVEL_ERROR, __FILENAME__, __LINE__, msg, ##__VA_ARGS__)
#define LOG_FATAL(msg, ...) __PRIVATE_LOG(LogLevel::S3D_LOG_LEVEL_FATAL, __FILENAME__, __LINE__, msg, ##__VA_ARGS__)
