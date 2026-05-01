#include <iostream>

#include "include/memory.h"
#include "include/registers.h"
#include "include/decode.h"
#include "programs/loop_sum.h"

void run_single_cycle(Memory& mem, RegisterFile& rf);

int main() {

    Memory mem;
    RegisterFile rf;

    int program_size = sizeof(loop_sum) / sizeof(loop_sum[0]);

    for(int i = 0; i < program_size; i++){

        int mask = 0xFF;

        mem.store(i*4 + 0, (loop_sum[i] >> 0) & mask);
        mem.store(i*4 + 1, (loop_sum[i] >> 8) & mask);
        mem.store(i*4 + 2, (loop_sum[i] >> 16) & mask);
        mem.store(i*4 + 3, (loop_sum[i] >> 24) & mask);


    }
    
    run_single_cycle(mem, rf);
    return 0;
}