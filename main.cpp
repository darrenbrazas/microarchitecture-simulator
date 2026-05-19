#include <iostream>

#include "include/memory.h"
#include "include/registers.h"
#include "include/decode.h"
#include "programs/memory_test.h"

void run_pipeline(Memory& mem, RegisterFile& rf);

int main() {

    Memory mem;
    RegisterFile rf;

    int program_size = sizeof(memory_test) / sizeof(memory_test[0]);

    for(int i = 0; i < program_size; i++){

  

        mem.store(i*4 + 0, (memory_test[i] >> 0)  & 0xFF);
        mem.store(i*4 + 1, (memory_test[i] >> 8)  & 0xFF);
        mem.store(i*4 + 2, (memory_test[i] >> 16) & 0xFF);
        mem.store(i*4 + 3, (memory_test[i] >> 24) & 0xFF);


    }
    
    run_pipeline(mem, rf);
    return 0;
}