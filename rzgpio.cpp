// Renesas RZG2L GPIO Control 
// ref to https://www.ics.com/blog/how-control-gpio-hardware-c-or-c
#include "rzgpio.h"
using namespace std;

RzGPIO::RzGPIO()
{

Init();
    
}
// test P42_4 only 
void RzGPIO::Init_P42_4()
{
Init_GPIO();
// Inst P42_4 only    
    int fd1 = open("/sys/class/gpio/export", O_WRONLY);
    if (fd1 == -1) {
        perror("Unable to open /sys/class/gpio/export");
        exit(1);
    }
// P42_4, ID = 42 x 8 + 4 + 120 = 460
struct stat sb;
int ret = stat("/sys/class/gpio/P42_4", &sb);
if ( ret != 0 )
    if (write(fd1, "460", 3) != 3) {
        perror("Error writing to /sys/class/gpio/export");
        exit(1);
    }

    close(fd1);
    // Set the pin to be an output by writing "out" to /sys/class/gpio/gpio24/direction

    int fd = open("/sys/class/gpio/P42_4/direction", O_WRONLY);
    if (fd == -1) {
         perror("Unable to open /sys/class/gpio/P42_4/direction");
         exit(1);
    }

    // if (write(fd, "out", 3) != 3) {
    if (write(fd, "in", 2) != 2) {
        perror("Error writing to /sys/class/gpio/P42_4/direction");
        exit(1);
    }

    close(fd);



}

void RzGPIO::Init()
{

Init_GPIO();

// Export the desired pin by writing to /sys/class/gpio/export
int fd;
int fd1 = open("/sys/class/gpio/export", O_WRONLY);
if (fd1 != -1) {

 struct stat sb;

 for ( int n = 0 ; n < MAX_GPIO_Ns ; n++ ) {
 if ( Gpio[n].port > 0 ) {

 char r[100];
 strcpy(r,"/sys/class/gpio/");
 strcat(r,Gpio[n].name);
 int ret = stat(r, &sb);
 if ( ret != 0 )
     if (write(fd1, Gpio[n].ID, 3) == 3) {
     // need a little delay
     usleep(100000);        
     strcat(r,"/direction");
     int fd = open(r, O_WRONLY);
     if (fd != -1) {
        write(fd, Gpio[n].direction, strlen(Gpio[n].direction));
     }
   }
 }
}
     close(fd1);
     close(fd);

}

}


void RzGPIO::Init_GPIO()
{

Gpio[PMOD0_7].port = 0; // not used

Gpio[PMOD0_8].port = 43;
Gpio[PMOD0_8].pin = 2;
Gpio[PMOD0_8].ID = "466";
Gpio[PMOD0_8].name = "P43_2";
Gpio[PMOD0_8].direction = "out";

Gpio[PMOD0_9].port = 41;
Gpio[PMOD0_9].pin = 0;
Gpio[PMOD0_9].ID = "448";
Gpio[PMOD0_9].name = "P41_0";
Gpio[PMOD0_9].direction = "out";

Gpio[PMOD0_10].port = 0; // not used

Gpio[PMOD1_7].port = 0; // not used

Gpio[PMOD1_8].port = 5;
Gpio[PMOD1_8].pin = 2;
Gpio[PMOD1_8].ID = "162";
Gpio[PMOD1_8].name = "P5_2";
Gpio[PMOD1_8].direction = "in";

Gpio[PMOD1_9].port = 42;
Gpio[PMOD1_9].pin = 4;
Gpio[PMOD1_9].ID = "460";
Gpio[PMOD1_9].name = "P42_4";
Gpio[PMOD1_9].direction = "in";

Gpio[PMOD1_10].port = 47;
Gpio[PMOD1_10].pin = 2;
Gpio[PMOD1_10].ID = "498";
Gpio[PMOD1_10].name = "P47_2";
Gpio[PMOD1_10].direction = "in";


}

void RzGPIO::Write(int n, int Value)
{
    char r[100];
    strcpy(r,"/sys/class/gpio/");
    strcat(r,Gpio[n].name);
    strcat(r,"/value");

    int fd = open(r, O_WRONLY);
    if (fd != -1) {         
std::string s = std::to_string(Value);
char const *pchar = s.c_str();    
        if (write(fd, pchar, 1) != 1) {
            perror("Error writing to value");

        }
    }

    close(fd);

}

void RzGPIO::Write_P42_4(int Value)
{
    int fd = open("/sys/class/gpio/P42_4/value", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/P42_4/value");
        exit(1);
    }

    // Toggle LED 50 ms on, 50ms off, 100 times (10 seconds)
std::string s = std::to_string(Value);
char const *pchar = s.c_str(); 

    // std::string s = std::to_string(value);
        if (write(fd, pchar, 1) != 1) {
            perror("Error writing to /sys/class/gpio/P42_4/value");
            exit(1);
        }

    close(fd);

}


int RzGPIO::Read(int n)
{
    int ret = 0 ;
    char r[100];
    strcpy(r,"/sys/class/gpio/");
    strcat(r,Gpio[n].name);
    strcat(r,"/value");
    // printf("r=%s\n",r);
    int fd = open(r, O_RDONLY);
    if (fd != -1) {         \
// std::string s = std::to_string(Value);
char pchar[]="0";
    read(fd, pchar, 1);
    ret = atoi(pchar);
    }
    close(fd);
    return ret;    
}
    
int RzGPIO::Read_P42_4()
{
    int ret = 0 ;
    int fd = open("/sys/class/gpio/P42_4/value", O_RDONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/P42_4/value");
        exit(1);
    }

char pchar[]= "0"; 

    read(fd, pchar, 1);
    ret = atoi(pchar);        

    close(fd);
    return ret;

}

int RzGPIO::Close()
{
    int fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/unexport");
        exit(1);
    }

    if (write(fd, "460", 2) != 2) {
        perror("Error writing to /sys/class/gpio/unexport");
        exit(1);
    }

    close(fd);
    return 0;
}






