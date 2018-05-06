#include "Sensor.h"
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <stdio.h>

Sensor::Sensor() {
	this->device = new I2CDevice();
	this->accelerationX = 0;
	this->accelerationY = 0;
	this->accelerationZ = 0;
	this->magneticX = 0;
	this->magneticY = 0;
	this->magneticZ = 0;
	this->gyroX = 0;
	this->gyroY = 0;
	this->gyroZ = 0;
}

Sensor::~Sensor()
{
	delete this->device;
}
int Sensor::readacc() {
	this->accelerationX = (short)(this->device->readRegister(ACCELEROMETER_ADDR,OUT_X_H_A) << 8 | this->device->readRegister(ACCELEROMETER_ADDR,OUT_X_L_A))>>8;
	this->accelerationY = (short)(this->device->readRegister(ACCELEROMETER_ADDR,OUT_Y_H_A) << 8 | this->device->readRegister(ACCELEROMETER_ADDR,OUT_Y_L_A))>>8;
	this->accelerationZ = (short)(this->device->readRegister(ACCELEROMETER_ADDR,OUT_Z_H_A) << 8 | this->device->readRegister(ACCELEROMETER_ADDR,OUT_Z_L_A))>>8;
	return 0;
}
int Sensor::readmag() {
	this->device->readRegister(MAGNETIC_ADDR, MR_REG_M);
	this->magneticX = (short)(this->device->readRegister(MAGNETIC_ADDR, OUT_X_H_M) << 8 | this->device->readRegister(MAGNETIC_ADDR, OUT_X_L_M))>>6;
	this->magneticY = (short)(this->device->readRegister(MAGNETIC_ADDR, OUT_Y_H_M) << 8 | this->device->readRegister(MAGNETIC_ADDR, OUT_Y_L_M))>>6;
	this->magneticZ = (short)(this->device->readRegister(MAGNETIC_ADDR, OUT_Z_H_M) << 8 | this->device->readRegister(MAGNETIC_ADDR, OUT_Z_L_M))>>6;
	return 0;
}
int Sensor::readgyro() {
	
	this->gyroX = (short)(this->device->readRegister(GYROSCOPE_ADDR, OUT_X_H_A) << 8 | this->device->readRegister(GYROSCOPE_ADDR, OUT_X_L_A))>>10;
	this->gyroY = (short)(this->device->readRegister(GYROSCOPE_ADDR, OUT_Y_H_A) << 8 | this->device->readRegister(GYROSCOPE_ADDR, OUT_Y_L_A))>>10;
	this->gyroZ = (short)(this->device->readRegister(GYROSCOPE_ADDR, OUT_Z_H_A) << 8 | this->device->readRegister(GYROSCOPE_ADDR, OUT_Z_L_A))>>10;
	return 0;
}
