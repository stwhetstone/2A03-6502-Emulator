#include <array>

#include "cpu_types.hpp"
#include "emulator_types.hpp"


#ifndef CPU_HPP
#define CPU_HPP

namespace CPU {
    class Core {
        public:
        Registers registers;
        Emulator::MainBus &bus;

        std::array<Instruction, 255> instructionTable;
        const std::array<uint16_t, 2> resetVector = {0x0, 0x0};


        Core(Emulator::MainBus &t_bus);

        void addToPC(uint8_t add);
        void clearPC();
        void incrementPC();
        void updateStatusRegister(StatusFlag flag, bool isSet);

        void writeDataBusToPc(bool isLeastSigByte);
        void writePcToAddrBus();
        void writeResetVectorToAddrBus(bool isFirstByte);


        // Instructions 
        void ADC();
        void AND();
        void ASL();
        void BCC();
        void BCS();

        void BEQ();
        void BIT();
        void BMI();
        void BNE();
        void BPL();

        void BRK();
        void BVC();
        void BVS();
        void CLC();
        void CLD();

        void CLI();
        void CLV();
        void CMP();
        void CPX();
        void CPY();

        void DEC();
        void DEX();
        void DEY();
        void EOR();
        void INC();

        void INX();
        void INY();
        void JMP();
        void JSR();

        void LDA(); // load value from memory into A register
        void LDX(); // load value from memory into X register
        void LDY(); // load value from memory into Y register
        void LSR();
        void NOP();
        void ORA();

        void PHA();
        void PHP();
        void PLA();
        void PLP();
        void ROL();

        void ROR();
        void RTI();
        void RTS();
        void SBC();
        void SEC();

        void SED();
        void SEI();
        void STA(); // store A register in memory
        void STX(); // store X register in memory
        void STY(); // store Y register in memory

        void TAX();
        void TAY();
        void TSX();
        void TXA();
        void TXS();

        void TYA();
    };
};

#endif
