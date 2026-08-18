#include <iostream>

#include "emulator.hpp"
#include "cpu.hpp"

Emulator::Core::Core() : cpu(this->bus) {
    bus = { 0, 0, 0, 0, 0 };

    rom.fill(0xea);

    rom[0xfffc - (0xffff - 0xbfe0)] = 0x00;
    rom[0xfffd - (0xffff - 0xbfe0)] = 0x00;
    rom[0x00] = 0xa9;
    rom[0x01] = 0x00;
    rom[0x02] = 0x8d;
    rom[0x03] = 0x00;
    rom[0x04] = 0x02;
    rom[0x05] = 0xa9;
    rom[0x06] = 0x05;
    rom[0x07] = 0x8d;
    rom[0x08] = 0x01;
    rom[0x09] = 0x02;
    rom[0x0a] = 0xa9;
    rom[0x0b] = 0x08;
    rom[0x0c] = 0x8d;
    rom[0x0d] = 0x02;
    rom[0x0e] = 0x02; 


    cpu.clearPC();
    for(int i = 0; i < 2; i++) {
        cpu.addrBusLoadFromResetVector(i == 0);
        bus.data = rom[bus.address - (0xffff - 0xbfe0)];
        cpu.dataBusWriteToPC(i == 0);
    }


    CPU::Instruction* inst;
    uint16_t ramAddress = 0;

    while(true) {
        if(rom[cpu.registers.PC] == 0xea) {
            break;
        }

        inst = getNextInstruction(ramAddress);

        if(inst->mode == CPU::AddressingMode::Immediate) {
            bus.data = (uint8_t)(0x00ff & ramAddress);
        } else if(inst->rw == CPU::rwSignal::read) {
            bus.data = ram[ramAddress];
        } else if(inst->rw == CPU::rwSignal::write) {
            ram[ramAddress] = bus.data;
        }

        (cpu.*(inst->exec))();

        cpu.addToPC(inst->size);
    }

    printf("%x\n", cpu.registers.A);
}


CPU::Instruction* Emulator::Core::getNextInstruction(uint16_t& ramAddress) {
    cpu.addrBusLoadFromPC();

    uint16_t pc = bus.address;
    uint8_t opCode = rom[pc];
    CPU::Instruction* inst = &cpu.instructionTable[opCode];
    std::array<uint16_t, 3> instBytes;

    for(int i = pc; i < pc + inst->size; i++) {
        instBytes[i - pc] = rom[i];
    }

    ramAddress = (instBytes[1]) | (instBytes[2] << 8);

    return inst;
}
