#include <cstdint>
#include <array>

#include "emulator_types.hpp"
#include "cpu.hpp"


#ifndef EMULATOR_HPP
#define EMULATOR_HPP

namespace Emulator {
    class Core {
        public:
        std::array<uint8_t, 2048> ram;
        std::array<uint8_t, 0xbfe0> rom;

        MainBus bus;
        CPU::Core cpu;

        Core();

        CPU::Instruction* getNextInstruction(uint16_t& ramAddress);
    };
};

#endif // !EMULATOR_H
