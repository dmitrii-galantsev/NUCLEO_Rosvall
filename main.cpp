#include "mbed/mbed.h"
#include "mbed/TARGET_NUCLEO_L432KC/TOOLCHAIN_GCC_ARM/stm32l4xx_ll_rcc.h"
#include "mbed/TARGET_NUCLEO_L432KC/TOOLCHAIN_GCC_ARM/stm32l4xx_ll_gpio.h"
#include "mbed/TARGET_NUCLEO_L432KC/TOOLCHAIN_GCC_ARM/stm32l4xx_ll_tim.h"
#include "mbed/TARGET_NUCLEO_L432KC/TOOLCHAIN_GCC_ARM/stm32l4xx_ll_rcc.h"

#define RFID_ADDR 0xFB // 0x7D is the default address, 0x7C if you close the address jumper.
#define DEBUG 1

/* assign ticker */
Ticker ticker;

/* assign pin names */
PinName sda = port_pin(PortA, I2C_SDA);
PinName scl = port_pin(PortA, I2C_SCL);

/* attach serial and led */
Serial pc(SERIAL_TX, SERIAL_RX);
DigitalOut myled(LED1);

/* init i2c */
I2C i2c(sda, scl);

/* declare and init data */
char * data = (char *) calloc(5, 1);

void read_rfid();
void t_init();
void t_sleep();

void flip_led() { myled = !myled;}

int main()
{

	pc.printf("\n\nstart\n");
	//LL_RCC_MSI_EnableRangeSelection();
	//LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_1);
	//LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_10);

	set_time(2147483638);
	void flip_led();

	ticker.attach(&read_rfid, 1.2);
	ticker.attach(&flip_led, 1);

	while(1) {
	}

	return 0;
}

/*
 * read_rfid - reads data off the ID_12LA
 *
 * data - rfid data will be collected here (5 byte)
 */
void read_rfid()
{
	pc.printf(".");

	/* 5 byte array */
	char status = 0;

	/* read rfid tag */
	if(i2c.read(RFID_ADDR, data, 5))
#if DEBUG
		pc.printf("[WARN] i2c read returned non-zero!\n");
#endif

	/* set status (0 if no rfid found) */
	status = data[0] | data[1] | data[2] | data[3] | data[4];
	myled = status;

	/* only print rfid data in hex if any data read */
	if (!status) {
		pc.printf("d : \"%02x%02x%02x%02x%02x\"\n", data[0], data[1], data[2], data[3], data[4]);
		pc.printf("RANGE : %d\n", LL_RCC_MSI_GetRange());
	}

#if DEBUG
	if (status)
		pc.printf("s: %d    ", status);
#endif
}

void t_init()
{
}

void t_sleep()
{
}
