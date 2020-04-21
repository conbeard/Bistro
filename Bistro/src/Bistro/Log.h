//
// Created by Connor Beard on 4/20/20.
//

#ifndef BISTRO_LOG_H
#define BISTRO_LOG_H

#include "Core.h"


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


#endif //BISTRO_LOG_H
