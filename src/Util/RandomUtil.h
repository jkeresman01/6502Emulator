#pragma once

#include <random>

namespace emulator6502
{
////////////////////////////////////////////////////////////
/// 
/// @class Random
///
/// @brief A utility class for generating random numbers using the
///        Mersenne Twister algorithm. 
///        This class provides methods
///        to initialize the random engine and generate random numbers
///        within a specified range.
///
////////////////////////////////////////////////////////////
class Random
{
  public:
    //////////////////////////////////////////////////////////////
    ///
    /// @brief Deleted default constructor to prevent instantiation.
    ///        Utility class.
    ///
    //////////////////////////////////////////////////////////////
    Random() = delete;

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Initializes the random engine with a seed.
    ///
    //////////////////////////////////////////////////////////////
    static void Init();

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Generates a random number within the range [0, max).
    ///
    /// @param [in] max The upper limit of the random number 
    ///                 range (exclusive).
    ///
    /// @return A random number between 0 and max.
    ///
    //////////////////////////////////////////////////////////////
    static uint32_t Generate(uint32_t max);

  private:
    //////////////////////////////////////////////////////////////
    ///
    /// @brief Random number generator engine (Mersenne Twister).
    ///
    //////////////////////////////////////////////////////////////
    static std::mt19937 s_randomEngine;

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Distribution for generating random integers.
    ///
    //////////////////////////////////////////////////////////////
    static std::uniform_int_distribution<std::mt19937::result_type> s_distribution;
};

} // namespace emulator6502
