#include <cstdint>
#include <vector>
#include <iostream>
#include "PayloadBuilder.h"

class LightFX
{
public:
    const uint8_t *Init();
    const uint8_t *Region(int region);
    const uint8_t *Color(int red, int green, int blue);
    const uint8_t *Save();
};
const uint8_t *LightFX::Init()
{
    const uint8_t payload[] = {0x03, 0x21, 0x00, 0x01, 0xff, 0xff};
    PayloadBuilder builder(payload, sizeof(payload) / sizeof(payload[0]));
    return builder.getCompletePayload();
}

const uint8_t *LightFX::Region(int region)
{
    const uint8_t payload[] = {0x03, 0x23, 0x01, 0x00, 0x04};
    PayloadBuilder builder(payload, sizeof(payload) / sizeof(payload[0]));
    switch (region)
    {
    case 0:
        builder.pushEnd(0x08);
        builder.pushEnd(0x09);
        builder.pushEnd(0x0a);
        builder.pushEnd(0x0b);
        break;
    case 1:
        builder.pushEnd(0x08);
        break;
    case 2:
        builder.pushEnd(0x09);
        break;
    case 3:
        builder.pushEnd(0x0a);
        break;
    case 4:
        builder.pushEnd(0x0b);
        break;
    default:
        return 0;
    }
    return builder.getCompletePayload();
}

const uint8_t *LightFX::Color(int red, int green, int blue)
{
    const uint8_t payload[] = {0x03, 0x24, 0x00, 0x07, 0xd0, 0x00, 0xfa};
    PayloadBuilder builder(payload, sizeof(payload) / sizeof(payload[0]));
    builder.pushEnd(static_cast<uint8_t>(red));
    builder.pushEnd(static_cast<uint8_t>(green));
    builder.pushEnd(static_cast<uint8_t>(blue));
    return builder.getCompletePayload();
}

const uint8_t *LightFX::Save()
{
    const uint8_t payload[] = {0x03, 0x21, 0x00, 0x03};
    PayloadBuilder builder(payload, sizeof(payload) / sizeof(payload[0]));
    return builder.getCompletePayload();
}