#include "Sensor.cpp"
#include "Setup.cpp"
#include "gpio.cpp"
#include <iostream>
#include <sys/time.h>

using namespace std;

void delay(int ms){
	usleep(ms*1000);

}

int main()
{
	gpio gpio66("66");
	gpio66.mode("66","out");
	int pos_x=0,pos_y=0,pos_z=0;
	int velocity_x=0,velocity_y=0,velocity_z=0;
	int  _write;
	bool bflag=true;
	Sensor *sensor=new Sensor();
	setup_dev();
	int X=28370000,Y=28000000;
	int count=1;
	int Xcount_per_degree=3261;
	int Ycount_per_degree=2148;
	int Xdegree90=28370000;
	int Ydegree90=28570000;
	char buffer[8];
	char AINbuffer[5];
	int fd_x;
	int fd_y;
	int AIN;
	fd_x = open("/sys/devices/ocp.3/pwm_test_P9_14.15/period",O_WRONLY);
	sprintf (buffer, "%d", 30000000);
	_write = write(fd_x,&buffer[0],sizeof(buffer)+1);
	close(fd_x);
	fd_y = open("/sys/devices/ocp.3/pwm_test_P9_16.17/period",O_WRONLY);
	sprintf (buffer, "%d", 30000000);
	_write = write(fd_y,&buffer[0],sizeof(buffer)+1);
	close(fd_y);
	for (;;)
	{
		int temp_pos_x=0,temp_pos_y=0,temp_pos_z=0;
		//sensor->readacc();
		//cout << "X: " << sensor->getAccelerationX() << ", Y: " << sensor->getAccelerationY() << ", Z: " << sensor->getAccelerationZ() << endl;
		for(int i=0;i<count;i++){
			sensor->readgyro();
			//cout << "GyroX: " << sensor->getgyroX() << ", GyroY: " << sensor->getgyroY() << ", GyroZ: " << sensor->getgyroZ() << endl;
			temp_pos_z+=sensor->getgyroZ();
			temp_pos_y+=sensor->getgyroY();
		}
		
		temp_pos_z=(int)(temp_pos_z/count);
		temp_pos_y=(int)(temp_pos_y/count);
		pos_z+=temp_pos_z;
		pos_y+=temp_pos_y;
		if(pos_z>256)
			temp_pos_x=256;
		else if(pos_z<-256)
			temp_pos_x=-256;
		else
			temp_pos_x=pos_z;
		if(pos_y>256)
			temp_pos_y=256;
		else if(pos_y<-256)
			temp_pos_y=-256;
		else
			temp_pos_y=pos_y;
		//velocity_x=abs(sensor->getAccelerationX());
		//velocity_y=abs(sensor->getAccelerationY());
		int x_axis=-Xcount_per_degree*temp_pos_x+Xdegree90;
		int y_axis=Ycount_per_degree*temp_pos_y+Ydegree90;
		cout<<temp_pos_x<<"  "<<temp_pos_y<<endl;
		// if(velocity_x<2){
			// X=x_axis;
		// }
		// else if(X>x_axis){
			// X-=(velocity_x*500);
		// }
		// else if(X<x_axis){
			// X+=(velocity_x*500);
		// }
		// if(velocity_y<3){
			// Y=y_axis;
		// }
		// else if(Y>y_axis){
			// Y-=(velocity_y*500);
		// }
		// else if(Y<y_axis){
			// Y+=(velocity_y*500);
		// }
	
		//cout<<pos_z<<"temp_pos_x : "<<temp_pos_x<<endl;
		//cout<<x_axis<<"  x_turn"<<temp_pos_x<<endl;
		fd_x = open("/sys/devices/ocp.3/pwm_test_P9_14.15/duty",O_WRONLY);
		sprintf (buffer, "%d", x_axis);
		_write = write(fd_x,&buffer[0],sizeof(buffer)+1);
		close(fd_x);
		/*
		fd_y = open("/sys/devices/ocp.3/pwm_test_P9_16.17/duty",O_WRONLY);
		sprintf (buffer, "%d", y_axis);
		_write = write(fd_y,&buffer[0],sizeof(buffer)+1);
		close(fd_y); 
		*/
		int finger01,finger02;
		AIN = open("/sys/devices/ocp.3/helper.16/AIN0",O_RDONLY);
		read(AIN,AINbuffer,sizeof(AINbuffer)+1);
		close(AIN);
		sscanf(AINbuffer, "%d", &finger01);
		
		AIN = open("/sys/devices/ocp.3/helper.16/AIN1",O_RDONLY);
		read(AIN,AINbuffer,sizeof(AINbuffer)+1);
		close(AIN);
		sscanf(AINbuffer, "%d", &finger02);
		//cout<<"finger01 : "<<finger01<<"  finger02 : "<<finger02<<endl;
		
		if(finger01 < 1200 && finger02 < 1200 && bflag){
			bflag=false;
			gpio66.write("66","1");
			//gpio66.write("66","0");
			cout<<"shoot"<<endl;
			
		}
		else if(finger01 >1550 &&finger02>1550){
			bflag=true;
			gpio66.write("66","0");
			cout<<"reset"<<endl;
			pos_z=0;
			pos_y=0;
		}
		else if(finger01 > 1550 && finger02 < 1200 && !bflag){
			bflag=true;
		}
		else{
			gpio66.write("66","0");
			cout<<"other"<<endl;
		}
		delay(40);
	}

	return 0;
}