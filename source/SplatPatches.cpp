#include "SplatPatches.hpp"
#include "creamer/patch/code_patcher.hpp"

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
        Vector2<float> mPos;
        Vector2<float> mScale;
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


    static sead::Color4f rainbowColors[7] = {
        // Red
        { 1.0f, 0.0f, 0.0f, 1.0f },
        // Orange
        { 1.0f, 0.5f, 0.0f, 1.0f },
        // Yellow
        { 1.0f, 1.0f, 0.0f, 1.0f },
        // Green
        { 0.0f, 1.0f, 0.0f, 1.0f },
        // Blue
        { 0.0f, 0.0f, 1.0f, 1.0f },
        // Indigo
        { 0.5f, 0.0f, 1.0f, 1.0f },
        // Violet
        { 0.75f, 0.0f, 1.0f, 1.0f }
    };

    // void MyTestFunc()
    void MyTestFunc(sead::Viewport const* pViewport)
    {
        static bool first = true;
        if (first) {
            WHBLogPrintf("splatoon_test_patches: MyTestFunc() called! First time.");
            first = false;
        }

        beginDrawImm(mtx34Ident, mtx44Ident, 4);
        // drawBoundBoxImm(box1, color1, 1.0f);
        // drawBoundBoxImm(box2, color2, 1.0f);

        // Make a rainbow box
        for (int i = 0; i < 7; i++) {
            sead::BoundBox3<float> box = {
                { -0.97f + (i * 0.01f), -0.97f + (i * 0.01f), 0.0f },
                { 0.97f - (i * 0.01f), 0.97f - (i * 0.01f), 0.0f }
            };
            drawBoundBoxImm(box, rainbowColors[i], 1.0f);
        }
        
        // // drawBoundBoxImm(box2, color2, 15.0f);
        // drawPointImm({ 0.0f, 0.0f, 0.0f }, color2, 30.0f);
    }

    void MyTestFunc2(sead::TextWriter *writer)
    {
        static bool first = true;
        if (first) {
            WHBLogPrintf("splatoon_test_patches: MyTestFunc2() called! First time.");
            first = false;
        }

        // WHBLogPrintf("splatoon_test_patches:    Writing to TextWriter...");
        sead_TextWriter_printf(writer, "Hello World!\n");
        // sead_TextWriter_printf(writer, "writer.mPos.x = %f\n", writer->mPos.x);
        // sead_TextWriter_printf(writer, "writer.mPos.y = %f\n", writer->mPos.y);
        // sead_TextWriter_printf(writer, "writer.mScale.x = %f\n", writer->mScale.x);
        // sead_TextWriter_printf(writer, "writer.mScale.y = %f\n", writer->mScale.y);

        // writer->mScale.x = 3.0f;
        // writer->mScale.y = 3.0f;
        // sead_TextWriter_printf(writer, "LARGE TEXT\n");

        writer->mPos.x = -160.0f;
        writer->mPos.y = -300.0f;
        writer->mScale.x = 1.8f;
        writer->mScale.y = 1.8f;
        sead_TextWriter_printf(writer, "Made by Sheldon\n");
    }

    u16 HIWORD(u32 value)
    {
        return (u16)(value >> 16);
    }
    u16 LOWORD(u32 value)
    {
        return (u16)(value & 0xFFFF);
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

        WHBLogPrintf("Gambit.rpx->textAddr: %08x", gambit_rpx->textAddr);
        WHBLogPrintf("Gambit.rpx->dataAddr: %08x", gambit_rpx->dataAddr);
        // WHBLogPrintf("Gambit.rpx->readAddr: %08x", gambit_rpx->readAddr);

        dataAddr = gambit_rpx->dataAddr;
        textAddr = gambit_rpx->textAddr;

        uintptr_t base = gambit_rpx->textAddr;
        uintptr_t func = base + 0xAD7160; /* gsys::SystemTask::invokeDrawTV_ */
        uintptr_t func2 = base + 0x89dcd8;


        /// OLD CODE
        // UTL::WriteCode(func + 0x144, 0x3d600000 | ((((uintptr_t)&MyTestFunc) >> 16) & 0x0000FFFF)); // lis r11, MyTestFunc@ha
        // UTL::WriteCode(func + 0x148, 0x616b0000 | (((uintptr_t)&MyTestFunc) & 0x0000FFFF));         // ori r11, r11, MyTestFunc@l
        // UTL::WriteCode(func + 0x14c, 0x7d6903a6); // mtspr, ctr, r11
        // UTL::WriteCode(func + 0x150, 0x4e800421); // bctrl
        // // Jump forward a bit to skip the built in debug draw code. (Jump to func + 0x1AC)
        // UTL::WriteCode(func + 0x154, UTL::inst::Branch(0x1AC - 0x154)); // b 0x58
        
        // // Slight revision to above code
        // UTL::WriteCode(func + 0x144, 0x38610030);                                                   // addi r3, r1, 0x30
        // UTL::WriteCode(func + 0x148, 0x3d600000 | ((((uintptr_t)&MyTestFunc) >> 16) & 0x0000FFFF)); // lis r11, MyTestFunc@ha
        // UTL::WriteCode(func + 0x14C, 0x616b0000 | (((uintptr_t)&MyTestFunc) & 0x0000FFFF));         // ori r11, r11, MyTestFunc@l
        // UTL::WriteCode(func + 0x150, 0x7d6903a6);                                                   // mtspr, ctr, r11      (also: mtctr r11)
        // UTL::WriteCode(func + 0x154, 0x4e800421);                                                   // bctrl
        // // Jump forward a bit to skip the built in debug draw code. (Jump to func + 0x1AC)
        // UTL::WriteCode(func + 0x158, UTL::inst::Branch(0x1AC - 0x158)); // b 0x54

        // // Different branch location test
        // uintptr_t func2 = base + 0x89dcd8;
        // UTL::WriteCode(func2 + 0x4c, UTL::inst::Nop);
        // UTL::WriteCode(func2 + 0x64, 0x3d600000 | ((((uintptr_t)&MyTestFunc2) >> 16) & 0x0000FFFF)); // lis r11, MyTestFunc2@ha
        // UTL::WriteCode(func2 + 0x68, 0x616b0000 | (((uintptr_t)&MyTestFunc2) & 0x0000FFFF));         // ori r11, r11, MyTestFunc2@l
        // UTL::WriteCode(func2 + 0x6c, 0x7d6903a6);                                                    // mtspr, ctr, r11
        // UTL::WriteCode(func2 + 0x70, 0x4e800421);                                                    // bctrl
        // // Jump to end of function for cleanup
        // UTL::WriteCode(func2 + 0x74, UTL::inst::Branch(0x280 - 0x74)); // b 0x20C
        /// END OLD CODE

        crm::WriteCode(func + 0x144, crm::inst::AddImmediate(crm::Register::r3, crm::Register::r1, 0x30));
        crm::WriteCode(func + 0x148, crm::inst::LoadImmediateShifted(crm::Register::r11, HIWORD((uintptr_t)&MyTestFunc)));
        crm::WriteCode(func + 0x14C, crm::inst::OrImmediate(crm::Register::r11, crm::Register::r11, LOWORD((uintptr_t)&MyTestFunc)));
        crm::WriteCode(func + 0x150, crm::inst::MoveToCountRegister(crm::Register::r11));
        crm::WriteCode(func + 0x154, crm::inst::BranchCountLink());
        crm::WriteCode(func + 0x158, crm::inst::Branch(0x1AC - 0x158));

        // crm::WriteCode(func2 + 0x4c, crm::inst::NoOperation());
        // crm::WriteCode(func2 + 0x64, crm::inst::LoadImmediateShifted(crm::Register::r11, HIWORD((uintptr_t)&MyTestFunc2)));
        // crm::WriteCode(func2 + 0x68, crm::inst::OrImmediate(crm::Register::r11, crm::Register::r11, LOWORD((uintptr_t)&MyTestFunc2)));
        // crm::WriteCode(func2 + 0x6c, crm::inst::MoveToCountRegister(crm::Register::r11));
        // crm::WriteCode(func2 + 0x70, crm::inst::BranchCountLink());
        // crm::WriteCode(func2 + 0x74, crm::inst::Branch(0x280 - 0x74));

        // Temporary test code because something is wrong with the above code -_-
        // Or the Wii U hates me. One of the two.
        crm::WriteCode(func2 + 0x4c, crm::inst::Nop);
        crm::WriteCode(func2 + 0x64, 0x3d600000 | ((((uintptr_t)&MyTestFunc2) >> 16) & 0x0000FFFF)); // lis r11, MyTestFunc2@ha
        crm::WriteCode(func2 + 0x68, 0x616b0000 | (((uintptr_t)&MyTestFunc2) & 0x0000FFFF));         // ori r11, r11, MyTestFunc2@l
        crm::WriteCode(func2 + 0x6c, 0x7d6903a6);                                                    // mtspr, ctr, r11
        crm::WriteCode(func2 + 0x70, 0x4e800421);                                                    // bctrl
        crm::WriteCode(func2 + 0x74, crm::inst::Branch(0x280 - 0x74)); // b 0x20C

        // ~~~~~~~~~~~~~~
         
        beginDrawImm = (void (*)(sead::Matrix34<float> const& mtx34, sead::Matrix44<float> const& mtx44, int a3))(base + 0xA0ED08);
        drawPointImm = (void (*)(sead::Vector3<float> const& pos, sead::Color4f const& color, float a3))(base + 0xA1100C);
        drawBoundBoxImm = (void (*)(sead::BoundBox3<float> const &box, sead::Color4f const &color, float a3))(base + 0xA11158);

        sead_TextWriter_printf = (void (*)(sead::TextWriter * _this, const char * format, ...))(base + 0x8CC420);
        // sead_TextWriter__ct = (sead::TextWriter * (*)(sead::TextWriter * _this))(base + 0x8CC3B4);
        // sead_TextWriter__ct_test = (sead::TextWriter * (*)(sead::TextWriter * _this, int))(base + 0x8CC3B4);
        // sead_TextWriter__ct_test = (sead::TextWriter * (*)(sead::TextWriter * _this, sead::Viewport const *))(base + 0x8CC3B4);
    }
}