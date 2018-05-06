#include "gpio.h"


using namespace std;

	gpio::gpio(string number)
	{
		FILE * fs;
		//fstream fs;
		portnumber=number;
		char* numbers=&number[0];
		fs = fopen("/sys/class/gpio/export","w");
		fputs(numbers,fs);
		fclose(fs);
	}

	void gpio:: mode(string port_number,string mod){
	FILE * fs;
	string path="/sys/class/gpio/gpio";   
	path.append(port_number);
	path.append("/direction");	
	char * moded,*Fpath;
	Fpath=&path[0];
	moded=&mod[0];
	fs=fopen(Fpath,"w");
	fputs(moded,fs);
	fclose(fs);
	
    
    }

	string gpio:: read(string port_number){
	char val[100];
	FILE * fs;
	string path="/sys/class/gpio/gpio";   
	path.append(port_number);
	path.append("/value");
	char * Fpath;
	Fpath=&path[0];;
	fs=fopen(Fpath,"r");
	fgets(val,100,fs);
	fclose(fs);
	return val;
	}

	void gpio::write(string port_number, string val){
	FILE * fs;
	string path="/sys/class/gpio/gpio";   
	path.append(port_number);
	path.append("/value");
	char * Fpath,*value;
	Fpath=&path[0];
	value=&val[0];
	fs=fopen(Fpath,"w");
	fputs(value,fs);
	fclose(fs);
	}

	gpio::~gpio()
	{
		FILE * fs;
		//fstream fs;
		char* numbers=&portnumber[0];
		fs = fopen("/sys/class/gpio/unexport","w");
		fputs(numbers,fs);
		fclose(fs);
	}


