#include "I2CDevice.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <fcntl.h>
#include <iomanip>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
//accelerometer and magnetic senor address
#define ACCELEROMETER_ADDR 0x19
#define MAGNETIC_ADDR 0x1E

//gyroscope senor address
#define GYROSCOPE_ADDR 0x6B

//control registers
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define CTRL_REG6 0x25
#define CTRL_REG7 0x26
//magnetic senor
#define CRA_REG_M   0x00
#define CRB_REG_M   0x01
#define MR_REG_M    0x02

#define IG_THS_XL       0x32
#define IG_THS_XH       0x33
#define IG_THS_YL       0x34
#define IG_THS_YH       0x35
#define IG_THS_ZL       0x36
#define IG_THS_ZH       0x37
#define IG_DURING       0x38
#define IG_CFG		    0x30

#define BB_I2C_2 "/dev/i2c-1"

I2CDevice::I2CDevice() {
	this->file = -1;
	this->i2c_open();
	this->Init();
}

void I2CDevice::Init() {
	//initialize the accelerometer
	this->i2c_write(ACCELEROMETER_ADDR,CTRL_REG1, 0x57);
	this->i2c_write(ACCELEROMETER_ADDR,CTRL_REG2, 0x18);
	//initialize the magnetic
	this->i2c_write(MAGNETIC_ADDR,CRA_REG_M, 0x14);
	this->i2c_write(MAGNETIC_ADDR,CRB_REG_M, 0xE0);
	this->i2c_write(MAGNETIC_ADDR,MR_REG_M , 0x00);

	// initialize the Gyro
	this->i2c_write(GYROSCOPE_ADDR, CTRL_REG1, 0x6F);
 	this->i2c_write(GYROSCOPE_ADDR, CTRL_REG4, 0x00);
	this->i2c_write(GYROSCOPE_ADDR, IG_THS_XL, 0x1F);
	this->i2c_write(GYROSCOPE_ADDR, IG_THS_XH, 0x58);
	this->i2c_write(GYROSCOPE_ADDR, IG_THS_YL, 0x1F);
	this->i2c_write(GYROSCOPE_ADDR, IG_THS_YH, 0x58);
	this->i2c_write(GYROSCOPE_ADDR, IG_THS_ZL, 0x1F);
	this->i2c_write(GYROSCOPE_ADDR, IG_THS_ZH, 0x58);
	this->i2c_write(GYROSCOPE_ADDR, IG_DURING, 0x01);
	this->i2c_write(GYROSCOPE_ADDR, IG_CFG, 0x65);
}



int I2CDevice::i2c_open() {
	std::string name = BB_I2C_2;
	if ((this->file = open(name.c_str(), O_RDWR)) < 0)
	{
		perror("I2C: failed to open the bus\n"); return 1;
	}
	return 0;
}

int I2CDevice::setAddress(unsigned char address) {
	if (ioctl(this->file, I2C_SLAVE, address) < 0)
	{
		perror("I2C: Failed to connect to the device\n"); return 1;
	}
	return 0;
}



unsigned char I2CDevice::readRegister(unsigned char address,unsigned char registerAddress) {
	this->setAddress(address);
	this->i2c_write(address,registerAddress);
	unsigned char buffer[1];
	this->setAddress(address);
	if (read(this->file, buffer, 1) != 1)
	{
		perror("I2C: Failed to read in the value.\n"); return 1;
	}
	return buffer[0];
}

int I2CDevice::i2c_write( unsigned char address,unsigned char value) {
	unsigned char buffer[1];
	buffer[0] = value;
	this->setAddress(address);
	if (write(this->file, buffer, 1) != 1)
	{
		perror("I2C: Failed write to the device\n"); return 1;
	}
	return 0;
}

int I2CDevice::i2c_write(unsigned char address,unsigned char registerAddress, unsigned char value) {
	unsigned char buffer[2];
	buffer[0] = registerAddress;
	buffer[1] = value;
	this->setAddress(address);
	if (write(this->file, buffer, 2) != 2)
	{
		perror("I2C: Failed write to the device\n"); return 1;
	}
	return 0;
}

void I2CDevice::i2c_close() {
	close(this->file);
	this->file = -1;
}

I2CDevice::~I2CDevice()
{
	if (this->file != -1) this->i2c_close();
}