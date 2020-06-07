#include "WST_open_info.hpp"

namespace WST{

static WST_OpenInfo wst_oInfo = {
    .u16_raw_WSPD_RightFront = 0,
    .u16_raw_WSPD_RightSide = 0,
    .u16_raw_WSPD_LeftFront = 0,
    .u16_raw_WSPD_LeftSide = 0,
};

WST_OpenInfo* get_ptr_oInfo(){
    return &wst_oInfo;
}


};