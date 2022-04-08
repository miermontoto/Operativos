#include <iostream>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]) {

    // Si se invoca sin parámetros, lanzar error.
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " [<argumentos>]" << endl;
        exit(EXIT_FAILURE);
    }
    
    // Añadir un null al vector.
    argv[argc] = NULL;

    // Reemplazar el contenido del proceso actual por el comando indicado en
    // los argumentos.
    execvp(argv[1], argv + 1);
}