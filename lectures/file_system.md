# Core Components

* The Kernel
* Min. set of Standart Libraries
* Min. set of Standart Tools
* High-Level libraries
* High-level framework components
* Desktop Environment
* Server Environment

# API Level Abstraction

*Standart Libraries*

* C Language
* C++ Language

*Operating System Interaction*

* Portable Operating System Interface based on UNIX (POSIX): IEEE 1003.1-2017 - стандарт, описывающий интерфейсы на уровне заголовочных файлов.

# API Level Abstraction

* Application
* High-Level Libraries and Frameworks
* libstdc++ (Linux, *BSD), msvcp.dll (Windows) or libc++ (MacOS)

*Implements POSIX standart API:*

* glibc, bionic, uclib, BSD libc, libSystem.dylib
* Kernel system calls

# Libraries Interaction

* Libraries to be loaded within program by ld.so
* Libraries contents lives within the same process address space
* Function usually must be called indirectly via Procedure Linkage Table
* Function arguments might be any values within process address space

# Linux Kernel Interaction

* INT 0x80 instruction (x86-32)

  * eax stores syscall number
  * ebx, ecx, edx, esi, edi, ebp - argument, eax - retval
* SYSCALL instruction (x86-64)

  * rax stores syscall number
  * rdi, rsi, rdx, r10, r8, r9 - arguments, rax - retval
* Arguments might be just integer

  * integer values
  * pointers

  ---
* Virtual Dynmaic Shared Object - pseudo-lebrary with no real library file
* Kernel Space to User Space memory mapping
* x86_64 function: __vdos_clock_gettime, getcpu, gettimeofday, time

# Kernel Subsystem

* Device Drivers
* Memory Managment Services
* Process and Thread Scheduler
* Inter-Process Communication
* Virtual File System (UNIX)

# UNIX Virtual File System

* Common file hierarchy for all mounted devices and network locations
* Common API to access files
* Tree-based file lookup by naming convention

# UNIX File Types (stat)

* Regular File
* Directory
* Devices: block, character devices
* FIFO (named pipes)
* Sockets

## Regular File

* Just stores data
* Random-access to data: allows iseek, allows fflush(stdin)
* Data structure for contents has no meaning for The Kernel
* Hi-Level APIs migh be sensitive for file format. Example: fopen 'b' flag for binary data

## Directories

* Just a file of specified format to store directory entries
* File contents are *struct dirent* entries
* *struct dirent* is implementation defined
* POSIX defined at least *struct dirent* contents: inode, record size (by file name length), file name up to NAME_MAX(256) bytes

### Devices

* File-like API to access hardware
* Character devices allows send/receive data
* Block devices allows random access like regular file

### FIFO and sockets

* Inter-Process Communications
* Just file name to access but no real storage
* FIFO pipes (mkfifo)
* Sockets: more complicated to allow many-to-one process communications

# Physical File System Types

* Disk-oriented: FAT, NTFS, EXT2/3/4, XFS
* With no structure: SWAP
* Network: SMBFS (Windows), NFS (UNIX), SSHFS (Universal)
* Virtual: TMPFS, OVERPLAYFS

# VFS and File Descriptors

* (st_dev, st_ino) references distinct files
* Process can't access file until it opens
* File Descriptor - integer number within distinct process
* Each process has it's own file descriptors table
* Each process has maximum file descriptor value (usually 1024)

# Data Integrity

* The Linux Kernel uses as most memory available to cache I/O
* Actual data flushes on umount or sync command.
