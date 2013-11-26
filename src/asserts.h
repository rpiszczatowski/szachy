#pragma once

#include <iostream>
#include <assert.h>
#include "print.h"

#define DEBUG
#ifdef DEBUG
#define ASSERT(cond, ...) \
    if (!(cond)) { \
        println(std::cerr, "(", #__VA_ARGS__, ") = (", ##__VA_ARGS__, ")"); \
        assert(cond); \
    }
#else
#define ASSERT(cond, ...)
#endif
