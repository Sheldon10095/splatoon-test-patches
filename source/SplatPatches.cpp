#include "SplatPatches.hpp"

namespace Splatoon
{
    void ApplyPatches()
    {
        auto gambit_rpx = FindRPL(*gRPLInfo, "Gambit.rpx");
        if (!gambit_rpx)
        {
            WHBLogPrintf("rce_patches: Couldn't find Gambit.rpx ...");
            return;
        }
    }
}