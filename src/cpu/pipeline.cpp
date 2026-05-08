#include "../../include/isa.h"
#include "../../include/registers.h"
#include "../../include/memory.h"
#include "../../include/decode.h"
#include "../../include/pipeline.h"
#include <iostream>

void WB(MEM_WB& mem_wb, RegisterFile& rf, int& instructions) {
    if(!mem_wb.valid) return;

    Instruction inst = mem_wb.inst;

    // if load, write memory data
    // otherwise write ALU result
    if(inst.opcode == 0x03) {
        rf.write(inst.rd, mem_wb.memData);
    } else {
        rf.write(inst.rd, mem_wb.result);
    }

    instructions++;
}

void MEM(EX_MEM& ex_mem, MEM_WB& mem_wb, Memory& mem) {
    mem_wb.valid = ex_mem.valid;
    if(!ex_mem.valid) return;

    mem_wb.inst = ex_mem.inst;
    mem_wb.pc = ex_mem.pc;
    mem_wb.result = ex_mem.result;

    // handle load
    if(ex_mem.inst.opcode == 0x03) {
        mem_wb.memData = mem.load(ex_mem.result);
    }
    // handle store
    else if(ex_mem.inst.opcode == 0x23) {
        mem.store(ex_mem.result, ex_mem.rs2_val);
        mem_wb.valid = false; // stores don't writeback
    }
}

void EX(ID_EX& id_ex, EX_MEM& ex_mem, IF_ID& if_id, int& programCounter, int& numFlushes) {
    ex_mem.valid = id_ex.valid;
    if(!id_ex.valid) return;

    ex_mem.inst = id_ex.inst;
    ex_mem.pc = id_ex.pc;
    ex_mem.rs2_val = id_ex.rs2_val;

    int val1 = id_ex.rs1_val;
    int val2 = id_ex.rs2_val;
    int imm = id_ex.inst.immediate;

    switch(id_ex.inst.opcode) {
        case 0x33: // R-type
            if(id_ex.inst.funct3 == 0x0 && id_ex.inst.funct7 == 0x00)
                ex_mem.result = val1 + val2;
            else if(id_ex.inst.funct3 == 0x0 && id_ex.inst.funct7 == 0x20)
                ex_mem.result = val1 - val2;
            break;
        case 0x13: // I-type ALU
            if(id_ex.inst.funct3 == 0x0)
                ex_mem.result = val1 + imm;
            break;
        case 0x03: // LW - calculate address
        case 0x23: // SW - calculate address
            ex_mem.result = val1 + imm;
            break;
        default:
            ex_mem.result = 0;
            break;
    }

    //branch handling
    //branch opcode (B-type)
    if(id_ex.inst.opcode == 0x63) {


        int val1 = id_ex.rs1_val;
        int val2 = id_ex.rs2_val;
        bool taken = false;

        if(id_ex.inst.funct3 == 0x0 && val1 == val2){
            taken = true; //BEQ
        }

        if(id_ex.inst.funct3 == 0x1 && val1 != val2){
            taken = true; //BNE
        }

        if(taken) {
            //if branch taken then we flush IF and ID and move the program counter to the branched location
            //increment number of flushes
            programCounter = id_ex.pc + (id_ex.inst.immediate / 4);
            if_id.valid = false;
            id_ex.valid = false;
            numFlushes++;
        }

    }
    
}

void ID(IF_ID& if_id, ID_EX& id_ex, RegisterFile& rf) {
    id_ex.valid = if_id.valid;
    if(!if_id.valid) return;

    id_ex.inst = if_id.inst;
    id_ex.pc = if_id.pc;
    id_ex.rs1_val = rf.read(if_id.inst.rs1);
    id_ex.rs2_val = rf.read(if_id.inst.rs2);
}

void IF(IF_ID& if_id, Memory& mem, int& programCounter, bool& running) {
    uint32_t raw = (mem.load(programCounter*4))
                |  (mem.load(programCounter*4 + 1) << 8)
                |  (mem.load(programCounter*4 + 2) << 16)
                |  (mem.load(programCounter*4 + 3) << 24);

    if(raw == 0) {
        if_id.valid = false;
        running = false;
        return;
    }

    if_id.inst = decode(raw);
    if_id.pc = programCounter;
    if_id.valid = true;
    programCounter++;
}

bool hazard_detection(ID_EX& id_ex, EX_MEM& ex_mem, IF_ID& if_id) {

    if(!id_ex.valid) return false;
    if(id_ex.inst.rd == 0) return false;

    //returns true if a harzard is detected.
    if (id_ex.inst.rd == if_id.inst.rs1) return true;
    if (id_ex.inst.rd == if_id.inst.rs2) return true;

    return false;

}
void  run_pipeline(Memory& mem, RegisterFile& rf){

    //copied and pasted from single cycle cpu
    int programCounter = 0;
    int cycles = 0;
    int instructionCount = 0;
    int numStalls = 0;
    int numFlushes = 0;

    bool running = true;

    //declare the pipeline registers

    IF_ID if_id;
    ID_EX id_ex;
    EX_MEM ex_mem;
    MEM_WB mem_wb;


    while(running){

    
        //WB
        WB(mem_wb, rf, instructionCount);
        
        //MEM
        MEM(ex_mem, mem_wb, mem);

        //EX
        EX(id_ex, ex_mem, if_id, programCounter, numFlushes);

        //Insert Hazard Detection

        if(hazard_detection(id_ex, ex_mem, if_id) == true) {

            //if it returns true that means a hazard detection was discovered thus we have to stall/bubble

            id_ex.valid = false;
            numStalls++;
        } else {

            //otherwise there is no hazard detection continue as needed
 
            //ID
            ID(if_id, id_ex, rf);

            //IF
            IF(if_id, mem, programCounter, running);
        }

        cycles++;
    }

    // drain remaining instructions in pipeline
    for(int i = 0; i < 4; i++) {
        WB(mem_wb, rf, instructionCount);
        MEM(ex_mem, mem_wb, mem);
        EX(id_ex, ex_mem, if_id, programCounter, numFlushes);
        ID(if_id, id_ex, rf);
        cycles++;
    }

    //metrics

    std::cout << "x1 (sum) = " << rf.read(1) << "\n";
    std::cout << "\n=== Pipeline Metrics ===\n";
    std::cout << "Cycles:       " << cycles << "\n";
    std::cout << "Instructions: " << instructionCount << "\n";
    std::cout << "CPI:          " << (float)cycles / instructionCount << "\n";
    std::cout << "Stalls:       " << numStalls << "\n";
    std::cout << "Flushes:      " << numFlushes << "\n";

}