#include <string.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>

using namespace std;

int setup_dev()
{
	int fd = open("/sys/devices/bone_capemgr.9/slots", O_WRONLY);
	if (fd < 0)
	{
		perror("export_open"); //return -1;
	}
	char path01[11];
	sprintf(path01, "am33xx_pwm");
	int  _write = write(fd, &path01[0], sizeof(path01) + 1);
	if (_write < 0)
	{
		perror("am33xx_pwm_write"); 
		//close(fd); 
		//return -1;
	}
	char path02[15];
	sprintf(path02, "bone_pwm_P9_14");
	_write = write(fd, &path02[0], sizeof(path02) + 1);
	if (_write < 0)
	{
		perror("bone_pwm_P9_14"); 
		//close(fd); 
		//return -1;
	}
	char path03[8];
	sprintf(path03, "BB-I2C1");
	_write = write(fd, &path03[0], sizeof(path03) + 1);
	if (_write < 0)
	{
		perror("i2c_write"); 
		//close(fd); 
		//return -1;
	}
	char path04[14];
	sprintf(path04, "cape-bone-iio");
	_write = write(fd, &path04[0], sizeof(path04) + 1);
	if (_write < 0)
	{
		perror("AIN"); 
		//close(fd); 
		//return -1;
	}
	char path05[15];
	sprintf(path05, "bone_pwm_P9_16");
	_write = write(fd, &path05[0], sizeof(path05) + 1);
	if (_write < 0)
	{
		perror("bone_pwm_P9_16"); 
		//close(fd); 
		//return -1;
	}
	close(fd);
	return 0;
}