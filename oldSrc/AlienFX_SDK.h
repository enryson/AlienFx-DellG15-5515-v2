#include <cstdint>
#include <vector>
#include <iostream>
#include "LightFX.h"
#include "USBDeviceHandler.h"
#include "PayloadAgregation.h"

class AlienFX_SDK
{
public:
    int StaticColorAll(int red, int green, int blue);
};

int AlienFX_SDK::StaticColorAll(int red, int green, int blue)
{
    USBDeviceHandler usbHandler(0x187c, 0x0550);
    LightFX LFX;
    PayloadAgregation payloads;

    if (!usbHandler.init())
        return 1;
    if (!usbHandler.open())
        return 1;
    if (!usbHandler.claimInterface(0))
        return 1;

    payloads.addPayload(LFX.Init(), sizeof(LFX.Init()));
    payloads.addPayload(LFX.Region(0), sizeof(LFX.Region(0)));
    payloads.addPayload(LFX.Color(red, green, blue), sizeof(LFX.Color(red, green, blue)));
    payloads.addPayload(LFX.Save(), sizeof(LFX.Save()));

    size_t num_payloads = payloads.getNumPayloads();
    for (size_t i = 0; i < num_payloads; ++i)
    {
        const uint8_t *current_payload = payloads.getPayload(i);
        size_t current_payload_size = payloads.getPayloadSize(i);
        usbHandler.sendPayload(current_payload, current_payload_size);
    }

    usbHandler.releaseInterface(0);
    usbHandler.close();
}
