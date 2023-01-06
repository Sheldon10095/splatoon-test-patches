#include "SplatPatches.hpp"
#include "CodePatchUtils.hpp"

namespace Splatoon
{
    void ApplyPatches()
    {
        auto gambit_rpx = FindRPL(*gRPLInfo, "Gambit.rpx");
        if (!gambit_rpx)
        {
            WHBLogPrintf("splatoon_test_patches: Couldn't find Gambit.rpx ...");
            return;
        }

        // ~~~ Begin Patches ~~~

        // // Address of 'gsys::SystemTask::invokeDrawTV_' is 0x02AD7160
        // u32 addr_func_gsys__SystemTask__invokeDrawTV_ = gambit_rpx->textAddr + 0xAD7160;
        // // Patch func + 0x144 to 0x60000000 (nop)
        // u32 patch1 = addr_func_gsys__SystemTask__invokeDrawTV_ + 0x144; // 0x02AD72A4
        // PatchInstruction((u32*)patch1, 0x41820068, 0x60000000); // beq + 0x68 -> nop
        // 
        // // Address of 'gsys::SystemTask::invokeDrawTV_' is 0x02AD7160
        // uintptr_t addr_func_gsys__SystemTask__invokeDrawTV_ = gambit_rpx->textAddr + 0xAD7160;
        // 
        // // Patch func + 0x144 to 0x60000000 (nop)
        // uintptr_t patch1 = addr_func_gsys__SystemTask__invokeDrawTV_ + 0x144; // 0x02AD72A4
        // PatchInstruction((uintptr_t *)patch1, 0x41820068, 0x60000000);        // beq + 0x68 -> nop

        uintptr_t base = gambit_rpx->textAddr;
        uintptr_t func = base + 0xAD7160; /* gsys::SystemTask::invokeDrawTV_ */
        UTL::WriteCode(func + 0x144, UTL::inst::Nop);
    }
}