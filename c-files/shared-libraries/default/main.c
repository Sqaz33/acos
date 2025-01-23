// gcc -o main -L. main.c -llib -Wl,-rpath,'$ORIGIN/
extern void func();


int main() {
    func();
}