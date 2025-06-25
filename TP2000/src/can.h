#pragma once

namespace TP2000 {
    struct CAN {
        const static int data_buffer_length = 32;
        
        short identifier;
        char data_length;
        bool rtr, ide;
        short crc;
        char eof;
        char ifs;
        char data[data_buffer_length];

        CAN();

        void parse(const char *buffer, const int buflen, const int can_offset);
        void serialize(char *dest, const int buflen) {

        }
    };
}