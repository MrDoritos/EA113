#include "lawicel.h"

namespace TP2000 {
    void read_hex(char *dest, const char source, int offset) {
        int roff = offset / 2;
        bool m = offset & 1;
        if (source >= '0' && source <= '9')
            dest[roff] |= (source-'0') << (m ? 0 : 4);
        else {
            char sub = 'A';
            if (source >= 'a')
                sub = 'a';
            dest[roff] |= (source-sub) << (m ? 0 : 4);
        }
    }

    LAWICEL::LAWICEL(Serial *serial) {
        this->serial = serial;
    }

    int LAWICEL::open() {
        serial->write("O\r", 2);
    }

    int LAWICEL::close() {
        serial->write("C\r", 2);
    }

    int LAWICEL::available() {
        return serial->available();
    }

    int LAWICEL::send(const CAN *frames, int bufsize) {

    }

    int LAWICEL::receive(CAN *frames, int bufsize) {
        if (!available())
            return 0;
        
        char buf;
        int offset = 0;
        int canoffset = 0;

        while (1) {
            int error = serial->read(&buf, 1);
            if (error)
                break;

            switch (buf) {
                case '\r':
                case '\n':
                    if (offset + 1 >= bufsize)
                        return offset;
                    offset++;
                    canoffset = 0;
                    break;
                case 'T':
                    frames[offset].ide = true;
                    break;
                case 't':
                    frames[offset].ide = false;
                    break;
                default:
                    if (canoffset < 3) {
                        frames[offset].identifier |= (short(buf-'0') << (2-canoffset));
                    } else
                    if (canoffset == 3) {
                        frames[offset].data_length = (buf-'0');
                    } else {
                        read_hex(&frames[offset].data[canoffset-3], buf, canoffset & 1);
                    }
                    canoffset++;
                    break;
            }
        }

        return offset;
    }
}