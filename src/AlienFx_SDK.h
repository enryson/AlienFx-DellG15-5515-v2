#include "LightFX.h"
#include "USBDeviceHandler.h"
#include "PayloadAgregation.h"
#include <map>
#include <vector>
#include <string>

class AlienFx_SDK
{
private:
    uint16_t vendor_id = 0x187c;
    uint16_t product_id = 0x0550;

public:
    int SetColorAll(int red, int green, int blue);
    int SetColorZones(const std::map<std::string, std::vector<int>> &zones);
};

int AlienFx_SDK::SetColorAll(int red, int green, int blue)
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

    payloads.addPayload(LFX.Init(1));
    payloads.addPayload(LFX.Init(2));
    payloads.addPayload(LFX.Region(4));
    payloads.addPayload(LFX.Color(red, green, blue));
    payloads.addPayload(LFX.Save(1));
    payloads.addPayload(LFX.Save(2));

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

int AlienFx_SDK::SetColorZones(const std::map<std::string, std::vector<int>> &zones)
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

    payloads.addPayload(LFX.Init(1));
    payloads.addPayload(LFX.Init(2));

    int counter = 0;
    for (const auto &pair : zones)
    {
        payloads.addPayload(LFX.Region(counter));
        payloads.addPayload(LFX.Color(pair.second[0], pair.second[1], pair.second[2]));
        counter++;
    }

    payloads.addPayload(LFX.Save(1));
    payloads.addPayload(LFX.Save(2));

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
