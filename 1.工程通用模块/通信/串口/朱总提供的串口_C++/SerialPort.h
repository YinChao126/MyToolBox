#ifndef __LINUX_SERIAL_PORT_H
#define __LINUX_SERIAL_PORT_H

//#define SIM_MODE


#include<stdio.h>

#ifndef SIM_MODE
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<termios.h>
#include<errno.h>
#include<string.h>
#endif

#define PORT_IDLE	0
#define PORT_OPEN	1
#define PORT_READY	2

class cUart
{
public:
	cUart();
	~cUart();

	bool Open(const char* Port);
	void Close();

	bool Init(int Speed, int FlowCtrl, int DataBits, int StopBits, char Parity);
	bool Send(unsigned char *SendBuf, int DataLen);
	int Recv(unsigned char *RecvBuf, int DataLen);

private:
	int fd;
	int fd_flag;
};

#endif
