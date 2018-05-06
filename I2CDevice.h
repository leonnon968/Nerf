#ifndef I2CDevice_H_
#define I2CDevice_H_


using namespace std;

class I2CDevice {
private:
	int file;
public:
	I2CDevice();
	void Init();
	int i2c_open();
	int setAddress(unsigned char address);
	unsigned char readRegister(unsigned char address, unsigned char registerAddress);
	int i2c_write(unsigned char address, unsigned char value);		
	int i2c_write(unsigned char address, unsigned char registerAddress, unsigned char value);
	
	void i2c_close();
	~I2CDevice();
};

#endif