#include "ShareMemoryMap.hpp"


static MoC_OpenMemory moc_memory = {
    .memory0 = {
        0,
        0,
        0,
        0
    },
    .memory1 = {
    
    }
};

static MaSoC_OpenMemory masoc_memory = {
    .memory0 = {
        0,
        0,
        0,
        0
    },
    .memory1 = {
    
    }
};


MoC_OpenMemory* get_ptr_MoC_OpenMemory(){ return &moc_memory; }
MaSoC_OpenMemory* get_ptr_MaSoC_OpenMemory(){ return &masoc_memory; }
