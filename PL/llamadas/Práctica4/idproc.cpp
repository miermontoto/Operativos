#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main() {
    cout << "PID: " << getpid() << ", PPID: " << getppid() << endl;

    cout << endl << "U/G propietario" << endl;
    cout << "Usuario: " << getuid() << ", grupo: " << getgid() << endl;

    cout << endl << "U/G efectivo" << endl;
    cout << "Usuario: " << geteuid() << ", grupo: " << getegid() << endl;
}