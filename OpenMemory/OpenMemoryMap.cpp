#include "OpenMemoryMap.hpp"


#ifdef MOC_MICON
static MoC_OpenMemory moc_memory = {
    .memory0 = {
        .header = MMT_MOC_HEADER,
        .u32_nowMMT_CNT = 0,
        .u8_dummy00 = {},
        .flt_nowPos_X = 0.0f,
        .flt_nowPos_Y = 0.0f,
        .flt_nowPos_THETA = 0.0f,
        .u16_rEncCNT = 0,
        .u16_lEncCNT = 0,
        .u8_dummy01 = {},
        .footer = MMT_MOC_FOOTER
    }
};

static MaSoC_OpenMemory masoc_memory = {
    .memory0 = {
        .header = MMT_MASOC_HEADER,
        .u32_nowMMT_CNT = 0,
        .u8_dummy00 = {},
        .flt_WallDistance_Right = 0.0f,
        .flt_WallDistance_Left = 0.0f,
        .flt_WallDistance_Front = 0.0f,
        .u8_dummy01 = {},
        .footer = MMT_MASOC_FOOTER
    },
    .memory1 = {
        .header = MMT_MASOC_HEADER,
        .u32_nowMMT_CNT = 0,
        .u8_dummy00 = {},
        .flt_WallDistance_Right = 0.0f,
        .flt_WallDistance_Left = 0.0f,
        .flt_WallDistance_Front = 0.0f,
        .u8_dummy01 = {},
        .footer = MMT_MASOC_FOOTER
    }
};
#else
static MoC_OpenMemory moc_memory = {
    .memory0 = {
        .header = MMT_MOC_HEADER,
        .u32_nowMMT_CNT = 0,
        .u8_dummy00 = {},
        .flt_nowPos_X = 0.0f,
        .flt_nowPos_Y = 0.0f,
        .flt_nowPos_THETA = 0.0f,
        .u16_rEncCNT = 0,
        .u16_lEncCNT = 0,
        .u8_dummy01 = {},
        .footer = MMT_MOC_FOOTER
    },
    .memory1 = {
        .header = MMT_MOC_HEADER,
        .u32_nowMMT_CNT = 0,
        .u8_dummy00 = {},
        .flt_nowPos_X = 0.0f,
        .flt_nowPos_Y = 0.0f,
        .flt_nowPos_THETA = 0.0f,
        .u16_rEncCNT = 0,
        .u16_lEncCNT = 0,
        .u8_dummy01 = {},
        .footer = MMT_MOC_FOOTER
    }
};

static MaSoC_OpenMemory masoc_memory = {
    .memory0 = {
        .header = MMT_MASOC_HEADER,
        .u32_nowMMT_CNT = 0,
        .u8_dummy00 = {},
        .flt_WallDistance_Right = 0.0f,
        .flt_WallDistance_Left = 0.0f,
        .flt_WallDistance_Front = 0.0f,
        .u8_dummy01 = {},
        .footer = MMT_MASOC_FOOTER
    }
};
#endif

MoC_OpenMemory* get_ptr_MoC_OpenMemory(){ return &moc_memory; }
MaSoC_OpenMemory* get_ptr_MaSoC_OpenMemory(){ return &masoc_memory; }
