# ST95160

Also known as the e2p, external eeprom, 2kb flash

### Layout

Name|Offset|Size
---|---|---
Immo|0x0+0x40|0x20

### Checksums

- http://nefariousmotorsports.com/forum/index.php?topic=1068.msg23507#msg23507

### Seed Keys

- http://nefariousmotorsports.com/forum/index.php?topic=4983.0title=

### Info

- Loaded into the MPC's RAM upon boot
- MPC's RAM content saved to EEPROM
  - Loaded at address 0x7F8000 - 0x807FF0
  - KWP2000 0x2C and 0x21

### Tools

eeprom_V2.1.0.exe

### Writing

- http://nefariousmotorsports.com/forum/index.php?topic=6159.0title=