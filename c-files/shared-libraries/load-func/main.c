#include <stdlib.h>
#include <stdio.h>

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

typedef int (*func_t)(int);

int main(int argc, char* argv[]) {
    const char* file_name = argv[1];
    int arg = atoi(argv[2]);

    int fd = open(file_name, O_RDONLY);
    struct stat st = {};
    fstat(fd, &st);
    func_t func = mmap(NULL, st.st_size, 
                       PROT_READ | PROT_EXEC, 
                       MAP_PRIVATE, fd, 0);
    close(fd);
    if (MAP_FAILED == func) { perror("mmap failed"); _exit(1); }

    int res = func(arg);
    printf("func(%d) = %d\n", arg, res);
    munmap(func, st.st_size);
 }