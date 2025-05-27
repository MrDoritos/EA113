//#include <SPI.h>

const int chipSelectPin  = 53;
const int holdPin        = 0;
const int writeEnablePin = 0;
const int chipMOSIPin    = 51;
const int chipMISOPin    = 50;
const int chipSCKPin     = 52;

const int writeEnableInstruction            = 0b00000110;
const int writeDisableInstruction           = 0b00000100;
const int readStatusRegisterInstruction     = 0b00000101;
const int writeStatusRegisterInstruction    = 0b00000001;
const int readFromMemoryInstruction         = 0b00000011;
const int writeToMemoryInstruction          = 0b00000010;
const int readIdentifcationInstruction      = 0b10000011;
const int writeIdentificationInstruction    = 0b10000010;
const int readIdentificationLockInstruction = 0b10000011;
const int lockIdentificationLockInstruction = 0b10000010;

//const SPISettings spiSettings(20000000, MSBFIRST, SPI_MODE0);

void setup() {
  Serial.begin(9600);
  pinMode(chipSelectPin, OUTPUT);
  pinMode(chipMOSIPin, OUTPUT);
  pinMode(chipMISOPin, INPUT);
  pinMode(chipSCKPin, OUTPUT);
  pinMode(13, OUTPUT);
  SPCR = (1 << SPE) | (1 << MSTR);
}

volatile byte transferByte(volatile byte data) {
  SPDR = data;
  while (!(SPSR & (1 << SPIF))) { }

  return SPDR;
}

byte readStatusRegister() {
  digitalWrite(chipSelectPin, LOW);
  transferByte(readStatusRegisterInstruction);
  byte recv = transferByte(0);

  digitalWrite(chipSelectPin, HIGH);

  return recv;
}

byte readAddress(volatile uint16_t address) {
  digitalWrite(chipSelectPin, LOW);
  transferByte(readFromMemoryInstruction);
  transferByte((address >> 8) & 0xFF);
  transferByte(address & 0xFF);
  byte recv = transferByte(0);

  digitalWrite(chipSelectPin, HIGH);
  return recv;
}

void printByte(volatile byte v) {
  char buf[9];
  for (int i = 0; i < 8; i++) {
    buf[i] = ((v >> (7-i)) & 1) ? '1' : '0';
  }
  buf[8] = 0;
  Serial.println(&buf[0]);
}

void readAddressRange(volatile uint16_t startAddress, volatile uint16_t endAddress) {
  for (uint16_t i = startAddress; i < endAddress; i++) {
    //printByte(readAddress(i));
    digitalWrite(13, LOW);
    byte b = readAddress(i);
    digitalWrite(13, HIGH);
    Serial.write(b);
  }
}

void loop() {
  //while (!Serial.available()) {}
  delay(5000);
  readAddressRange(0x0, 0x0800);
  delay(-1);
}
