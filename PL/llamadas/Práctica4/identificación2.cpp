#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main() {
    cout << "Usuario propietario: " << getuid() << endl;
    cout << "Grupo propietario: " << getgid() << endl;
    cout << endl << "Usuario efectivo: " << geteuid() << endl;
    cout << "Grupo efectivo: " << getegid() << endl;
}