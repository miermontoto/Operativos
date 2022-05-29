#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

using namespace std;

string mensaje;

void Manejador(int sig) {
    cout << mensaje << endl;
    exit(0);
}

int main(int argc, char** argv) {
    // Comprobar que se introducen dos argumentos.
    if (argc != 3) {
        cout << "Uso: " << argv[0] << " <segundos> <mensaje> " << endl;
        return 1;
    }

    mensaje = argv[2];

    struct sigaction act;
    act.sa_handler = Manejador;
    sigaction(SIGALRM, &act, NULL);

    if(fork()) {
        exit(0); // Si es el proceso padre, salir.
    } else {
        alarm(atoi(argv[1]));
        pause();
    }
}