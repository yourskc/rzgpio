#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h> 
#include <iostream>

#define PMOD0_7    0
#define PMOD0_8    1
#define PMOD0_9    2
#define PMOD0_10   3

#define PMOD1_7    4
#define PMOD1_8    5
#define PMOD1_9    6
#define PMOD1_10   7

#define MAX_GPIO_Ns 8

struct GPIO {
    int port;
    long pin;
    const char *direction;
    const char *ID;
    const char *name;
};

class RzGPIO {
public :
    RzGPIO();
struct GPIO Gpio[MAX_GPIO_Ns];    
void Init();
void Init_P42_4();
void Init_GPIO();
void Write(int n, int Value);
void Write_P42_4(int Value);
int Read(int n);
int Read_P42_4();
int Close();
};