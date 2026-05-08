#pragma once
#include "isa.h"

struct IF_ID {
    Instruction inst;
    int pc;
    bool valid = false;
};

struct ID_EX {
    Instruction inst;
    int pc;
    int rs1_val;
    int rs2_val;
    bool valid = false;
};

struct EX_MEM {

    Instruction inst;
    int pc;
    int result;
    int rs2_val;
    bool valid = false;
};

struct MEM_WB {

    Instruction inst;
    int pc;
    int result;
    int memData;
    bool valid = false;
};