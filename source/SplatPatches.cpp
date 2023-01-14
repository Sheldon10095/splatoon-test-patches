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
    struct Vector2
    {
        T x;
        T y;
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
        // u8 _0[80];
        u32 dword0;
        u32 dword4;
        u32 dword8;
        u32 dwordC;
        Vector2<float> mVector10;
        Vector2<float> mVector18;
        Color4f mColor;
        float unk30;
        float float34;
        u32 dword38;
        float float3C;
        u32 dword40;
        u32 dword44;
        u8 byte48;
        u32 dword4C; // vtable
    };
    static_assert(sizeof(TextWriter) == 80, "TextWriter size is wrong");

    struct Viewport
    {
        // u8 _0[24];
        u32 _0[24 / sizeof(u32)];
    };
}


namespace Splatoon
{
    void (*beginDrawImm)(sead::Matrix34<float> const& mtx34, sead::Matrix44<float> const& mtx44, int a3); // agl::ShaderType a3); // Maybe???
    void (*drawBoundBoxImm)(sead::BoundBox3<float> const& box, sead::Color4f const & color, float a3);

    void (*drawPointImm)(sead::Vector3<float> const& pos, sead::Color4f const & color, float a3);



    sead::TextWriter *(*sead_TextWriter__ct)(sead::TextWriter *_this);
    sead::TextWriter *(*sead_TextWriter__ct_test)(sead::TextWriter *_this, sead::Viewport const *); // int a2);
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


    // void MyTestFunc()
    void MyTestFunc(sead::Viewport const* pViewport)
    {
        // static bool first = true;
        // if (first) {
        //     WHBLogPrintf("splatoon_test_patches: MyTestFunc() called! First time.");
        //     first = false;
        // }

        // // static int i = 60;
        // // if (i > 0) {
        // //     i--;
        // // } else {
        // //     WHBLogPrintf("splatoon_test_patches: MyTestFunc() called! Heartbeat Message. (Expected every 60 frames)");
        // //     i = 60;
        // // }

        // beginDrawImm(mtx34Ident, mtx44Ident, 4);

        // drawBoundBoxImm(box1, color1, 1.0f);
        // // drawBoundBoxImm(box2, color2, 1.0f);
        // // drawBoundBoxImm(box2, color2, 15.0f);

        // // drawPointImm({ 0.0f, 0.0f, 0.0f }, color2, 30.0f);

        // // WHBLogPrintf("Attempting to construct TextWriter... (pViewport = %p)", pViewport);
        sead::TextWriter writer = { 0 };
        auto test = sead_TextWriter__ct_test(&writer, pViewport);

        // sead_TextWriter_printf(test, "TEST MESSAGE 1");
        // test->_0[0x48] = 0x0;
        // sead_TextWriter_printf(test, "TEST MESSAGE 2");
        // test->_0[0x48] = 0x1;
        // sead_TextWriter_printf(test, "TEST MESSAGE 3");
        // test->_0[0x48] = 0x0;
        // sead_TextWriter_printf(test, "TEST MESSAGE 4");

        sead_TextWriter_printf(&writer, "TEST MESSAGE 1");

        writer.mVector18.y = 1.8f;
        writer.mVector18.x = 1.8f;
        // writer.mVector10.y = 0.1f;
        // writer.mVector10.x = 0.1f;
        writer.mVector10.x = -160.0f;
        writer.mVector10.y = -300.0f;
        writer.mColor = color1;

        sead_TextWriter_printf(&writer, "TEST MESSAGE 2");


        if (test) {
            // WHBLogPrintf("TextWriter constructed successfully! (maybe???)");
            sead_TextWriter_printf(test, "Hello World!");
            // WHBLogPrintf("TextWriter printed successfully!");
        } else {
            // WHBLogPrintf("TextWriter construction failed!");
        }

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

    void MyTestFunc2(sead::TextWriter *writer)
    {
        WHBLogPrintf("splatoon_test_patches:    Writing to TextWriter...");
        sead_TextWriter_printf(writer, "Hello World!");
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

        // UTL::WriteCode(func + 0x144, 0x3d600000 | ((((uintptr_t)&MyTestFunc) >> 16) & 0x0000FFFF)); // lis r11, MyTestFunc@ha
        // UTL::WriteCode(func + 0x148, 0x616b0000 | (((uintptr_t)&MyTestFunc) & 0x0000FFFF));         // ori r11, r11, MyTestFunc@l
        // UTL::WriteCode(func + 0x14c, 0x7d6903a6); // mtspr, ctr, r11
        // UTL::WriteCode(func + 0x150, 0x4e800421); // bctrl
        // // Jump forward a bit to skip the built in debug draw code. (Jump to func + 0x1AC)
        // UTL::WriteCode(func + 0x154, UTL::inst::Branch(0x1AC - 0x154)); // b 0x58

        
        // Slight revision to above code
        UTL::WriteCode(func + 0x144, 0x38610030);                                                   // addi r3, r1, 0x30
        UTL::WriteCode(func + 0x148, 0x3d600000 | ((((uintptr_t)&MyTestFunc) >> 16) & 0x0000FFFF)); // lis r11, MyTestFunc@ha
        UTL::WriteCode(func + 0x14C, 0x616b0000 | (((uintptr_t)&MyTestFunc) & 0x0000FFFF));         // ori r11, r11, MyTestFunc@l
        UTL::WriteCode(func + 0x150, 0x7d6903a6);                                                   // mtspr, ctr, r11
        UTL::WriteCode(func + 0x154, 0x4e800421);                                                   // bctrl
        // Jump forward a bit to skip the built in debug draw code. (Jump to func + 0x1AC)
        UTL::WriteCode(func + 0x158, UTL::inst::Branch(0x1AC - 0x158)); // b 0x54
        


        // Different branch location test
        uintptr_t func2 = base + 0x89DD24;
        UTL::WriteCode(func2 + 0x4c, UTL::inst::Nop);
        UTL::WriteCode(func2 + 0x64, 0x3d600000 | ((((uintptr_t)&MyTestFunc2) >> 16) & 0x0000FFFF)); // lis r11, MyTestFunc2@ha
        UTL::WriteCode(func2 + 0x68, 0x616b0000 | (((uintptr_t)&MyTestFunc2) & 0x0000FFFF));         // ori r11, r11, MyTestFunc2@l
        UTL::WriteCode(func2 + 0x6c, 0x7d6903a6);                                                    // mtspr, ctr, r11
        UTL::WriteCode(func2 + 0x70, 0x4e800421);                                                    // bctrl
        // Jump to end of function for cleanup
        UTL::WriteCode(func2 + 0x74, UTL::inst::Branch(0x280 - 0x74)); // b 0x20C



        drawBoundBoxImm = (void (*)(sead::BoundBox3<float> const &box, sead::Color4f const &color, float a3))(base + 0xA11158);
        beginDrawImm = (void (*)(sead::Matrix34<float> const& mtx34, sead::Matrix44<float> const& mtx44, int a3))(base + 0xA0ED08);

        drawPointImm = (void (*)(sead::Vector3<float> const& pos, sead::Color4f const& color, float a3))(base + 0xA1100C);




        sead_TextWriter__ct = (sead::TextWriter * (*)(sead::TextWriter * _this))(base + 0x8CC3B4);
        sead_TextWriter_printf = (void (*)(sead::TextWriter * _this, const char * format, ...))(base + 0x8CC420);

        // sead_TextWriter__ct_test = (sead::TextWriter * (*)(sead::TextWriter * _this, int))(base + 0x8CC3B4);
        sead_TextWriter__ct_test = (sead::TextWriter * (*)(sead::TextWriter * _this, sead::Viewport const *))(base + 0x8CC3B4);
    }
}