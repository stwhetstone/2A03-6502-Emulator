#include <cstdint>
#include <array>

#include "emulator_types.hpp"
#include "cpu.hpp"
#include "rom.hpp"


#ifndef EMULATOR_HPP
#define EMULATOR_HPP

namespace Emulator {
    class Core {
        public:
        std::array<uint8_t, 2048> ram;

        MainBus bus;
        CPU::Core cpu;
        ROM::Core rom;

        Core();

        CPU::Instruction* getNextInstruction(uint16_t* ramAddress);
    };
};

#endif
