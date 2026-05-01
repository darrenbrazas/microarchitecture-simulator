#pragma once
#include <cstdint>

/* The FOLLOWING Loop will be implemented in RISC-V Assembly



# x1 = 0  (sum)
# x2 = 0  (counter i)
# x3 = 10 (limit)

addi x1, x0, 0     # sum = 0
addi x2, x0, 0     # i = 0
addi x3, x0, 10    # limit = 10

loop:
add  x1, x1, x2    # sum = sum + i
addi x2, x2, 1     # i++
bne  x2, x3, loop  # if i != 10, loop back

*/

uint32_t loop_sum[] = {
    0x00000093, // addi x1, x0, 0
    0x00000113, // addi x2, x0, 0
    0x00A00193,  // addi x3, x0, 10

    0x002080B3, // add  x1, x1, x2   (sum = sum + i)
    0x00110113, // addi x2, x2, 1    (i++)
    0xFE311CE3, // bne  x2, x3, -8   (if i != 10, loop)

    0x00000000
};




