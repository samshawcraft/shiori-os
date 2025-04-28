Shiori-OS
=========

This is an operating system based on [Théo HEMMER](https://github.com/theohemmer)'s work and is intended to pass Prof. Kai Dong's operating system experiment. This project may be propelled by interest and inspiration.

Source of Infrastructure
------------------------

The following parts of this OS are based on Théo HEMMER's work, some of which are modified in order to improve the functionality:

- Bootloader
- VGA 360x200x256 graphic driver
- Keyboard handling
- Mouse handling
- Memory management

Functionality
-------------

According to Prof. Kai Dong's requirements for writing an OS from scratch in the summer of 2025, the OS completed in the experiment should at least reach the level of a 2nd Gen of OS. Furthermore, if any one of the features in the 3rd Gen of OS is implemented, the experiment would get extra marks.

> 1st Gen, vacuum tube (1945-1955) — mainframe: Libraries
> - “OS”: a set of libraries of commonly-used functions.
> - One program ran at a time, as controlled by a human operator.
> 	- Batch system with a human operator.
> 2nd Gen, transistor (1955-1965) — beyond Libraries: + Protection
> - Now suppose a bus replacing the operator.
> - What if an application read from / write to anywhere on disk?
> 	- System call + Dual mode
> 3rd Gen, integrated circuit (1965-1980) — minicomputer: + Long-term Scheduling
>	- Multiprogramming
> 	- Batch system with an operating system
> 4th Gen, large-scale integration (1980-now) — personal computer (PC): + Short-term Scheduling
> - Timesharing

### Progress Tracking

#### Minimum Requirements for Experimental Objectives
- [x] System calls (Syscall #103 syslog is implemented in alpha build 0)
- [x] Dual mode (User mode is switched to and has a syscall of syslog in alpha build 0)
- [ ] Memory protection
- [ ] I/O protection
- [x] Basic Batch Processing 

#### Extra Requirements for Experimental Objectives for Extra Credits
- [ ] Multiprogramming
- [ ] Long-term scheduling
- [ ] Primitive process management

#### Requirements for OS Development Objectives 
This list of requirements is from [Creating an Operating System](https://wiki.osdev.org/Creating_an_Operating_System).

- [x] Terminal support (Implemented in alpha build 0, partly from Théo HEMMER's)
- [ ] Stack smash protector 
- [ ] Multiboot
- [x] Global Descriptor Table (Implemented in alpha build 0, partly from Théo HEMMER's)
- [x] Memory management (Implemented in alpha build 0, from Théo HEMMER's)
- [x] Interrupts (Implemented in alpha build 0, partly from Théo HEMMER's)
- [ ] Multithreaded kernel
- [x] Keyboard (Implemented in alpha build 0, partly from Théo HEMMER's)
- [ ] Internal kernel debugger
- [ ] Filesystem support
- [x] Dual mode (Implemented in alpha build 0)
- [ ] Program Loading 
- [ ] System calls
- [ ] OS specific toolchain
- [ ] Creating a C library 
- [ ] Forking and executing
- [ ] Shell
- [ ] Time
- [ ] Threads
- [ ] Thread Local Storage
- [ ] Symmetric multiprocessing
- [ ] Secondary storage
- [ ] Real filesystems
- [ ] Graphics
- [ ] User interface
- [ ] Networking
- [ ] Sound
- [ ] Universal serial bus

Compile and Run
---------------

To compile this OS, you'll need a [Cross Compiler](https://wiki.osdev.org/GCC_Cross-Compiler) for i686-elf.

To run this OS, you will also need [QEMU](https://www.qemu.org/) for i386.

Resources
---------

I'm using the [OSDev Wiki](https://wiki.osdev.org) to create this OS and find useful resources.
