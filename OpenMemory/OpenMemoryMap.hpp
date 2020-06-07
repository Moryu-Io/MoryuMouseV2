#ifndef SHAREMEMORYMAP_HPP_
#define SHAREMEMORYMAP_HPP_

#include "stm32g4xx.h"
#include "def_const_param.hpp"

// 256Byte
struct MoC_OpenMemoryMap{
    uint32_t  header;                           // 0x0000~0x0003
    uint32_t  u32_nowMMT_CNT;                   // 0x0004~0x0007
    uint8_t   u8_dummy00[8];                    // 0x0008~0x000F
    float     flt_nowPos_X;                     // 0x0010~0x0013
    float     flt_nowPos_Y;                     // 0x0014~0x0017
    float     flt_nowPos_THETA;                 // 0x0018~0x001B
    float     flt_nowVel_X;                     // 0x001C~0x001F
    float     flt_nowVel_Y;                     // 0x0020~0x0023
    float     flt_nowAccel_X;                   // 0x0024~0x0027
    float     flt_nowAccel_Y;                   // 0x0028~0x002B
    float     flt_nowGyro_Z;                    // 0x002C~0x002F
    uint16_t  u16_rEncCNT;                      // 0x0030~0x0031
    uint16_t  u16_lEncCNT;                      // 0x0032~0x0033
    uint8_t   u8_dummy01[200];                  // 0x0034~0x00FB
    uint32_t  footer;                           // 0x00FC~0x00FF
};

struct MaSoC_OpenMemoryMap{
    uint32_t  header;                           // 0x0000~0x0003
    uint32_t  u32_nowMMT_CNT;                   // 0x0004~0x0007
    uint8_t   u8_dummy00[8];                    // 0x0008~0x000F
    float     flt_WallDistance_Right;           // 0x0010~0x0013
    float     flt_WallDistance_Left;            // 0x0014~0x0017
    float     flt_WallDistance_Front;           // 0x0018~0x001B
    uint8_t   u8_dummy01[224];                  // 0x001C~0x00FB
    uint32_t  footer;                           // 0x00FC~0x00FF
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
    MaSoC_OpenMemoryMap* ptr_now_oMem = &memory0;       // oMemは他マイコンとやり取りするメモリ
    MaSoC_OpenMemoryMap* ptr_now_rMem = &memory1;       // rMemはマイコン内で読めるメモリ
    uint32_t memory_byte_size = sizeof(MaSoC_OpenMemoryMap);
    void set_oMem_to_memory0(){ 
        ptr_now_oMem = &memory0;
        ptr_now_rMem = &memory1; };
    void set_oMem_to_memory1(){
        ptr_now_oMem = &memory1;
        ptr_now_rMem = &memory0; };
};
#else
struct MoC_OpenMemory{
    MoC_OpenMemoryMap memory0;
    MoC_OpenMemoryMap memory1;
    MoC_OpenMemoryMap* ptr_now_oMem = &memory0;       // oMemは他マイコンとやり取りするメモリ
    MoC_OpenMemoryMap* ptr_now_rMem = &memory1;       // rMemはマイコン内で読めるメモリ
    uint32_t memory_byte_size = sizeof(MoC_OpenMemoryMap);
    void set_oMem_to_memory0(){ 
        ptr_now_oMem = &memory0;
        ptr_now_rMem = &memory1; };
    void set_oMem_to_memory1(){
        ptr_now_oMem = &memory1;
        ptr_now_rMem = &memory0; };
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