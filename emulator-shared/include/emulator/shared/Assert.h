#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>

//////////////////////////////////////////////////////////////
///
/// @def ASSERT(condition)
///
/// @brief A simple assertion macro for validating conditions
///        at runtime.
///
/// If the condition evaluates to `false`, the macro prints an
/// error message to `std::cerr` showing:
///   - the failed condition  
///   - the source file name  
///   - the line number  
///
/// After printing, the program is terminated by calling
/// `std::abort()`.
///
/// Example usage:
/// @code
/// int x = 5;
/// ASSERT(x == 5);   // OK
/// ASSERT(x == 10);  // Fails, prints error and aborts
/// @endcode
///
//////////////////////////////////////////////////////////////
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

