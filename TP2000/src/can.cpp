#include "can.h"

#include <stdlib.h>
#include <string.h>

namespace TP2000 {
    CAN::CAN() {
        memset(this, 0, sizeof(*this));
    }

    void CAN::parse(const char *buffer, const int buflen, const int can_offset) {
        if (buflen < 1)
            return;

        identifier = short(buffer[0]) << 8;
        identifier = buffer[1] & 0b11100000;
        identifier >>= 5;
        rtr = (buffer[1] & 0b00010000) > 0;
        ide = (buffer[1] & 0b00001000) > 0;
    }

    void CAN::serialize(char *dest, const int buflen) {

    }
}