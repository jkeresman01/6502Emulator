#pragma once

#include <random>

namespace emulator6502
{

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

    static void Init();
    static uint32_t Generate(uint32_t max);

  private:
    static std::mt19937 s_randomEngine;
    static std::uniform_int_distribution<std::mt19937::result_type> s_distribution;
};

} // namespace emulator6502