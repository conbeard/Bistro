//
// Created by Connor Beard on 4/20/20.
//

#ifndef BISTRO_CORE_H
#define BISTRO_CORE_H

#include <memory>
#include <csignal>

#define B_ASSERT(x, ...) { if (!x) { B_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); raise(SIGTRAP); } }
#define B_CORE_ASSERT(x, ...) { if (!x) { B_CORE_CRITICAL("ASSERTION FAILED: {0}", __VA_ARGS__); raise(SIGTRAP); } }

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Bistro {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;
}

#endif //BISTRO_CORE_H
