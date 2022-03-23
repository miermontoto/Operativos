#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main() {
    pid_t idProceso;
    pid_t idPadre;

    idProceso = getpid();
    idPadre = getppid();

    cout << "PID del proceso: " << idProceso << endl;
    cout << "PID del padre: " << idPadre << endl;
}