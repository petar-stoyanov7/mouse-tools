#ifndef MYSHKIN_KEYBOARD_H
#define MYSHKIN_KEYBOARD_H
#include <fcntl.h>
#include <string>


class Keyboard {
public:
    int fd;
    bool isEnabled;
    Keyboard(std::string devId);
    Keyboard();
};



#endif //MYSHKIN_KEYBOARD_H
