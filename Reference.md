# Car ECU

1K0 907 115 S

# Bench ECU

Name|Number
---|---
ECU Part #|1K0 907 115 P
CPU|MPC562MZP56
Serial|VWZCZ000000000
Identification|BPG-810
Revision|\-\-H14\-\-\-
Date|01.06.06
Test stand #|1479
Manufacturer #|0279
Software|A000
Software|A4.9.6
Hardware #|8P0 907 115 B
Immo Challenge|3F CA 83 DC
Chassis #|WVWXK93C57E024522
VCID|306FA5C7A3235A0B73-8064
VAG #|3C0 907 115 S
WSC|22595
Imp|444
Component|2.0l R4/4V TFSI 0020
Extra|Geraet 85221

VIN WVWXK93C57E024522

- 2007 Volkswagen Passat
- COI: Germany
- Last Mileage: 82,834?

# MPC562MZP56

- PowerPC e200
- 32bit ISA RISC
- No internal flash?
- Code compression supported
- 64bit FPU
- Nexus debug port (class 3) IEEE-ISTO 5001-1999
- Background debug mode (BDM)
- IEEE 1194.1 (JTAG)
- BGA 388
- 40/56/66 MHz
- 5v VCC
- 32Kb SRAM
- 1 core
- MPU
- 3 CAN, TouCAN_A, TouCAN_B, TouCAN_C (shared with MIOS14 GPIO or QSMCM)
- JTAG selectable by PORESET

# GCC 11.1.0

`./configure --target=powerpc-e200-eabi --prefix=/usr/local/powerpc-e200-eabi --enable-languages=c,c++`

```
----------------------------------------------------------------------
Libraries have been installed in:
   /usr/local/powerpc-e200-eabi/lib/../lib

If you ever happen to want to link against installed libraries
in a given directory, LIBDIR, you must either use libtool, and
specify the full pathname of the library, or use the `-LLIBDIR'
flag during linking and do at least one of the following:
   - add LIBDIR to the `LD_LIBRARY_PATH' environment variable
     during execution
   - add LIBDIR to the `LD_RUN_PATH' environment variable
     during linking
   - use the `-Wl,-rpath -Wl,LIBDIR' linker flag
   - have your system administrator add LIBDIR to `/etc/ld.so.conf'

See any operating system documentation about shared libraries for
more information, such as the ld(1) and ld.so(8) manual pages.
----------------------------------------------------------------------
```