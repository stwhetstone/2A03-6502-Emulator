#include <iostream>

#include "cpu.hpp"

CPU::Core::Core(Emulator::MainBus &t_bus) : bus(t_bus) {
    this->registers = {0, 0, 0, 0xFD, 0b00101100, 0xFFFC};


    // LDA
    instructionTable[0xa9] = { 2, 2, RWSignal::read, AddressingMode::Immediate, &Core::LDA};
    instructionTable[0xa5] = { 2, 3, RWSignal::read, AddressingMode::ZeroPage, &Core::LDA};
    instructionTable[0xb5] = { 2, 4, RWSignal::read, AddressingMode::ZeroPageIndexedX, &Core::LDA};
    instructionTable[0xad] = { 3, 4, RWSignal::read, AddressingMode::Absolute, &Core::LDA};
    instructionTable[0xbd] = { 3, 4, RWSignal::read, AddressingMode::AbsoluteIndexedX, &Core::LDA};
    instructionTable[0xb9] = { 3, 4, RWSignal::read, AddressingMode::AbsoluteIndexedY, &Core::LDA};
    instructionTable[0xa1] = { 2, 6, RWSignal::read, AddressingMode::IndirectIndexedX, &Core::LDA};
    instructionTable[0xb1] = { 2, 5, RWSignal::read, AddressingMode::IndirectIndexedY, &Core::LDA};

    // STA
    instructionTable[0x85] = { 2, 3, RWSignal::write, AddressingMode::ZeroPage, &Core::STA};
    instructionTable[0x95] = { 2, 4, RWSignal::write, AddressingMode::ZeroPageIndexedX, &Core::STA};
    instructionTable[0x8d] = { 3, 4, RWSignal::write, AddressingMode::Absolute, &Core::STA};
    instructionTable[0x9d] = { 3, 5, RWSignal::write, AddressingMode::AbsoluteIndexedX, &Core::STA};
    instructionTable[0x99] = { 3, 5, RWSignal::write, AddressingMode::AbsoluteIndexedY, &Core::STA};
    instructionTable[0x81] = { 2, 6, RWSignal::write, AddressingMode::IndexedIndirectX, &Core::STA};
    instructionTable[0x91] = { 2, 6, RWSignal::write, AddressingMode::IndirectIndexedX, &Core::STA};
}



void CPU::Core::addToPC(uint8_t add) {
    registers.PC += add;
}


void CPU::Core::clearPC() {
    registers.PC = 0xffff;
}


void CPU::Core::incrementPC() {
    registers.PC++;
}


void CPU::Core::writeDataBusToPc(bool isLeastSigByte) {
    if(isLeastSigByte) {
        registers.PC &= bus.data;
        return;
    }

    registers.PC |= (bus.data << 8);
}


void CPU::Core::writePcToAddrBus() {
    bus.address = registers.PC;
}


void CPU::Core::writeResetVectorToAddrBus(bool isFirstByte) {
    if(isFirstByte) {
        bus.address = resetVector[0];
        return;
    }

    bus.address = resetVector[1];
}



void CPU::Core::ADC() {

}

void CPU::Core::AND() {

}

void CPU::Core::ASL() {

}

void CPU::Core::BCC() {

}

void CPU::Core::BCS() {

}

void CPU::Core::BEQ() {

}

void CPU::Core::BIT() {

}

void CPU::Core::BMI() {

}

void CPU::Core::BNE() {

}

void CPU::Core::BPL() {

}

void CPU::Core::BRK() {

}

void CPU::Core::BVC() {

}

void CPU::Core::BVS() {

}

void CPU::Core::CLC() {

}

void CPU::Core::CLD() {

}

void CPU::Core::CLI() {

}

void CPU::Core::CLV() {

}

void CPU::Core::CMP() {

}

void CPU::Core::CPX() {

}

void CPU::Core::CPY() {

}

void CPU::Core::DEC() {

}

void CPU::Core::DEX() {

}

void CPU::Core::DEY() {

}

void CPU::Core::EOR() {

}

void CPU::Core::INC() {

}

void CPU::Core::INX() {

}

void CPU::Core::INY() {

}

void CPU::Core::JMP() {

}

void CPU::Core::JSR() {

}

void CPU::Core::LDA() {
    registers.A = bus.data;
}

void CPU::Core::LDY() {

}

void CPU::Core::LSR() {

}

void CPU::Core::NOP() {

}

void CPU::Core::ORA() {

}

void CPU::Core::PHA() {

}

void CPU::Core::PHP() {

}

void CPU::Core::PLA() {

}

void CPU::Core::PLP() {

}

void CPU::Core::ROL() {

}

void CPU::Core::ROR() {

}

void CPU::Core::RTI() {

}

void CPU::Core::RTS() {

}

void CPU::Core::SBC() {

}

void CPU::Core::SEC() {

}

void CPU::Core::SED() {

}

void CPU::Core::SEI() {

}

void CPU::Core::STA() {
    bus.data = registers.A;
}

void CPU::Core::STX() {

}

void CPU::Core::STY() {

}

void CPU::Core::TAX() {

}

void CPU::Core::TAY() {

}

void CPU::Core::TSX() {

}

void CPU::Core::TXA() {

}

void CPU::Core::TXS() {

}

void CPU::Core::TYA() {

}

