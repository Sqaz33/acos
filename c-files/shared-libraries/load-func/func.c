int square(int x) { return x * x; }

// gcc -fPIC -o func.o -c func.c
// objcopy -j .text -O binary func.o func.bin