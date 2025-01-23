// gcc -o main -ldl

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>

typedef void (*func_t)();

int main(int argc, char* argv[]) {
    void* handle;

    handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        _exit(1);
    }

    dlerror();
    func_t func = dlsym(handle, argv[2]);
    char* error = dlerror();

    if (error) {
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        _exit(1);
    }

    getchar();

    func();

    dlclose(handle);
    return 0;


}