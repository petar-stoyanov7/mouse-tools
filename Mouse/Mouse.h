#ifndef MYSHKIN_MOUSE_H
#define MYSHKIN_MOUSE_H
#include <fcntl.h>
#include <string>


class Mouse {
public:
    int fd;
    bool isEnabled;
    Mouse(std::string devId);
    Mouse();
};



#endif //MYSHKIN_MOUSE_H
