#include "mbed.h"

#define RFID_ADDR 0x7D // 0x7D is the default address, 0x7C if you close the address jumper.
#define I2C_PORTS (0x30) // sda(11) + scl(12)

Serial pc(SERIAL_TX, SERIAL_RX);

//PortOut scl (PortA, P12);
//PortOut sda (PortB, P11);
PinName p2 = port_pin(PortA, 2);
PinName p1 = port_pin(PortA, 1);

I2C i2c(p1, p2);

int main() {
    while(1) {
		//pc.printf("%d\n", i2c.read(0));
		//pc.printf("HELLO! %d\n", my_io.read());
		pc.printf("memes\n");
        wait(1.0); // 1 sec
    }

	return 0;
}
