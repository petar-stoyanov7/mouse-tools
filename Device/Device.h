#ifndef MYSHKIN_DEVICE_H
#define MYSHKIN_DEVICE_H

#include <libevdev-1.0/libevdev/libevdev.h>
#include <fcntl.h>
#include <string>
#include <unistd.h>

extern bool debugMode;

class Device {
protected:
    struct libevdev* find_device_by_name(const std::string& name);
    struct libevdev *dev;
    void printDeviceDebug(std::string type);

public:
    struct libevdev* getDevice() const;
};



#endif //MYSHKIN_DEVICE_H
