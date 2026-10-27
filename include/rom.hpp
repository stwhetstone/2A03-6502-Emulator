#include <vector>
#include <cstdint>

#include "emulator_types.hpp"

#ifndef ROM_HPP
#define ROM_HPP

namespace ROM {
    class Core {
        public:
        Emulator::MainBus &bus;

        Core(Emulator::MainBus &t_bus);

        char dataBusLoadByteFromPC(uint16_t pc);
        void textToByteFile(std::string fileName);

        private:
        std::vector<uint8_t> _bytes;
        int _size;
    };
}

#endif
