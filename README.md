ARMLinux
========

##Tools

* cross-compile-toolchain "arm-linux-gnueabi"
* ccache

##Config Settings

###Kernel

* initramfs source file points to "rootFSconfig"
* enable loadable module support unchecked

* used "make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- vexpress_defconfig"

* Device Drivers
 * Generic Driver options -> Select only drivers that don't need  compile-time external firmwarwe 
 * -> prevent firmware from being built
 * -> include in-kernel firmware blobs in kernel binary
 * Memory Technology Device support
 * Block devices
 * SCSI device support -> SCSI disk support
 * Serial ATA and ...
 * Network device support -> Ethernet driver support
 * soundcard support
 * HID devices
 * USB support
 * MMC/SD/SDIO card support
 * Realtime Clock
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
  * "CROSS_COMPILE=arm-linux-gnueabi-" because cross-compiler is "arm-linux-gnueabi-gcc" -> look at CC in makefile

###Compile Busybox

* get latest stable busybox version (used 1.21.1)
* extract busybox
  * command "tar xfvj [ARCHIV].tar.bz2" for .tar.bz2 busybox
* configure makefile for ccache 
  * CC = ccache $(CROSS_COMPILE)gcc
  * HOSTCC = ccache gcc
* compile busybox
 * command "make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- busybox"

###Create rootFS with busybox

* use command "make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- install"
 * in menuconfig BusyBox Settings –> Build Options -> Installation  Options (make install behavior) points to output dir of rootFS 

###Run Emulation
* use "arm-system-qemu" for arm systems
* use "-M vexpress-a9" to specify Verstaile Express Board with A9 Core
* use "-serial stdio" to specify stdin/out as input/output devices

##Questions

enabled device drivers after default config for arm:

* MTD 
* SATA
* Ethernet
* soundcard support
* HID
* USB
* SCSI Disk
* SD card
* Realtime Clock
* IOMMU

Explanation of serial and virtual consoles:
* /dev/console:  
Set of devices that can be set with console= parameter at boot time.
Can be redirected to virt. console or serial devices, default is /dev/tty0.
* /dev/tty0  
Current virtual console.
* /dev/tty[1-x]  
One of the virtual consoles.
* /dev/tty  
The console used by the process querying it.
* /dev/ttyS0  
First UART serial port
* /dev/pty  
Pseudo terminal master side.

Sources:  
http://unix.stackexchange.com/questions/60641/linux-difference-between-dev-console-dev-tty-and-dev-tty0
https://www.kernel.org/doc/Documentation/devices.txt

##Useful Links

* cross-compile-toolchain: http://gumstix.org/basic-cross-compilation.html
* MTD: http://de.wikipedia.org/wiki/Memory_Technology_Device
* I2C: http://de.wikipedia.org/wiki/I%C2%B2C
* IOMMU: http://de.wikipedia.org/wiki/IOMMU
* HID: http://de.wikipedia.org/wiki/Human_Interface_Device
* Busybox rootFS: http://emreboy.wordpress.com/2012/12/20/building-a-root-file-system-using-busybox/
