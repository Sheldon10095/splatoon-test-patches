#pragma once

#include "types.h"

// #include <cstring>

#include <whb/log.h>
#include <whb/log_module.h>
#include <whb/log_cafe.h>
#include <whb/log_udp.h>


#include <patcher/rplinfo.h>
#include <patcher/patcher.h>

#include <kernel/kernel.h>

#include <coreinit/title.h>
#include <coreinit/cache.h>
#include <coreinit/memorymap.h>

#undef DECL_FUNCTION
#include <function_patcher/function_patching.h>


#define SPLATOON_TID_J 0x0005000010162B00
#define SPLATOON_TID_U 0x0005000010176900
#define SPLATOON_TID_E 0x0005000010176A00

#define SPLATOON_TID SPLATOON_TID_J, SPLATOON_TID_U, SPLATOON_TID_E


extern std::optional<rplinfo> gRPLInfo;


namespace Splatoon
{
    void ApplyPatches();
}