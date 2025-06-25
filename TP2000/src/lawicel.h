#pragma once

#include "serial.h"
#include "can.h"

namespace TP2000 {
    struct LAWICEL {
        Serial *serial;
        CAN partial_frame;

        LAWICEL(Serial *serial);

        int open();
        int close();

        int available();

        int send(const CAN *frames, int bufsize);
        int receive(CAN *frames, int bufsize);
    };
}