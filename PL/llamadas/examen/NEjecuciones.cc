#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

using namespace std;
#define MAX_ARGUMENTOS 10
int i = 0;

void Manejador(int s) {
	cout << " <- Registrado CTRL+C: reduciendo 1 ejecución." << endl;
	i++;
}

void ManejadorNull(int s) {}

int main(int argc, char *argv[]) {
	if(argc < 4) {
		cout << "Uso: " << argv[0] << " <nVeces> <segundos> <orden> [argumentosOrden]" << endl;
		exit(EXIT_FAILURE);
	}

	struct sigaction act; // Manejador para la señal que genera CTRL-C.
	act.sa_handler = Manejador;
	sigaction(SIGINT, &act, NULL);

	char *argumentos[MAX_ARGUMENTOS]; // Se inicializa el vector de argumentos que se va a utilizar.
	for(int j = 0; j < MAX_ARGUMENTOS; j++) {
		argumentos[j] = NULL;
	}

	argumentos[0] = argv[3]; // Registrar argumentos en el vector.
	for(int j = 4; j < argc; j++) {
		argumentos[j - 3] = argv[j];
	}


	for(i = 0; i < atoi(argv[1]); i++) { // Se ejecuta nVeces el comando con sus argumentos.
		int pidHijo = fork();
		if(pidHijo == 0) { // Código del hijo.
			execvp(argumentos[0], argumentos);
			cout << "Comando desconocido." << endl;
			exit(EXIT_FAILURE);
		}

		// Código del padre.
		wait(NULL);
		if(i+1 < atoi(argv[1])) sleep(atoi(argv[2])); // Se espera la cantidad de tiempo indicada después de cada ejecución, a menos que sea la última.
	}

}
