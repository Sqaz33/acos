// gcc -o liblib.so lib.c -fPIC -shared
#include <stdio.h>


void func() {
    puts("Hi from lib\n");
}