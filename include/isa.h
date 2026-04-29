#pragma once

//different instruction formats
enum class InstructionType {

    rFormat, iFormat, sFormat, bFormat, jFormat, uFormat, UNKNOWN


};

//each instruction type has these componenets exclusive or not
struct Instruction {

    //no need for character array since this is after decoding we only need 
    //integer values
    int opcode;
    int rd;
    int rs1;
    int rs2;
    int immediate;
    int funct3;
    int funct7;
    InstructionType type;


};

