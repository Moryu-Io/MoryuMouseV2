#ifndef SHAREMEMORYMAP_HPP_
#define SHAREMEMORYMAP_HPP_

#include "stm32g4xx.h"
#include "def_const_param.hpp"

struct MoC_OpenMemoryMap{
    uint32_t  header;
    uint32_t  isThisMemoryLocked;                // 0x0000
    uint8_t   dummy0[4];                         // 0x0001~0x0003
    uint32_t  footer;
};

struct MaSoC_OpenMemoryMap{
    uint32_t  header;
    uint32_t  isThisMemoryLocked;                // 0x0000
    uint8_t   dummy0[4];                         // 0x0001~0x0003
    uint32_t  footer;
};


#ifdef MOC_MICON
struct MoC_OpenMemory{
    MoC_OpenMemoryMap memory0;
    MoC_OpenMemoryMap* ptr_now_oMem = &memory0;
    uint32_t memory_byte_size = sizeof(MoC_OpenMemoryMap);
    void set_oMem_to_memory0(){ ptr_now_oMem = &memory0; };
};
struct MaSoC_OpenMemory{
    MaSoC_OpenMemoryMap memory0;
    MaSoC_OpenMemoryMap memory1;
    MaSoC_OpenMemoryMap* ptr_now_oMem = &memory0;
    uint32_t memory_byte_size = sizeof(MaSoC_OpenMemoryMap);
    void set_oMem_to_memory0(){ ptr_now_oMem = &memory0; };
    void set_oMem_to_memory1(){ ptr_now_oMem = &memory1; };
};
#else
struct MoC_OpenMemory{
    MoC_OpenMemoryMap memory0;
    MoC_OpenMemoryMap memory1;
    MoC_OpenMemoryMap* ptr_now_oMem = &memory0;
    uint32_t memory_byte_size = sizeof(MoC_OpenMemoryMap);
    void set_oMem_to_memory0(){ ptr_now_oMem = &memory0; };
    void set_oMem_to_memory1(){ ptr_now_oMem = &memory1; };
};
struct MaSoC_OpenMemory{
    MaSoC_OpenMemoryMap memory0;
    MaSoC_OpenMemoryMap* ptr_now_oMem = &memory0;
    uint32_t memory_byte_size = sizeof(MaSoC_OpenMemoryMap);
    void set_oMem_to_memory0(){ ptr_now_oMem = &memory0; };
};
#endif

MoC_OpenMemory* get_ptr_MoC_OpenMemory();
MaSoC_OpenMemory* get_ptr_MaSoC_OpenMemory();

#endif