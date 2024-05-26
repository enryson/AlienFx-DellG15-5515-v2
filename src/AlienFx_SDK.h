#include "LightFX.h"
#include "USBDeviceHandler.h"
#include "PayloadAgregation.h"

class AlienFx_SDK
{
private:
    uint16_t vendor_id = 0x187c;
    uint16_t product_id = 0x0550;

public:
    auto SetColorAll(int red, int green, int blue);
};

auto AlienFx_SDK::SetColorAll(int red, int green, int blue)
{
    USBDeviceHandler usbHandler(vendor_id, product_id);
    LightFX LFX;
    PayloadAgregation payloads;
    if (!usbHandler.init())
        return 1;
    if (!usbHandler.open())
        return 1;
    if (!usbHandler.claimInterface(0))
        return 1;

    payloads.addPayload(LFX.Init());
    payloads.addPayload(LFX.Region(4));
    payloads.addPayload(LFX.Color(red,green,blue));
    payloads.addPayload(LFX.Save());


    size_t num_payloads = payloads.getNumPayloads();

    for (size_t i = 0; i < num_payloads; ++i)
    {
        const uint8_t *current_payload = payloads.getPayload(i);
        usbHandler.sendPayload(current_payload, sizeof(current_payload));
    }

    usbHandler.releaseInterface(0);
    usbHandler.close();
    return 0;
}
