#include <cstdint>  

#include "cpu_types.hpp"


#ifndef EMULATOR_TYPES_HPP 
#define EMULATOR_TYPES_HPP  


namespace Emulator {
    typedef struct MainBus {
        uint8_t data;
        uint16_t address;
        CPU::RWSignal rw;
        uint8_t nmi, irq;
    } MainBus;
};


#endif // !Emulator_TYPES_HPP 
