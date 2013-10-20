ARMLinux
========

##Tools

* cross-compile-toolchain "arm-linux-gnueabi"
* ccache

##Config Settings

###Kernel

* used "make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- defconfig"

* Device Drivers
 * Generic Driver options -> Select only drivers that don't need  compile-time external firmwarwe 
 * prevent firmware from being built
 * include in-kernel firmware blobs in kernel binary
 * Memory Technology Device support
 * Block devices -> RAM block device support
 * Network device support -> Ethernet driver support
 * Network device support -> Wireless LAN
 * I2C support
 * soundcard support
 * HID devices
 * USB support
 * MMC/SD/SDIO card support
 * IOMMU Hardware support

###Busybox

* init utilities -> init
* shells -> ash (associated with "sh")
* coreutils -> ls, echo
* editors -> vi
* Linux System Utilities -> mount, umount, mdev

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
* configure makefile for ccache 
  * CC = ccache $(CROSS_COMPILE)gcc
  * HOSTCC = ccache gcc
* compile busybox
 * command "make CROSS_COMPILE=arm-linux-gnueabi- build"

###Create rootFS with busybox

* use command "make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- install"
 * in menuconfig BusyBox Settings –> Build Options -> Installation  Options (make install behavior) points to output dir of rootFS 

##Questions

enabled device drivers after default config for arm:

* MTD 
* RAM block device
* Ethernet, WLAN
* soundcard support
* I2C
* HID
* USB
* SD card
* IOMMU

##Useful Links

* cross-compile-toolchain: http://gumstix.org/basic-cross-compilation.html
* MTD: http://de.wikipedia.org/wiki/Memory_Technology_Device
* I2C: http://de.wikipedia.org/wiki/I%C2%B2C
* IOMMU: http://de.wikipedia.org/wiki/IOMMU
* HID: http://de.wikipedia.org/wiki/Human_Interface_Device
