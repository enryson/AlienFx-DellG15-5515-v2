#include <cstdint>
#include <cstring>

class LightFX
{
public:
    const uint8_t *Init(int mode);
    const uint8_t *Reset();
    const uint8_t *HardReset();
    const uint8_t *Region(int region);
    const uint8_t *Color(int red, int green, int blue);
    const uint8_t *Save(int mode);
};

const uint8_t* LightFX::Init(int mode)
{
    uint8_t* payloadInit = new uint8_t[32];
    payloadInit[0] = 0x03;
    payloadInit[1] = 0x21;
    payloadInit[2] = 0x00;
    if (mode == 1) // clean
        payloadInit[3] = 0x04;
    if (mode == 2) // start new
        payloadInit[3] = 0x01;
    payloadInit[4] = 0x00;
    payloadInit[5] = 0x61;
    std::memset(payloadInit + 6, 0, 32 - 6);
    return payloadInit;
}

const uint8_t* LightFX::HardReset()
{
    uint8_t* payloadInit = new uint8_t[32];
    payloadInit[0] = 0x03;
    payloadInit[1] = 0xff;
    payloadInit[2] = 0x80;
    payloadInit[3] = 0x00;
    payloadInit[4] = 0x03;
    payloadInit[5] = 0xe8;
    payloadInit[6] = 0x3c;
    payloadInit[7] = 0xff;
    std::memset(payloadInit + 8, 0, 32 - 8);
    return payloadInit;
}

const uint8_t* LightFX::Reset()
{
    uint8_t* payloadInit = new uint8_t[32];
    payloadInit[0] = 0x03;
    payloadInit[1] = 0xff;
    payloadInit[2] = 0x80;
    payloadInit[3] = 0x00;
    payloadInit[4] = 0x03;
    payloadInit[5] = 0xe8;
    payloadInit[6] = 0x3c;
    payloadInit[7] = 0xff;
    std::memset(payloadInit + 8, 0, 32 - 8);
    return payloadInit;
}

const uint8_t *LightFX::Region(int region)
{
    uint8_t* payloadRegion = new uint8_t[32];
    int size = 9;
    payloadRegion[0] = 0x03;
    payloadRegion[1] = 0x23;
    payloadRegion[2] = 0x01;
    payloadRegion[3] = 0x00;
    payloadRegion[4] = 0x04;
    switch (region)
    {
    case 0:
        payloadRegion[5] = 0x08;
        payloadRegion[6] = 0x00;
        payloadRegion[7] = 0x00;
        payloadRegion[8] = 0x00;
        size = 9;
        break;
    case 1:
        payloadRegion[5] = 0x00;
        payloadRegion[6] = 0x09;
        payloadRegion[7] = 0x00;
        payloadRegion[8] = 0x00;
        break;
    case 2:
        payloadRegion[5] = 0x00;
        payloadRegion[6] = 0x00;
        payloadRegion[7] = 0x0a;
        payloadRegion[8] = 0x00;
        break;
    case 3:
        payloadRegion[5] = 0x00;
        payloadRegion[6] = 0x00;
        payloadRegion[7] = 0x00;
        payloadRegion[8] = 0x0b;
        break;
    case 4:
        payloadRegion[5] = 0x08;
        payloadRegion[6] = 0x09;
        payloadRegion[7] = 0x0a;
        payloadRegion[8] = 0x0b;
        break;
    }
    std::memset(payloadRegion + size, 0, 32 - size);
    return payloadRegion;
}

const uint8_t *LightFX::Color(int red, int green, int blue)
{

    uint8_t* payloadColor = new uint8_t[32];
    payloadColor[0] = 0x03;
    payloadColor[1] = 0x24;
    payloadColor[2] = 0x00;
    payloadColor[3] = 0x07;
    payloadColor[4] = 0xd0;
    payloadColor[5] = 0x00;
    payloadColor[6] = 0xfa;

    payloadColor[7] = static_cast<uint8_t>(red);
    payloadColor[8] = static_cast<uint8_t>(green);
    payloadColor[9] = static_cast<uint8_t>(blue);

    std::memset(payloadColor + 10, 0, 32 - 10);
    return payloadColor;
}

const uint8_t *LightFX::Save(int mode)
{
    uint8_t* payloadSave = new uint8_t[32];
    payloadSave[0] = 0x03;
    payloadSave[1] = 0x21;
    payloadSave[2] = 0x00;
    if (mode == 1) // finish and save
        payloadSave[3] = 0x02;
    if (mode == 2) // set default
        payloadSave[3] = 0x06;
    payloadSave[4] = 0x00;
    payloadSave[5] = 0x61;

    std::memset(payloadSave + 6, 0, 32 - 6);
    return payloadSave;
}
