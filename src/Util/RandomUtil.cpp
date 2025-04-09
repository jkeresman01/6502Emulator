#include "RandomUtil.h"

namespace emulator6502
{

std::mt19937 Random::s_randomEngine;
std::uniform_int_distribution<std::mt19937::result_type> Random::s_distribution;

void Random::Init()
{
    s_randomEngine.seed(std::random_device()());
}

uint32_t Random::Generate(uint32_t max)
{
    return s_distribution(s_randomEngine) % (max + 1);
}

} // namespace emulator6502
