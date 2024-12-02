// Renesas RZG2L GPIO Control 
// ref to https://www.ics.com/blog/how-control-gpio-hardware-c-or-c

#include "sysfs.h"
using namespace std;
int main()
{
    cout << "Init..." << endl;
    RZG2L_GPIO_Init();
    cout << "Start..." << endl;
    for (int i = 0; i < 10; i++) {    
        RZG2L_GPIO_Write(42, 4, 1);
        cout << "1" << endl;
        sleep(3);    
        RZG2L_GPIO_Write(42, 4, 0);
        cout << "0" << endl;
        sleep(3);    
    }
    return 0;
}


int RZG2L_GPIO_Init()
{

/*    
    int fd1 = open("/sys/class/gpio/export", O_WRONLY);
    if (fd1 == -1) {
        perror("Unable to open /sys/class/gpio/export");
        exit(1);
    }
*/    
// P42_4, ID = 42 x 8 + 4 + 120 = 460
struct stat sb;
if (stat("/sys/class/gpio/gpiochip512", &sb) != 0)
    {
cout << "no" <<endl;
    }
    else {
cout << "yes" <<endl;
    }

return 0;
}


int RZG2L_GPIO_Write(int Port, int Pin, int Value)
{
return 0;
}    

int RZG2L_GPIO_Close()
{
return 0;
}