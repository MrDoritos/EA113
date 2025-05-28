#!/bin/python3

import os
import sys
import re

# Credit
# http://nefariousmotorsports.com/forum/index.php?topic=4983.45
# https://github.com/bri3d/kwp2000/blob/master/src/main/java/com/brianledbetter/kwplogger/KWP2000/XorSeedKeyLogin.java

SEED_DATA = [
    0x0A221289,0x144890A1,0x24212491,0x290A0285,
    0x42145091,0x504822C1,0x0A24C4C1,0x14252229,
    0x24250525,0x2510A491,0x28488863,0x29148885,
    0x422184A5,0x49128521,0x50844A85,0x620CC211,
    0x124452A9,0x18932251,0x2424A459,0x29149521,
    0x42352621,0x4A512289,0x52A48911,0x11891475,
    0x22346523,0x4A3118D1,0x64497111,0x0AE34529,
    0x15398989,0x22324A67,0x2D12B489,0x132A4A75,
    0x19B13469,0x25D2C453,0x4949349B,0x524E9259,
    0x1964CA6B,0x24F5249B,0x28979175,0x352A5959,
    0x3A391749,0x51D44EA9,0x564A4F25,0x6AD52649,
    0x76493925,0x25DE52C9,0x332E9333,0x68D64997,
    0x494947FB,0x33749ACF,0x5AD55B5D,0x7F272A4F,
    0x35BD5B75,0x3F5AD55D,0x5B5B6DAD,0x6B5DAD6B,
    0x75B57AD5,0x5DBAD56F,0x6DBF6AAD,0x75775EB5,
    0x5AEDFED5,0x6B5F7DD5,0x6F757B6B,0x5FBD5DBD
]

def rotate_right(num:int, bits:int):
    mask = (1 << bits) - 1
    carry = (num & mask) << 32 - bits
    shift = (num & ~mask) >> bits
    return carry | shift

def shift_left(num:int, bits:int):
    return (num << bits) & 0xFFFFFFFF

def calculate_key(ecu_id:int, seed:int):
    for i in range(5):
        if ((seed & 0x80000000) == 0x80000000):
            seed = SEED_DATA[ecu_id] ^ rotate_right(seed, 31)
        else:
            seed = rotate_right(seed, 31)
    return seed

def print_help():
    print('./calculateSKC.py <ecu_id:num|hex> <seed:num|hex>')

def is_valid_input(arg):
    return arg.isnumeric() or re.match(r'0x[0-9a-fA-F]+', arg)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print('Not enough arguments')
        print_help()
        sys.exit(-1)

    if not is_valid_input(sys.argv[1]) or \
       not is_valid_input(sys.argv[2]):
        print('Use numbers or hex')
        print_help()
        sys.exit(-1)

    ecu_id = int(sys.argv[1], 0)
    seed = int(sys.argv[2], 0)

    key = calculate_key(ecu_id, seed)

    print('SKC/PIN:', key)
    print('SKC/PIN Hex:', hex(key).upper().replace('X', 'x'))