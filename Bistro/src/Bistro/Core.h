//
// Created by Connor Beard on 4/20/20.
//

#ifndef BISTRO_CORE_H
#define BISTRO_CORE_H


#define B_ASSERT(x, ...) { if (!x) { B_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); raise(SIGTRAP); } }
#define B_CORE_ASSERT(x, ...) { if (!x) { B_CORE_CRITICAL("ASSERTION FAILED: {0}", __VA_ARGS__); raise(SIGTRAP); } }

#define BIT(x) (1 << x)

#endif //BISTRO_CORE_H
