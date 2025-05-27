# Bosch Motronic MED9.1

No boot mode

K-Line not possible without GPT security pin activation.

Security pin on 95160 SPI EEPROM.

Write only flash possible with CAN and security pin.

Read and write with OBD with special flash program only.

### ST95xxx EEPROM Datasheet

https://www.st.com/resource/en/datasheet/m95160-w.pdf

### My Method

None of the standard EEPROM tools I was using was able to communicate with the ST95160 (the EEPROM chip on my ECU).

I ended up using a hot air station to remove the EEPROM chip off my test ECU and using a chip holder to attach some test leads to an Arduino MEGA.

The Arduino program I used is very simple [../SPIReadEEPROM.ino](../SPIReadEEPROM.ino). There is no control for when the program starts and it reads address 0x0000 to 0x0800 (2KiB). I simply used `socat` to open the serial interface and save the raw data to a file.

`socat -t 100 -x /dev/ttyACM0,b9600,rawer ECU.bin`

You have to make sure you align with the Arduino's reset. It's the fastest solution I had without modfiying flashrom. I think my CH341a programmer lacks an option for 5v, and this chip requires 4.5v to 5.5v. Simply check the ECU has a length of 2048.

My virgin EEPROM dump is [here](../ROM/ECU.bin)

Use [MED9-EEPROM-Tool](https://github.com/EliasKotlyar/MED9-EEPROM-Tool) to validate the checksums, mine all check out.
