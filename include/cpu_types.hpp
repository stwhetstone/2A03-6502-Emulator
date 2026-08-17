#include <cstdint>  
#include <functional>


#ifndef CPU_TYPES_HPP 
#define CPU_TYPES_HPP  


namespace CPU {
    typedef struct Registers {
        uint8_t A, X, Y, S, P;
        uint16_t PC;
    } Registers;

    enum RegisterName {
        A, X, Y, S, P, PC
    };
    
    enum StatusFlag {
        C, Z, I, D, B, One, V, N
    };


    enum AddressingMode {
        Absolute,
        Accumulator,
        Immediate,
        Implied,
        Indirect,
        Relative,
        ZeroPage,
        AbsoluteIndexedX,
        AbsoluteIndexedY,
        IndexedIndirectX,
        IndexedIndirectY,
        IndirectIndexedX,
        IndirectIndexedY,
        ZeroPageIndexedX,
        ZeroPageIndexedY
    };


    class Core;
    // rw
    //  0 = read 
    //  1 = write 
    //  2 = read then write
    typedef struct Instruction {
        uint8_t size, cycles, rw;
        AddressingMode mode;
        void (Core::*exec)(void) = nullptr;
    } Instruction;

};


#endif // !CPU_TYPES_HPP 
