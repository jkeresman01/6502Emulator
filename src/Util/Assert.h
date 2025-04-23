#pragma once

#include <cstdlib>
#include <iostream>

#define ASSERT(condition)                                                                                    \
    do                                                                                                       \
    {                                                                                                        \
        if (!(condition))                                                                                    \
        {                                                                                                    \
            std::cerr << "ASSERT FAILED: " << #condition << " at " << __FILE__ << ":" << __LINE__            \
                      << std::endl;                                                                          \
            std::abort();                                                                                    \
        }                                                                                                    \
    } while (0)