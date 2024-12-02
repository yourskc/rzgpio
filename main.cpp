#include "rzgpio.h"
using namespace std;
int main()
{
    cout << "Init..." << endl;
    cout << "Start..." << endl;
    RzGPIO *rzgpio = new RzGPIO();
    perror("Init OK");

// PMOD1#9 Led test  
/*   
    for (int i = 0; i < 10; i++) {    
        rsgpio->Write_42_4(1);
        cout << "1" << endl;
        sleep(3);    
        rsgpio->Write_P42_4(0);
        cout << "0" << endl;
        sleep(3);    
    }
*/
// PMOD1#9 Button polling test
int v, v_prev;
while (1) {
    v = rzgpio->Read(6);
if ( v != v_prev ){
    cout << v << endl;
  }
  v_prev = v;
    usleep(100000);  
}

    return 0;
}