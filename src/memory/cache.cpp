#include "../../include/cache.h"
#include "../../include/memory.h"

bool cache_load(Cache& cache, Memory& mem, uint32_t address, uint32_t& result) {
    int offset = (address >> 2) & 0x7;
    int index  = (address >> 5) & 0xF;
    int tag    = (address >> 9);

    // check each way for a hit
    for(int way = 0; way < Cache::WAYS; way++) {
        if(cache.lines[index][way].valid && cache.lines[index][way].tag == tag) {
            // HIT!
            result = cache.lines[index][way].data[offset];
            cache.hits++;
            return true;
        }
    }

    // MISS — load from memory into cache
    cache.misses++;

    // pick way to replace (simple: always use way 0)
    CacheLine& line = cache.lines[index][0];
    line.valid = true;
    line.tag = tag;

    // load 8 words from memory into cache line
    uint32_t base = address & ~0x1F; // align to cache line
    for(int i = 0; i < 8; i++) {
        line.data[i] = (mem.load(base + i*4))
                     | (mem.load(base + i*4 + 1) << 8)
                     | (mem.load(base + i*4 + 2) << 16)
                     | (mem.load(base + i*4 + 3) << 24);
    }

    result = line.data[offset];
    return false;
}

void cache_store(Cache& cache, Memory& mem, uint32_t address, uint32_t value) {
    int offset = (address >> 2) & 0x7;
    int index  = (address >> 5) & 0xF;
    int tag    = (address >> 9);

    // write to memory always (write-through policy)
    mem.store(address, value);

    // update cache if line exists
    for(int way = 0; way < Cache::WAYS; way++) {
        if(cache.lines[index][way].valid && cache.lines[index][way].tag == tag) {
            cache.lines[index][way].data[offset] = value;
            return;
        }
    }
}