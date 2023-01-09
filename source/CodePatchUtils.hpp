#pragma once

#include <cstdint>

#include <coreinit/cache.h>

#include "types.h"

namespace UTL
{
    using Instruction = uint32_t;

    namespace inst
    {
        static constinit Instruction Nop = 0x60000000;
        /*consteval*/ Instruction Branch(ptrdiff_t offset) {
            u8 opcode = 18;
            // u32 offset = offset & 0x03FFFFFC; // 26 bits. Ignore the last 2 bits in order to align to 4 bytes.
            offset &= 0x03FFFFFC;
            return (opcode << 26) | offset;
        }
        /*consteval*/ Instruction BranchLink(ptrdiff_t offset) {
            return Branch(offset) | 1;
        }
    }

    template<typename T>
    void Write(uintptr_t address, T value) {
        /* Have kernel do the copy. */
        KernelCopyData(
            OSEffectiveToPhysical(address),
            OSEffectiveToPhysical(reinterpret_cast<uintptr_t>(&value)),
            sizeof(T)
        );

        /* Flush data cache. */
        DCFlushRange(reinterpret_cast<void*>(address), sizeof(T));
    }
    
    inline void WriteCode(uintptr_t address, Instruction value) {
        /* Write data. */
        Write(address, value);
        
        /* Flush instruction cache. */
        ICInvalidateRange(reinterpret_cast<void*>(address), sizeof(Instruction));
    }
}