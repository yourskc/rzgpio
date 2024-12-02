# RsGPIO : Renesas RZ/G2L GPIO control

GPIO Test C++ Program for Renesas RZ/G2L

<img src="http://140.112.12.82/docu-moil-renesas/img/RZG2L_EVK.png" width="300px"/>


## 1. Environment

For cross compilation from x86_64 to aarch64, we need install poky toolchain. 

Please reference to Renesas Linux Start-up Guide to build toolchain using Yocto project, then install them on your system. After the installation, use the below commands,

```
cd /opt/poky/3.1.26
unset LD_LIBRARY_PATH
. environment-setup-aarch64-poky-linux
```

Clone the repository,

```
cd <workdir>
git clone https://github.com/yourskc/rzgpio.git
cd rzgpio
```

## 2. Compile 

On x86_64, we can use g++ to compile for debugging

```
g++ main.cpp rzgpio.cpp
```

Finally, we'll compile a aarch64 version with the cross compiler

```
$CXX main.cpp rzgpio.cpp
```

## 3. Transfer and run the executable on RZ/G2L

```
mv a.out rzgpio
scp rzgpio root@192.168.0.216:/home/root
``` 
or, from RZ/G2L
```
scp skc@192.168.0.105:/home/skc/rzgpio .

./rzgpio
```




