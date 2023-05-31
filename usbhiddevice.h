#ifndef USBHIDDEVICE_H
#define USBHIDDEVICE_H

extern "C"
{
  #include <libusb-1.0/libusb.h>
}

class USBHIDDevice {
private:
    libusb_context* ctx;
    libusb_device_handle* handle;
    bool open_status;

public:
    USBHIDDevice();
    ~USBHIDDevice();

    bool open(uint16_t vendorID, uint16_t productID);
    int read(uint8_t* buffer, int size, unsigned int timeout);
    int write(const uint8_t* buffer, int size, unsigned int timeout);
    bool IsOpened();
};

#endif  // USBHIDDEVICE_H
