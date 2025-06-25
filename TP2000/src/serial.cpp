#include "serial.h"

#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

namespace TP2000 {
    Serial::Serial(const char *filename, const int speed, const int parity):
    filename(filename),
    speed(speed),
    parity(parity)    
    {        
        is_open = false;
    }

    Serial::~Serial() {
        close();
    }

    /*
        Return true on error
    */
    int Serial::open() {
        if (is_open) {
            printf("Serial port already open");
            return 1;
        }

        fd = ::open(filename, O_RDWR | O_NOCTTY | O_SYNC);

        if (fd < 0) {
            printf("Failed to open serial port");
            return 1;
        }

        struct termios tty;

        if (tcgetattr(fd, &tty) != 0) {
            printf("Failed to tcgetattr %d", errno);
            return 1;
        }

        cfsetospeed(&tty, speed);
        cfsetispeed(&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
        tty.c_iflag &= ~IGNBRK;
        tty.c_lflag = 0;

        tty.c_oflag = 0;
        tty.c_cc[VMIN] = 0;
        tty.c_cc[VTIME] = 5;

        tty.c_iflag &= ~(IXON | IXOFF | IXANY);
        tty.c_cflag |= (CLOCAL | CREAD);

        tty.c_cflag &= ~(PARENB | PARODD);

        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr(fd, TCSANOW, &tty) != 0) {
            printf("Failed to tcsetattr %d", errno);
            return 1;
        }

        is_open = true;
        return 0;
    }

    void Serial::close() {
        if (!is_open)
            return;
        is_open = false;
        int error = ::close(fd);
    }

    int Serial::available() {
        int count, error;
        error = ioctl(fd, FIONREAD, &count);

        if (error == -1)
            return 0;

        return count;
    }

    int Serial::read(char *buf, int bufsize) {
        return ::read(fd, buf, bufsize);
    }

    int Serial::write(const char *buf, int bufsize) {
        return ::write(fd, buf, bufsize);
    }

    
}