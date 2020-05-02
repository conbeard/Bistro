//
// Created by Connor Beard on 4/20/20.
//

#ifndef BISTRO_LOG_H
#define BISTRO_LOG_H

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Bistro {
    class  Log {
        public:
            static void Init();

            inline static std::shared_ptr<spdlog::logger>& GetBistroLogger() { return s_CoreLogger; }
            inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

        private:
            static std::shared_ptr<spdlog::logger> s_CoreLogger;
            static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

#define B_CORE_TRACE(...) ::Bistro::Log::GetBistroLogger()->trace(__VA_ARGS__)
#define B_CORE_INFO(...)  ::Bistro::Log::GetBistroLogger()->info(__VA_ARGS__)
#define B_CORE_WARN(...)  ::Bistro::Log::GetBistroLogger()->warn(__VA_ARGS__)
#define B_CORE_ERROR(...) ::Bistro::Log::GetBistroLogger()->error(__VA_ARGS__)
#define B_CORE_CRITICAL(...) ::Bistro::Log::GetBistroLogger()->critical(__VA_ARGS__)


#define B_TRACE(...) ::Bistro::Log::GetClientLogger()->trace(__VA_ARGS__)
#define B_INFO(...)  ::Bistro::Log::GetClientLogger()->info(__VA_ARGS__)
#define B_WARN(...)  ::Bistro::Log::GetClientLogger()->warn(__VA_ARGS__)
#define B_ERROR(...) ::Bistro::Log::GetClientLogger()->error(__VA_ARGS__)
#define B_CRITICAL(...) ::Bistro::Log::GetClientLogger()->critical(__VA_ARGS__)

#endif //BISTRO_LOG_H
