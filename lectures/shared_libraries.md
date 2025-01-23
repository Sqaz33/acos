# Code Libraries

**Shared And Static**

.o - binary file unit that contains code, constant and other data.

* Static Library [Legacy!] (.a) - indexed archive of .o files.
* Shared Library (.so) - linked ELF file like a program with no entry point
* Libraries search/load order (performed by /lib/ld.so)
  * check for LD_PRELOAD entries.
  * check for realtive/absolute path.
  * check fo LD_LIBRARY_PATH directories.
  * check directories by config starting at /etc/ld.so.conf.
  * смотрит заголовок ELF-программы.

# Custom Library Path

**Library Path Section**

* DT_PATH[Old linkers] section.
* DT_RUNPATH[New linkers] section.
* To create: gcc -Wl, -rpath,DIRECTORY
  * Subtitution values:
    * $ORIGIN - binary program directory.
    * $PWD - current directory.
    * $LIB - library common name (lib or lib64).
    * $PLATFORM - like  'dollar'(uname -m) output

# Linux System Libraries

**Use Package Manager If Possible**.

Packages named like 'libSOMELIB':

- bundles of . so files and resources.
- just dependencies of software but not ready do develop.

Packages named like 'libSOMELIB-dev' (Debian, Ubuntu) or 'libSOMELIB-devel' (Fedora, openSUSE):

- header (.h or.hpp) files for related libraries.
- might contain meta information to simplify build process.

# Libraries Loading

**Prelinked And Runtime**

* Before _start by /lib/ld. so - from ELF header files.
* At random time:
  * allocate memory or map file with PROT EXEC flag.
  * make function pointer to code start.
  * call function.
* Pros: code might be generated at runtime (JIT-compilation).
* Cons: there are many things to handle (relocations etc.).

# Dynamic Library Loading

**dlopen -dlsym -dlclose**

* POSIX APIs (requires -ldl on Linux).
* Library functions but not system calls.

*Find and load library:*

```c
void* dlopen(const char* name, int flags);
```

*Find a symbol into loaded library*

```c
void* dlsym(void* lib, const char* name);
```
