#include <cstdint>
#include "isa.h"

InstructionType decode_instruction_type(uint32_t raw) {

    //in order to extract the lower 7 bits to determine the type of instruction
    //we can perform bitwise operations, such as performing
    //the AND operation  with the mask will change every bit to zero except
    // the first 7 bits then compare bits with actual op code

    int mask = 0x7F;
    int opcode = raw & mask;

    //actual decoder for instruction type uses switch statement

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

//decoding registers in full instruction
Instruction decode(uint32_t raw) {


    Instruction inst;

    inst.type = decode_instruction_type(raw);
    //these registers stay the same
    inst.opcode =  (raw & 0x7F);
    inst.rd = (raw & 0xF80) >> 7;
    inst.rs1 = (raw & 0xF8000) >> 15;
    inst.rs2 = (raw & 0x1F00000) >> 20;

    //funct3 and funct7

    inst.funct3 = (raw & 0x7000) >> 12;
    inst.funct7 = (raw & 0xFE000000) >> 25;

    //different instruction formats have different immediate value placements
    //here i shifted bits first then masked
    if(inst.type == InstructionType::iFormat){

        inst.immediate = (raw >> 20) & 0x0FFF;

    }else if (inst.type == InstructionType::sFormat){

        inst.immediate = ((raw >> 25) & 0x7F) << 5 | ((raw >> 7) & 0x1F);

    }else if (inst.type == InstructionType::bFormat){

        inst.immediate = ((raw >> 31) & 0x1) << 12
                       | ((raw >> 7)  & 0x1) << 11
                       | ((raw >> 25) & 0x3F) << 5
                       | ((raw >> 8)  & 0xF)  << 1;

    } else if(inst.type == InstructionType::uFormat){

        inst.immediate = (raw >> 12) & 0xFFFFF;

    } else if(inst.type == InstructionType::jFormat){

        inst.immediate = ((raw >> 31) & 0x1)   << 20
                       | ((raw >> 12) & 0xFF)   << 12
                       | ((raw >> 20) & 0x1)    << 11
                       | ((raw >> 21) & 0x3FF)  << 1;

    } else {
        inst.immediate = 0;
    }

    return inst;

}
