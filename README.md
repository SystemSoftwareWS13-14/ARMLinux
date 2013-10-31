ARMLinux
========

##Tools

* cross-compile-toolchain "arm-linux-gnueabi"
* ccache

##Config Settings

###Kernel

* used "make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- vexpress_defconfig"

* Manual set options
 * initramfs source file points to "rootFSconfig"
 * enable loadable module support unchecked
 * remove soundcard support

* Device Drivers set automatically
 * Generic Driver options -> Select only drivers that don't need  compile-time external firmware 
 * -> prevent firmware from being built
 * -> include in-kernel firmware blobs in kernel binary
 * Memory Technology Device support
 * Block devices
 * SCSI device support -> SCSI disk support
 * Serial ATA and ...
 * Network device support -> Ethernet driver support
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
* QEMU_AUDIO_DRV=none to disable audio
* -nographic: Redirect output (inclusive serial) to command line

##Questions

Other possibilities to give compile options:
* Set environment variable with export
* Set variables in Makefile

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

It is not required to specify the kernel console= parameter.
The kernel uses as default a serial port, and this serial port is redirected
to the qemu stdio.
> Kernel command line: root=/dev/nfs nfsroot=10.1.69.3:/work/nfsroot ip=dhcp console=ttyAMA0 mem=128M

> Serial: AMBA PL011 UART driver
mb:uart0: ttyAMA0 at MMIO 0x10009000 (irq = 37) is a PL011 rev1
console [ttyAMA0] enabled

The used console is ttyAMA0.
Source: https://www.kernel.org/doc/Documentation/arm/Booting

To use a pty terminal -serial pty is needed as qemu parameter.
After starting qemu, open the from qemu used pty (for example /dev/pts/25) with 
screen /dev/pts/25 and enter system_reset in the qemu monitor. Now you can view the kernel messages in the pty.

##Other useful information

###Explanation of serial and virtual consoles
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

How to see the boot messages from the kernel:
The kernel has the device /dev/console. This points to the serial terminal by default.
So qemu needs to redirect the serial output to its own tty.

Sources:  
http://unix.stackexchange.com/questions/60641/linux-difference-between-dev-console-dev-tty-and-dev-tty0
https://www.kernel.org/doc/Documentation/devices.txt

###Qemu
Qemu is started with the -nographic option. This means qemu can be used on the command line.
The serial ouput is also redirected to the command line. To get help for the qemu monitor,
press [Ctrl-a, h].

##Useful Links

* cross-compile-toolchain: http://gumstix.org/basic-cross-compilation.html
* MTD: http://de.wikipedia.org/wiki/Memory_Technology_Device
* I2C: http://de.wikipedia.org/wiki/I%C2%B2C
* IOMMU: http://de.wikipedia.org/wiki/IOMMU
* HID: http://de.wikipedia.org/wiki/Human_Interface_Device
* Busybox rootFS: http://emreboy.wordpress.com/2012/12/20/building-a-root-file-system-using-busybox/
