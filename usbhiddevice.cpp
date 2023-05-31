#include "usbhiddevice.h"

USBHIDDevice::USBHIDDevice() {
    ctx = nullptr;
    handle = nullptr;
    libusb_init(&ctx);
}

USBHIDDevice::~USBHIDDevice() {
    if (handle) {
        libusb_release_interface(handle, 0);
        libusb_close(handle);
    }
    if (ctx) {
        libusb_exit(ctx);
    }
}

bool USBHIDDevice::open(uint16_t vendorID, uint16_t productID) {
    handle = libusb_open_device_with_vid_pid(ctx, vendorID, productID);
    if (handle) {
        libusb_claim_interface(handle, 0);
        open_status = 1;
        return true;
    }
    open_status = 0;
    return false;
}

int USBHIDDevice::read(uint8_t* buffer, int size, unsigned int timeout) {
    int transferred;
    libusb_interrupt_transfer(handle, 0x81, buffer, size, &transferred, timeout);
    return transferred;
}

int USBHIDDevice::write(const uint8_t* buffer, int size, unsigned int timeout) {
    int transferred;
    libusb_interrupt_transfer(handle, 0x01, const_cast<uint8_t*>(buffer), size, &transferred, timeout);
    return transferred;
}

bool USBHIDDevice::IsOpened()
{
    return open_status;
}
