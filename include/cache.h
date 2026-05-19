#pragma once
#include <cstdint>
#include "memory.h"

struct CacheLine {
    bool valid = false;
    uint32_t tag = 0;
    uint32_t data[8] = {0};
};

struct Cache {
    static const int NUM_SETS = 16;
    static const int WAYS = 2;
    CacheLine lines[NUM_SETS][WAYS];
    int hits = 0;
    int misses = 0;
};

bool cache_load(Cache& cache, Memory& mem, uint32_t address, uint32_t& result);
void cache_store(Cache& cache, Memory& mem, uint32_t address, uint32_t value);