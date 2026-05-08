#pragma once
struct RegisterFile {

    int regs[32] = {0};

    //read, thus return whatever is in array
    int read(int reg) {

        return regs[reg];

    }

    void write(int reg, int value) {

        if(reg != 0) {

            regs[reg] = value;
        }

    }


};

