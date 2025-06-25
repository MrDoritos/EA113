#include "serial.h"

using namespace TP2000;

int main() {
    Serial dev("/dev/ttyACM0", 500000, 0);

    return 0;
}