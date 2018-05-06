#ifndef Sensor_H_
#define Sensor_H_
#include"I2CDevice.cpp"

#define BUFFER_SIZE 0x40
#define OUT_X_L_A 0x28
#define OUT_X_H_A 0x29
#define OUT_Y_L_A 0x2A
#define OUT_Y_H_A 0x2B
#define OUT_Z_L_A 0x2C
#define OUT_Z_H_A 0x2D
//magnetic field

#define OUT_X_L_M 0x03
#define OUT_X_H_M 0x04
#define OUT_Y_L_M 0x05
#define OUT_Y_H_M 0x06
#define OUT_Z_L_M 0x07
#define OUT_Z_H_M 0x08

class Sensor {
private:
	I2CDevice *device;
	short int accelerationX, accelerationY, accelerationZ; // raw 2's complement values
	short int magneticX, magneticY, magneticZ;	
	short int gyroX, gyroY, gyroZ;
public:
	Sensor();
	int readacc();
	int readmag();
	int readgyro();
	short int getAccelerationX() { return accelerationX; }
	short int getAccelerationY() { return accelerationY; }
	short int getAccelerationZ() { return accelerationZ; }
	short int getmagneticX() { return magneticX; }
	short int getmagneticY() { return magneticY; }
	short int getmagneticZ() { return magneticZ; }
	short int getgyroX() { return gyroX; }
	short int getgyroY() { return gyroY; }
	short int getgyroZ() { return gyroZ; }
	~Sensor();
};

#endif