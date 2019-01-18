#include "mbed.h"

#define RFID_ADDR 0xFB // 0x7D is the default address, 0x7C if you close the address jumper.

/* assign pin names */
PinName sda = port_pin(PortA, I2C_SDA);
PinName scl = port_pin(PortA, I2C_SCL);

/* attach serial and led */
Serial pc(SERIAL_TX, SERIAL_RX);
DigitalOut myled(LED1);

/* init i2c */
I2C i2c(sda, scl);

int main() {

	pc.printf("\n\nstart\n");

	set_time(2147483638);

	/* 5 byte array */
	char * data = (char *) calloc(5, 1);
	char status = 0;

    while(1) {
		time_t seconds = time(NULL);

		/* read rfid tag */
		if(i2c.read(RFID_ADDR, data, 5))
			pc.printf("[WARN] i2c read returned non-zero!\n");

		/* set status (0 if no rfid found) */
		status = data[0] | data[1] | data[2] | data[3] | data[4];
		myled = status;
		//pc.printf("s: %d    ", status);

		/* only print rfid data in hex if any data read */
		if (status)
			pc.printf("d : \"%02x%02x%02x%02x%02x\"\n", data[0], data[1], data[2], data[3], data[4]);

		/* sleep for 0.2 sec */
        wait(0.2);
    }

	return 0;
}
