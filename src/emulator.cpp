#include <iostream>

#include "emulator.hpp"
#include "cpu.hpp"

Emulator::Core::Core() : cpu(this->bus) {
    bus = { 0, 0, 0, 0, 0 };

    rom.fill(0xea);

    rom[0xfffc - (0xffff - 0xbfe0)] = 0x00;
    rom[0xfffd - (0xffff - 0xbfe0)] = 0x00;

    uint16_t a = 0xffff;

    cpu.clearPC();
    for(int i = 0; i < 2; i++) {
        cpu.addrBusLoadFromResetVector(i == 0);
        bus.data = rom[bus.address - (0xffff - 0xbfe0)];
        cpu.dataBusWriteToPC(i == 0);

    }

    printf("%x\n", cpu.registers.PC);
}
