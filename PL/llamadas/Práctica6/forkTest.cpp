#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main() {
    pid_t pid;
    pid = fork();
    switch (pid) {
        case -1: // Error del fork
            perror("fork");
            break;
        case 0: // Proceso hijo
            cout << "Proceso hijo " << getpid() << "; padre = "
            << getppid() << endl;
        break;
        default: // Proceso padre
            cout << "Proceso padre " << getpid() << "; padre = "
            << getppid() << endl;
            break;
    }
}