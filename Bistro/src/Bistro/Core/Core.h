//
// Created by Connor Beard on 4/20/20.
//

#ifndef BISTRO_CORE_H
#define BISTRO_CORE_H

#include <memory>

#define B_ASSERT(x, ...) { if (!x) { B_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); raise(SIGTRAP); } }
#define B_CORE_ASSERT(x, ...) { if (!(x)) { B_CORE_CRITICAL("ASSERTION FAILED: {0}", __VA_ARGS__); raise(SIGTRAP); } }

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Bistro {

    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> createScope(Args&& ... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> createRef(Args&& ... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#endif //BISTRO_CORE_H
