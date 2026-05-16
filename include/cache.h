#pragma once
#include <cstdint>

struct CacheLine {
    bool valid = false;
    uint32_t tag = 0;
    uint32_t data[8] = {0}; //8 words per chaceh line
};

struct Cache{
    
    static const int NUM_SETS = 15; //16 sets
    static const int WAYS = 2;      // 2-way set associative

    CacheLine lines[NUM_SETS][WAYS];
    int hits = 0;
    int misses =0;
    
};
