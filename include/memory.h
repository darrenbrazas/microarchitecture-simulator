#include <cstdint>

struct Memory {

    uint8_t memory[65536] = {0}; // 64KB

    //load memory address 
    int load(uint32_t address){

        return memory[address];

    };

    //void type function so it should not return a data type (void)
    void store(uint16_t address, int value){

        

            memory[address] = value;
        

    };
};