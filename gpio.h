#pragma once
#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <istream>
using std::string;
using std::fstream;
class gpio{
public:
	string portnumber;
	char direction[100];
	int value;
	gpio();

	gpio(string number);
	void mode(string port_number,string mod);
	string read(string port_number);
	void write(string port_number, string val);
	~gpio();

	};
