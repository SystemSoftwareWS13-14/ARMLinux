ARMLinux
========

##Tools

* cross-compile-toolchain "arm-linux-gnueabi"
* ccache

##Config Settings

###Kernel

* General Setup -> initramfs

###Busybox


##How To

###Compile Kernel

* get latest Linux 3.4.XX Kernel (used 3.4.66)
* extract kernel 
  * command "tar xfvj [ARCHIV].tar.bz2" for .tar.bz2 kernel
* configure makefile for ccache 
  * CC = ccache $(CROSS_COMPILE)gcc
  * HOSTCC = ccache gcc
* compile kernel
  * command "make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-"
  * use -jN for multithreaded compile
  * "CROSS_COMPILE=arm-linus-gnueabi-" because cross-compiler is "arm-linux-gnueabi-gcc" -> look at CC in makefile

###Compile Busybox

* get latest stable busybox version (used 1.21.1)
* extract busybox
  * command "tar xfvj [ARCHIV].tar.bz2" for .tar.bz2 busybox

##Useful Links

* http://gumstix.org/basic-cross-compilation.html
