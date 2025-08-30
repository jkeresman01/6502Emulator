#include "App/Emulator.h"

int main()
{
    emulator6502::Emulator6502 emulator6502;

    emulator6502.Init();
    emulator6502.Run();
    emulator6502.Shutdown();
}