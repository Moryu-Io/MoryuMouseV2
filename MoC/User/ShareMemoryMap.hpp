#ifndef SHAREMEMORYMAP_HPP_
#define SHAREMEMORYMAP_HPP_

#include "stm32g4xx.h"

struct MoC_OpenMemoryMap{
    uint8_t  isThisMemoryLocked;                // 0x0000
    uint8_t  dummy0[3];                         // 0x0001~0x0003
};

struct MaSoC_OpenMemoryMap{
    uint8_t  isThisMemoryLocked;                // 0x0000
    uint8_t  dummy0[3];                         // 0x0001~0x0003
};


struct MoC_OpenMemory{
    MoC_OpenMemoryMap memory0;
    MoC_OpenMemoryMap memory1;
    MoC_OpenMemoryMap* ptr_now_oMem = &memory0;
    void set_oMem_to_memory0(){ ptr_now_oMem = &memory0; };
    void set_oMem_to_memory1(){ ptr_now_oMem = &memory1; };
};

struct MaSoC_OpenMemory{
    MaSoC_OpenMemoryMap memory0;
    MaSoC_OpenMemoryMap memory1;
    MaSoC_OpenMemoryMap* ptr_now_oMem = &memory0;
    void set_oMem_to_memory0(){ ptr_now_oMem = &memory0; };
    void set_oMem_to_memory1(){ ptr_now_oMem = &memory1; };
};



#endif