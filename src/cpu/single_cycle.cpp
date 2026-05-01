#include "../../include/isa.h"
#include "../../include/registers.h"
#include "../../include/memory.h"
#include "../../include/decode.h"
#include <iostream>

//single cycle cpu that takes in parameters of memory and register file
void run_single_cycle(Memory& mem, RegisterFile& rf){


    //we would like it to start from pc = 0

    int programCounter = 0;
    int cycles = 0;
    int instructionCount = 0;

    bool running = true;

    while (running)
    {
        //1. Fetch
        //each memory address takes one address (one slot) we load each byte then shift left
        /*
        byte3    byte2    byte1    byte0
        00000100 00000011 00000010 00000001

        shift byte3 left by 24: 00000100 000000000000000000000000
        shift byte2 left by 16:          00000011 0000000000000000
        shift byte1 left by 8:                    00000010 00000000
        byte0 stays:                                        00000001
        */
        uint32_t raw = (mem.load(programCounter*4))
                    |  (mem.load(programCounter*4 + 1) << 8)
                    |  (mem.load(programCounter*4 + 2) << 16)
                    |  (mem.load(programCounter*4 + 3) << 24);

        //increment program counter after
        programCounter++;

        if(raw == 0) running = false;

        //2. Decode

        Instruction instruction = decode(raw);

        //3. Execute 

        switch(instruction.opcode) {

            case 0x33:

                //add
                if(instruction.funct3 == 0x0 && instruction.funct7 == 0x00){

                    int val1 = rf.read(instruction.rs1);
                    int val2 = rf.read(instruction.rs2);
                    rf.write(instruction.rd, val1 + val2);

                }

                //sub
               
                if(instruction.funct3 == 0x0 && instruction.funct7 == 0x20){

                    int val1 = rf.read(instruction.rs1);
                    int val2 = rf.read(instruction.rs2);
                    rf.write(instruction.rd, val1 - val2);

                }

                //XOR

                if(instruction.funct3 == 0x4 && instruction.funct7 == 0x00){

                    int val1 = rf.read(instruction.rs1);
                    int val2 = rf.read(instruction.rs2);
                    rf.write(instruction.rd, val1 ^ val2);

                }

                //AND

                if(instruction.funct3 == 0x7 && instruction.funct7 == 0x00){

                    int val1 = rf.read(instruction.rs1);
                    int val2 = rf.read(instruction.rs2);
                    rf.write(instruction.rd, val1 & val2);

                }

                //OR

                if(instruction.funct3 == 0x6 && instruction.funct7 == 0x00){

                    int val1 = rf.read(instruction.rs1);
                    int val2 = rf.read(instruction.rs2);
                    rf.write(instruction.rd, val1 | val2);

                }

                //SLL
                if(instruction.funct3 == 0x1 && instruction.funct7 == 0x00){

                    int val1 = rf.read(instruction.rs1);
                    int val2 = rf.read(instruction.rs2);
                    rf.write(instruction.rd, val1 << val2);

                }

                //SRL
                if(instruction.funct3 == 0x5 && instruction.funct7 == 0x00){

                    int val1 = rf.read(instruction.rs1);
                    int val2 = rf.read(instruction.rs2);
                    rf.write(instruction.rd, val1 >> val2);

                }

                break; 

       
            //I type instructions
            case 0x13:

                //ADDI
                if(instruction.funct3 == 0x0){

                    int val1 = rf.read(instruction.rs1);
                    int immediate = instruction.immediate;
                    rf.write(instruction.rd, val1 + immediate);

                }

                //XORI
                if(instruction.funct3 == 0x4){

                    int val1 = rf.read(instruction.rs1);
                    int immediate = instruction.immediate;
                    rf.write(instruction.rd, val1 ^ immediate);

                }

                //ANDI
                if(instruction.funct3 == 0x7){

                    int val1 = rf.read(instruction.rs1);
                    int immediate = instruction.immediate;
                    rf.write(instruction.rd, val1 & immediate);

                }

                //ORI
                if(instruction.funct3 == 0x6){

                    int val1 = rf.read(instruction.rs1);
                    int immediate = instruction.immediate;
                    rf.write(instruction.rd, val1 | immediate);

                }

                break;

            //I-type LW
            case 0x03:

                if(instruction.funct3 == 0x2){

                    int val1 = rf.read(instruction.rs1);
                    int immediate = instruction.immediate;
                    int memAddr = mem.load(val1 + immediate);
                    rf.write(instruction.rd, memAddr);

                }

                break;
        
            //S-Type SW
            case 0x23:

                if(instruction.funct3 == 0x2){

                    int address = rf.read(instruction.rs1) + instruction.immediate;
                    int value = rf.read(instruction.rs2);
                    mem.store(address, value);


                }

                break;


            case 0x63:

                //BEQ
                if(instruction.funct3 == 0x0){

                    int val1 = rf.read(instruction.rs1);
                    int val2 = rf.read(instruction.rs2);

                    int zeroFlag = val1 - val2;

                    if(zeroFlag == 0){

                        programCounter = (programCounter - 1) + (instruction.immediate / 4);

                    }


                }

                //BNE
                if(instruction.funct3 == 0x1){

                    int val1 = rf.read(instruction.rs1);
                    int val2 = rf.read(instruction.rs2);

                    int zeroFlag = val1 - val2;

                    if(zeroFlag != 0){

                        programCounter = (programCounter - 1) + (instruction.immediate / 4);

                    }


                }

                break;

            case 0x6F:

                rf.write(instruction.rd, programCounter * 4);
                programCounter = (programCounter - 1) + (instruction.immediate / 4);
        
                break;
            case 0x37:

                rf.write(instruction.rd, instruction.immediate << 12);
                break;
            case 0x17:
                
                rf.write(instruction.rd, (programCounter - 1) * 4 + (instruction.immediate << 12));
                break;


            default:
                running = false;
                break;
        

        }

        if(raw != 0) instructionCount++;

        cycles++;

    }

    std::cout << "Metrics";
    std::cout << "Cycles " << cycles << "\n";
    std::cout << "Instruction Count " << instructionCount << "\n";
    std::cout << "CPI: " <<  cycles/instructionCount;
    
};