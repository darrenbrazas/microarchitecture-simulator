#include "../../include/isa.h"
#include "../../include/registers.h"
#include "../../include/memory.h"
#include "../../include/decode.h"

//single cycle cpu that takes in parameters of memory and register file
void run_single_cycle(Memory& mem, RegisterFile& rf){


    //we would like it to start from pc = 0

    int programCounter = 0;

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
                    rf.write(instruction.rd, val1 + val2);

                }



                break; 

       

            case 0x13:

        

            case 0x03:

        

            case 0x23:


            case 0x63:

        

            case 0x6F:
        

            case 0x37:
            case 0x17:


            default:
        

        }

    }
    
};