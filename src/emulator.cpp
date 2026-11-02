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

    while(true) {
        inst = getNextInstruction();
        if(inst == nullptr) { 
            break;
        }

        if(inst->mode == CPU::AddressingMode::ZeroPageIndexedX) {
            cpu.addXToAddrBusZeroPage();
        } else if(inst->mode == CPU::AddressingMode::ZeroPageIndexedY) {
            cpu.addYToAddrBusZeroPage();
        } else if(inst->mode == CPU::AddressingMode::AbsoluteIndexedX) {
            cpu.addXToAddrBus();
        } else if(inst->mode == CPU::AddressingMode::AbsoluteIndexedY) {
            cpu.addYToAddrBus();
        }


        if(inst->mode == CPU::AddressingMode::Immediate) {
            bus.data = (uint8_t)(0x00ff & bus.address);
        } else if(bus.rw == CPU::RWSignal::read) {
            bus.data = ram[bus.address];
        }

        (cpu.*(inst->exec))();

        if(bus.rw == CPU::RWSignal::write) {
            ram[bus.address] = bus.data;
        }

        cpu.addToPC(inst->size);
        printf("A: %2x X: %2x Y: %2x S: %2x\n\n", cpu.registers.A, cpu.registers.X, cpu.registers.Y, cpu.registers.S);
    }


    printf("A: %x X: %x Y: %x\n", cpu.registers.A, cpu.registers.X, cpu.registers.Y);
}


CPU::Instruction* Emulator::Core::getNextInstruction() {
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

    bus.address = (instBytes[1]) | (instBytes[2] << 8);

    bus.rw = inst->rw;

    return inst;
}
