#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

using namespace std;

bool terminar = true;

void Manejador(int sig) {
    terminar = false;
}

int main(int argc, char** argv) {
    // Comprobar que se introducen dos argumentos.
    if (argc != 3) {
        cout << "Uso: " << argv[0] << " <segundos> <orden> " << endl;
        return 1;
    }

    struct sigaction act;
    act.sa_handler = Manejador;
    sigaction(SIGUSR1, &act, NULL);

    pid_t pid = fork();
    if (pid == 0) {
        // Código del hijo
        execvp(argv[2], argv + 2);
    } else {
        sleep(atoi(argv[1]));
        if(terminar) kill(pid, SIGKILL);
    }
}