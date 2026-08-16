#include <cstdint>  


#ifndef EMULATOR_TYPES_HPP 
#define EMULATOR_TYPES_HPP  


namespace Emulator {
    // rw
    //  0 = read 
    //  1 = write 
    //  2 = read then write
    typedef struct MainBus {
        uint8_t data;
        uint16_t address;
        uint8_t rw, nmi, irq;
    } MainBus;
};


#endif // !Emulator_TYPES_HPP 
