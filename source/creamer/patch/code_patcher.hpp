#pragma once

#include <coreinit/cache.h>
#include "types.h"

#define PACKED __attribute__((__packed__))

namespace crm
{
    using Instruction = uint32_t;

    enum Register : int
    {
        r0 = 0,
        r1 = 1,
        r2 = 2,
        r3 = 3,
        r4 = 4,
        r5 = 5,
        r6 = 6,
        r7 = 7,
        r8 = 8,
        r9 = 9,
        r10 = 10,
        r11 = 11,
        r12 = 12,
        r13 = 13,
        r14 = 14,
        r15 = 15,
        r16 = 16,
        r17 = 17,
        r18 = 18,
        r19 = 19,
        r20 = 20,
        r21 = 21,
        r22 = 22,
        r23 = 23,
        r24 = 24,
        r25 = 25,
        r26 = 26,
        r27 = 27,
        r28 = 28,
        r29 = 29,
        r30 = 30,
        r31 = 31,
    };

    // https://arcb.csc.ncsu.edu/~mueller/cluster/ps3/SDK3.0/docs/arch/PPC_Vers202_Book1_public.pdf

    namespace InstFmt
    {
        // 1.7.1
        struct PACKED IForm
        {
            u8 opcd : 6;     // Opcode              | 0 - 6
            u32 li : 30 - 6; // ???                 | 6 - 30
            u8 aa : 30 - 29; // Absolute Address    | 30
            u8 lk : 31 - 30; // Link                | 31

            // Works for Wii U, but is not portable
            // operator u32() const { return *reinterpret_cast<const u32 *>(this); }
            
            // Portable version
            operator u32() const {
                return (opcd << 26) | (li << 2) | (aa << 1) | lk;
            }
        };
        static_assert(sizeof(IForm) == sizeof(u32));

        // 1.7.2
        struct PACKED BForm
        {
            u8 opcd : 6;      // Opcode       | 0 - 6
            u8 bo : 11 - 6;   // ???          | 6 - 11
            u8 bi : 16 - 11;  // ???          | 11 - 16
            u16 bd : 30 - 16; // ???          | 16 - 30
            u8 aa : 30 - 29;  // Absolute     | 30
            u8 lk : 31 - 30;  // Link         | 31
        };
        static_assert(sizeof(BForm) == sizeof(u32));

        // 1.7.4 ~ Type 2
        struct PACKED DForm
        {
            u8 opcd : 6;          // Opcode       | 0 - 6
            Register rt : 11 - 6; // ???          | 6 - 11
            u8 ra : 16 - 11;      // ???          | 11 - 16     | Either a Register or 0
            u16 si : 31 - 16;     // ???          | 16 - 31

            // operator u32() const { return *reinterpret_cast<const u32 *>(this); }
            operator u32() const {
                return (opcd << 26) | (rt << 21) | (ra << 16) | (si << 0);
            }
        };
        static_assert(sizeof(DForm) == sizeof(u32));

        // 1.7.7 ~ Type 2
        struct PACKED XLForm
        {
            // OPCD BO BI /// BH XO LK
            u8 opcd : 6;      // Opcode       | 0 - 6
            u8 bo : 11 - 6;   // ???          | 6 - 11
            u8 bi : 16 - 11;  // ???          | 11 - 16
            int : 19 - 16;    // ///          | 16 - 19
            u8 bh : 21 - 19;  // ???          | 19 - 21
            u16 xo : 31 - 21; // ???          | 21 - 31
            u8 lk : 31 - 30;  // Link         | 31

            // operator u32() const { return *reinterpret_cast<const u32 *>(this); }
            constexpr operator u32() const {
                return (opcd << 26) | (bo << 21) | (bi << 16) | (bh << 11) | (xo << 1) | lk;
            }
        };
        static_assert(sizeof(XLForm) == sizeof(u32));

        // 1.7.8 ~ Type 7
        struct PACKED XFXForm
        {
            u8 opcd : 6;          // Opcode       | 0 - 6
            Register rs : 11 - 6; // ???          | 6 - 11
            u16 spr : 21 - 11;    // ???          | 11 - 21
            u16 xo : 31 - 21;     // ???          | 21 - 31
            int : 1;              // N/A          | 31

            XFXForm(u8 opcd, Register rs, u16 spr, u16 xo) : opcd(opcd), rs(rs), /*spr(spr),*/ xo(xo)
            {
                // Swap SPR
                spr &= 0x3FF;
                this->spr = (spr << 5) | (spr >> 5);
            }

            // Ctor is used to swap SPR before casting
            // operator u32() const { return *reinterpret_cast<const u32 *>(this); }
            constexpr operator u32() const {
                return (opcd << 26) | (rs << 21) | (spr << 11) | (xo << 1);
            }
        };
        static_assert(sizeof(XFXForm) == sizeof(u32));
    }

    namespace inst
    {
        static Instruction AddImmediate(Register rt, Register ra, u16 si) { return InstFmt::DForm(14, rt, ra, si); }        // addi
        static Instruction AddImmediate(Register rt, u8 ra, u16 si) { return InstFmt::DForm(14, rt, ra, si); }              // addi
        static Instruction AddImmediateShifted(Register rt, Register ra, u16 si) { return InstFmt::DForm(15, rt, ra, si); } // addis
        static Instruction AddImmediateShifted(Register rt, u8 ra, u16 si) { return InstFmt::DForm(15, rt, ra, si); }       // addis

        static Instruction Branch(u32 offset) { return InstFmt::IForm(18, (offset & 0x3FFFFFC) >> 2, 0, 0); }             // b
        static Instruction BranchLink(u32 offset) { return InstFmt::IForm(18, (offset & 0x3FFFFFC) >> 2, 0, 1); }         // bl
        static Instruction BranchAbsolute(u32 offset) { return InstFmt::IForm(18, (offset & 0x3FFFFFC) >> 2, 1, 0); }     // ba
        static Instruction BranchLinkAbsolute(u32 offset) { return InstFmt::IForm(18, (offset & 0x3FFFFFC) >> 2, 1, 1); } // bla

        static constexpr Instruction BranchCount() { return InstFmt::XLForm(19, 20, 0, 0, 528, 0); }     // bctr
        static constexpr Instruction BranchCountLink() { return InstFmt::XLForm(19, 20, 0, 0, 528, 1); } // bctrl

        static Instruction LoadImmediate(Register rt, u16 si) { return AddImmediate(rt, 0, si); }               // li
        static Instruction LoadImmediateShifted(Register rt, u16 si) { return AddImmediateShifted(rt, 0, si); } // lis

        static Instruction MoveToSpecialPurposeRegister(Register rs, u16 spr) { return InstFmt::XFXForm(31, rs, spr, 467); } // mtspr
        static Instruction MoveToCountRegister(Register rs) { return MoveToSpecialPurposeRegister(rs, 9); }                  // mtctr

        static Instruction OrImmediate(Register rt, Register ra, u16 si) { return InstFmt::DForm(24, rt, ra, si); }        // ori
        static Instruction OrImmediate(Register rt, u8 ra, u16 si) { return InstFmt::DForm(24, rt, ra, si); }              // ori

        static constinit Instruction Nop = 0x60000000; // nop
        static Instruction NoOperation() { OrImmediate(crm::Register::r0, 0, 0); } // nop (alias, same as above)
    }

    // Code Writing Functions
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