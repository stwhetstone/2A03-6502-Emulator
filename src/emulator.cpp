#include <cstddef>
#include <iostream>

#include "emulator.hpp"
#include "cpu.hpp"
#include "cpu_types.hpp"


Emulator::Core::Core() : cpu(this->bus), rom(this->bus) {
    rom.textToByteFile("assembly/test");
    bus = { 0, 0, CPU::RWSignal::read, 0, 0 };

    //cpu.clearPC();
    //for(int i = 0; i < 2; i++) {
        //cpu.addrBusLoadFromResetVector(i == 0);
        //bus.data = rom[bus.address - (0xffff - 0xbfe0)];
        //cpu.dataBusWriteToPC(i == 0);
    //}

    // fix later
    cpu.registers.PC = 0;


    CPU::Instruction* inst;
    uint16_t ramAddress = 0;

    while(true) {
        inst = getNextInstruction(&ramAddress);
        if(inst == nullptr) { 
            break;
        }


        if(inst->mode == CPU::AddressingMode::Immediate) {
            bus.data = (uint8_t)(0x00ff & ramAddress);
        } else if(bus.rw == CPU::RWSignal::read) {
            bus.data = ram[ramAddress];
        }

        (cpu.*(inst->exec))();

        if(bus.rw == CPU::RWSignal::write) {
            ram[ramAddress] = bus.data;
        }

        cpu.addToPC(inst->size);
    }

    printf("%x %x %x\n", cpu.registers.A, cpu.registers.X, cpu.registers.Y);
}


CPU::Instruction* Emulator::Core::getNextInstruction(uint16_t* ramAddress) {
    cpu.writePcToAddrBus();
    uint16_t pc = bus.address;


    if(rom.writeByteFromPcToDataBus(pc) == -1) {
        return nullptr;
    }
    uint8_t opCode = bus.data;
    CPU::Instruction* inst = &cpu.instructionTable[opCode];
    std::array<uint16_t, 3> instBytes;

    for(int i = pc; i < pc + inst->size; i++) {
        if(rom.writeByteFromPcToDataBus(i) == -1) {
            inst = nullptr;
            return inst;
        }

        instBytes[i - pc] = bus.data;
    }

    *ramAddress = (instBytes[1]) | (instBytes[2] << 8);

    bus.rw = inst->rw;

    return inst;
}
