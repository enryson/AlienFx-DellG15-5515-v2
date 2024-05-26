#include <iostream>
#include <libusb-1.0/libusb.h>
#include <iostream>
#include <cstring>


class USBDeviceHandler
{
public:
    USBDeviceHandler(uint16_t vendor_id, uint16_t product_id);
    ~USBDeviceHandler();
    bool init();
    bool open();
    bool claimInterface(int interface_number);
    bool sendPayload(const uint8_t *payload, size_t payloadSize);
    void releaseInterface(int interface_number);
    void close();

private:
    libusb_context *ctx;
    libusb_device_handle *handle;
    uint16_t vendor_id;
    uint16_t product_id;
};

USBDeviceHandler::USBDeviceHandler(uint16_t vendor_id, uint16_t product_id)
    : ctx(nullptr), handle(nullptr), vendor_id(vendor_id), product_id(product_id) {}

USBDeviceHandler::~USBDeviceHandler()
{
    if (handle)
    {
        libusb_close(handle);
    }
    if (ctx)
    {
        libusb_exit(ctx);
    }
}

bool USBDeviceHandler::init()
{
    int r = libusb_init(&ctx);
    if (r < 0)
    {
        std::cerr << "Falha ao inicializar libusb: " << libusb_error_name(r) << std::endl;
        return false;
    }
    return true;
}

bool USBDeviceHandler::open()
{
    handle = libusb_open_device_with_vid_pid(ctx, vendor_id, product_id);
    if (handle == nullptr)
    {
        std::cerr << "Não foi possível abrir o dispositivo USB" << std::endl;
        return false;
    }
    return true;
}

bool USBDeviceHandler::claimInterface(int interface_number)
{
    if (libusb_kernel_driver_active(handle, interface_number) == 1)
    {
        int r = libusb_detach_kernel_driver(handle, interface_number);
        if (r < 0)
        {
            std::cerr << "Falha ao desligar driver do kernel: " << libusb_error_name(r) << std::endl;
            return false;
        }
    }

    int r = libusb_claim_interface(handle, interface_number);
    if (r < 0)
    {
        std::cerr << "Falha ao requisitar interface: " << libusb_error_name(r) << std::endl;
        return false;
    }
    return true;
}

bool USBDeviceHandler::sendPayload(const uint8_t *payload, size_t payloadSize )
{
    int transferred;
    int r = libusb_interrupt_transfer(handle, LIBUSB_ENDPOINT_OUT | 1, (unsigned char *)payload, 32, &transferred, 0);
    if (r == 0 && transferred == 32)
    {
        std::cout << "Payload enviado com sucesso" << std::endl;
        return true;
    }
    else
    {
        std::cerr << "Falha ao enviar payload: " << libusb_error_name(r) << std::endl;
        return false;
    }
}

void USBDeviceHandler::releaseInterface(int interface_number)
{
    libusb_release_interface(handle, interface_number);
    libusb_attach_kernel_driver(handle, interface_number);
}

void USBDeviceHandler::close()
{
    if (handle)
    {
        libusb_close(handle);
        handle = nullptr;
    }
    if (ctx)
    {
        libusb_exit(ctx);
        ctx = nullptr;
    }
}
