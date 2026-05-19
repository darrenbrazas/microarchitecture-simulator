#pragma once
#include <cstdint>

/*
RISC-V Assembly:
addi x1, x0, 100    # address = 100
addi x2, x0, 42     # value = 42
sw   x2, 0(x1)      # store 42 at address 100
lw   x3, 0(x1)      # load from address 100 into x3
lw   x4, 0(x1)      # load again → should be cache HIT!
lw   x5, 0(x1)      # load again → should be cache HIT!
*/

uint32_t memory_test[] = {
    0x06400093,  // addi x1, x0, 100
    0x02A00113,  // addi x2, x0, 42
    0x0020A023,  // sw x2, 0(x1)
    0x0000A183,  // lw x3, 0(x1)
    0x0000A203,  // lw x4, 0(x1)
    0x0000A283,  // lw x5, 0(x1)
    0x00000000   // end
};