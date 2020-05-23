#include "OpenMemoryMap.hpp"


#ifdef MOC_MICON
static MoC_OpenMemory moc_memory = {
    .memory0 = {
        .header = MMT_MOC_HEADER,
        .isThisMemoryLocked = 0,
        .dummy0 = {},
        .footer = MMT_MOC_FOOTER
    }
};

static MaSoC_OpenMemory masoc_memory = {
    .memory0 = {
        .header = MMT_MASOC_HEADER,
        .isThisMemoryLocked = 0x96,
        .dummy0 = {},
        .footer = MMT_MASOC_FOOTER
    },
    .memory1 = {
        .header = MMT_MASOC_HEADER,
        .isThisMemoryLocked = 0x96,
        .dummy0 = {},
        .footer = MMT_MASOC_FOOTER
    }
};
#else
static MoC_OpenMemory moc_memory = {
    .memory0 = {
        .header = MMT_MOC_HEADER,
        .isThisMemoryLocked = 0,
        .dummy0 = {},
        .footer = MMT_MOC_FOOTER
    },
    .memory1 = {
        .header = MMT_MOC_HEADER,
        .isThisMemoryLocked = 0x96,
        .dummy0 = {},
        .footer = MMT_MOC_FOOTER
    }
};

static MaSoC_OpenMemory masoc_memory = {
    .memory0 = {
        .header = MMT_MASOC_HEADER,
        .isThisMemoryLocked = 0x96,
        .dummy0 = {},
        .footer = MMT_MASOC_FOOTER
    }
};
#endif

MoC_OpenMemory* get_ptr_MoC_OpenMemory(){ return &moc_memory; }
MaSoC_OpenMemory* get_ptr_MaSoC_OpenMemory(){ return &masoc_memory; }
