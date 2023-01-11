#include "SplatPatches.hpp"
#include "CodePatchUtils.hpp"

namespace sead
{
    struct Color4f
    {
        float r;
        float g;
        float b;
        float a;
    };

    template <typename T>
    struct Vector3
    {
        T x;
        T y;
        T z;
    };

    template <typename T>
    struct BoundBox3
    {
        Vector3<T> min;
        Vector3<T> max;
    };

    template <typename T>
    struct Matrix34
    {
        T m[3][4];
    };

    template <typename T>
    struct Matrix44
    {
        T m[4][4];
    };

    struct TextWriter
    {
        u8 _0[80];
    };
}


namespace Splatoon
{
    void (*beginDrawImm)(sead::Matrix34<float> const& mtx34, sead::Matrix44<float> const& mtx44, int a3); // agl::ShaderType a3); // Maybe???
    void (*drawBoundBoxImm)(sead::BoundBox3<float> const& box, sead::Color4f const & color, float a3);

    void (*drawPointImm)(sead::Vector3<float> const& pos, sead::Color4f const & color, float a3);



    sead::TextWriter *(*sead_TextWriter__ct)(sead::TextWriter *_this);
    sead::TextWriter *(*sead_TextWriter__ct_test)(sead::TextWriter *_this, int a2);
    void (*sead_TextWriter_printf)(sead::TextWriter *_this, const char *fmt, ...);

    static sead::BoundBox3<float> box1 = {
        { -0.94f, -0.94f, 0.0f },
        { 0.94f, 0.94f, 0.0f }
    };

    static sead::BoundBox3<float> box2 = {
        { -0.97f, -0.97f, 0.0f },
        { 0.97f, 0.97f, 0.0f }
    };

    static sead::Color4f color1 = { 1.0f, 1.0f, 1.0f, 1.0f };
    static sead::Color4f color2 = { 1.0f, 0.0f, 0.0f, 1.0f };

    static sead::Matrix34<float> mtx34Ident = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f
    };

    static sead::Matrix44<float> mtx44Ident = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };


    static uintptr_t textAddr = 0;
    static uintptr_t dataAddr = 0;


    void MyTestFunc()
    {
        static bool first = true;
        if (first) {
            WHBLogPrintf("splatoon_test_patches: MyTestFunc() called! First time.");
            first = false;
        }

        // static int i = 60;
        // if (i > 0) {
        //     i--;
        // } else {
        //     WHBLogPrintf("splatoon_test_patches: MyTestFunc() called! Heartbeat Message. (Expected every 60 frames)");
        //     i = 60;
        // }

        beginDrawImm(mtx34Ident, mtx44Ident, 4);

        drawBoundBoxImm(box1, color1, 1.0f);
        // drawBoundBoxImm(box2, color2, 1.0f);
        drawBoundBoxImm(box2, color2, 15.0f);

        drawPointImm({ 0.0f, 0.0f, 0.0f }, color2, 30.0f);

        // static sead::TextWriter *writer = nullptr;
        // if (!writer) {
        //     // writer = (sead::TextWriter*)malloc(sizeof(sead::TextWriter));
        //     // writer = (sead::TextWriter*)malloc(80);
        //     writer = sead_TextWriter__ct(writer);
        //     WHBLogPrintf("splatoon_test_patches:    Created TextWriter.");
        // }

        // if (writer) {
        //     WHBLogPrintf("splatoon_test_patches:    Writing to TextWriter...");
        //     sead_TextWriter_printf(writer, "Hello World!");
        // }

        // auto writer = sead_TextWriter__ct_test(writer, 0x104141f4);
        // if (writer) {
        //     WHBLogPrintf("splatoon_test_patches:    Writing to TextWriter...");
        //     sead_TextWriter_printf(writer, "Hello World!");
        // } else {
        //     WHBLogPrintf("splatoon_test_patches:    Failed to create TextWriter.");
        // }

        // static sead::TextWriter *writer = nullptr;
        // if (!writer) {
        //     writer = sead_TextWriter__ct_test(writer, 0x104141f4);
        //     WHBLogPrintf("splatoon_test_patches:    Created TextWriter.");
        // } else {
        //     sead_TextWriter_printf(writer, "Hello World!");
        // }

        // static sead::TextWriter writer = { 0 };
        // auto test_res = sead_TextWriter__ct_test(&writer, 0x104141f4);
        // WHBLogPrintf("test_res = %p", test_res);
        // // WHBLogPrintf("&test_res = %p", &test_res);
        // // WHBLogPrintf("*test_res = %p", *test_res);
        // WHBLogPrintf("&writer = %p", &writer);
        // // WHBLogPrintf("writer = %p", writer);
        // if (test_res) {
        //     WHBLogPrintf("splatoon_test_patches:    Writing to TextWriter...");
        //     sead_TextWriter_printf(test_res, "Hello World!");
        // }

        // static sead::TextWriter writer = { 0 };
        // // int a2 = 0x104141f4 + 0x503000;
        // int a2 = dataAddr + 0x4141f4;
        // // int a2 = dataAddr + 0x41421c;
        
        // WHBLogPrintf("Before Constructing TextWriter:");
        // WHBLogPrintf("%08x %08x %08x %08x", writer._0[0], writer._0[1], writer._0[2], writer._0[3]);
        // WHBLogPrintf("%08x %08x %08x %08x", writer._0[4], writer._0[5], writer._0[6], writer._0[7]);
        // WHBLogPrintf("%08x %08x %08x %08x", writer._0[8], writer._0[9], writer._0[10], writer._0[11]);
        // WHBLogPrintf("%08x %08x %08x %08x", writer._0[12], writer._0[13], writer._0[14], writer._0[15]);
        // WHBLogPrintf("%08x %08x %08x %08x", writer._0[16], writer._0[17], writer._0[18], writer._0[19]);

        // auto test_res = sead_TextWriter__ct_test(&writer, a2);

        // WHBLogPrintf("After Constructing TextWriter:");
        // WHBLogPrintf("%08x %08x %08x %08x", writer._0[0], writer._0[1], writer._0[2], writer._0[3]);
        // WHBLogPrintf("%08x %08x %08x %08x", writer._0[4], writer._0[5], writer._0[6], writer._0[7]);
        // WHBLogPrintf("%08x %08x %08x %08x", writer._0[8], writer._0[9], writer._0[10], writer._0[11]);
        // WHBLogPrintf("%08x %08x %08x %08x", writer._0[12], writer._0[13], writer._0[14], writer._0[15]);
        // WHBLogPrintf("%08x %08x %08x %08x", writer._0[16], writer._0[17], writer._0[18], writer._0[19]);

        // if (test_res) {
        //     WHBLogPrintf("splatoon_test_patches:    Writing to TextWriter...");
        //     sead_TextWriter_printf(test_res, "Hello World!");
        // }


        // WHBLogPrintf("splatoon_test_patches:    writer = %p", writer);
        
        // sead_TextWriter_printf(writer, "Did you just use a nullptr as the this pointer?");
    }

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

        WHBLogPrintf("Gambit.rpx->textAddr: %08x", gambit_rpx->textAddr);
        WHBLogPrintf("Gambit.rpx->dataAddr: %08x", gambit_rpx->dataAddr);
        WHBLogPrintf("Gambit.rpx->readAddr: %08x", gambit_rpx->readAddr);

        dataAddr = gambit_rpx->dataAddr;
        textAddr = gambit_rpx->textAddr;

        uintptr_t base = gambit_rpx->textAddr;
        uintptr_t func = base + 0xAD7160; /* gsys::SystemTask::invokeDrawTV_ */
        // UTL::WriteCode(func + 0x144, UTL::inst::Nop); // .text:02AD72A4         nop
        // UTL::WriteCode(func + 0x148, UTL::inst::BranchLink())

        // Attempt to call test function
        // UTL::WriteCode(func + 0x144, UTL::inst::BranchLink(((uintptr_t)&MyTestFunc) - (func + 0x144 + 4)));
        // auto MyTestFunc_addr = OSEffectiveToPhysical((uintptr_t)&MyTestFunc);
        // UTL::WriteCode(func + 0x144, UTL::inst::BranchLink(MyTestFunc_addr - (func + 0x144)));
        // WHBLogPrintf("SPT: [DEBUG] MyTestFunc() address: %p", &MyTestFunc);
        // WHBLogPrintf("SPT: [DEBUG] MyTestFunc() Physical Address: %p", OSEffectiveToPhysical((uint32_t)&MyTestFunc));
        // WHBLogPrintf("SPT: [DEBUG] func + 0x144: %p", func + 0x144);
        // WHBLogPrintf("SPT: [DEBUG] func + 0x144 physical: %p", OSEffectiveToPhysical(func + 0x144));
        // WHBLogPrintf("SPT: [DEBUG] MyTestFunc_addr - (func + 0x144): %p", MyTestFunc_addr - (func + 0x144));
        // WHBLogPrintf("SPT: [DEBUG] %08x", ((uintptr_t)&MyTestFunc) - (func + 0x144));
        // WHBLogPrintf("SPT: [DEBUG] ^ as PPC Hex Inst: %08x", UTL::inst::BranchLink(((uintptr_t)&MyTestFunc) - (func + 0x144)));

        UTL::WriteCode(func + 0x144, 0x3d600000 | ((((uintptr_t)&MyTestFunc) >> 16) & 0x0000FFFF));
        UTL::WriteCode(func + 0x148, 0x616b0000 | (((uintptr_t)&MyTestFunc) & 0x0000ffff));
        UTL::WriteCode(func + 0x14c, 0x7d6903a6);
        UTL::WriteCode(func + 0x150, 0x4e800421); // bctrl
        // UTL::WriteCode(func + 0x150, 0x4e800420); // bctr

        // Jump forward a bit to skip the built in debug draw code. (Jump to func + 0x1AC)
        UTL::WriteCode(func + 0x154, UTL::inst::Branch(0x1AC - 0x154)); // b 0x88

        

        drawBoundBoxImm = (void (*)(sead::BoundBox3<float> const &box, sead::Color4f const &color, float a3))(base + 0xA11158);
        beginDrawImm = (void (*)(sead::Matrix34<float> const& mtx34, sead::Matrix44<float> const& mtx44, int a3))(base + 0xA0ED08);

        drawPointImm = (void (*)(sead::Vector3<float> const& pos, sead::Color4f const& color, float a3))(base + 0xA1100C);




        sead_TextWriter__ct = (sead::TextWriter * (*)(sead::TextWriter * _this))(base + 0x8CC3B4);
        sead_TextWriter_printf = (void (*)(sead::TextWriter * _this, const char * format, ...))(base + 0x8CC420);

        sead_TextWriter__ct_test = (sead::TextWriter * (*)(sead::TextWriter * _this, int))(base + 0x8CC3B4);
    }
}