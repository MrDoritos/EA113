#pragma once

#include <stdio.h>
#include <stdlib.h>

namespace TP2000 {
    struct Serial {
        const char *filename;
        const int speed;
        const int parity;

        bool is_open;
        int fd;

        Serial(const char *filename, const int speed, const int parity);
        ~Serial();

        int open();
        void close();
        int available();
        int read(char *buf, int bufsize);
        int write(const char *buf, int bufsize);
    };
}