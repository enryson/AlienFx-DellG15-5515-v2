#include <iostream>
#include "USBDeviceHandler.h"
#include "LightFX.h"

int main()
{
    LightFX lightFX;
    const uint8_t *initPayload = lightFX.Init();
    const uint8_t *regionPayload = lightFX.Region(1);
    const uint8_t *colorPayload = lightFX.Color(255, 0, 0); // Red
    const uint8_t *savePayload = lightFX.Save();

    auto printPayload = [](const uint8_t *payload) {
        for (size_t i = 0; payload[i] != '\0'; ++i)
        {
            std::cout << std::hex << static_cast<int>(payload[i]) << " ";
        }
        std::cout << std::dec << std::endl;
    };

    std::cout << "Init Payload: ";
    printPayload(initPayload);

    std::cout << "Region Payload: ";
    printPayload(regionPayload);

    std::cout << "Color Payload: ";
    printPayload(colorPayload);

    std::cout << "Save Payload: ";
    printPayload(savePayload);

    return 0;
}
