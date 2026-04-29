#include <cstdint>
#include "isa.h"

InstructionType decode_instruction_type(uint32_t raw) {

    //in order to extract the lower 7 bits to determine the type of instruction
    //we can perform bitwise operations, such as performing
    //the AND operation  with the mask will change every bit to zero except
    // the first 7 bits then compare bits with actual op code 

    int mask = 0x7F;
    int opcode = raw & mask;

    //actual decoder

    switch(opcode)
    {

        case 0x33:

        return InstructionType::rFormat;

        case 0x13:

        return InstructionType::iFormat;

        case 0x03:

        return InstructionType::iFormat;

        case 0x23:

        return InstructionType::sFormat;

        case 0x63:

        return InstructionType::bFormat;

        case 0x6F:
        return InstructionType::jFormat;

        case 0x37:
        case 0x17:
        return InstructionType::uFormat;

        default:
        return InstructionType::uFormat;
    }

};
