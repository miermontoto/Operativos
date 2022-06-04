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

int longitudNum(int x) {
    int i = 0;
    while (x != 0) {
        x /= 10;
        i++;
    }
    return i;
}

/**
 * Comando externo 'sudo' que permite ejecutar cualquier programa con privilegios máximos.
 * 
 * Se comprueba el UID de dos maneras:
 *  - Se comprueba si el 'atoi()' de la línea del fichero devuelve exactamente el UID del usuario actual.
 *  - Se comprueba si tanto la línea como el UID del usuario tienen la misma longitud.
 * Esto evita que el programa admita como válido un UID que comienza por el UID del usuario actual, pero que no es
 * exactamente igual, como por ejemplo "1000 != 1000asldkfmklasd".
 * 
 * Se supone que el archivo binario que genera la compilación de este programa tiene el permiso especial 's' y que el
 * propietario es el superusuario. Se recomienda además que el archivo 'sudoers.txt' sea propiedad del superusuario y
 * que no lo puedan modificar otros usuarios ni grupos.
 * 
 * @param argc Número de argumentos.
 * @param argv Argumentos.
 * 
 */
int main(int argc, char* argv[]) {

    // Comprobar el número de argumentos.
    if(argc < 2) {
        cout << "Uso: " << argv[0] << " <comando> [argumentos]" << endl;
        exit(EXIT_FAILURE);
    }

    // Comprobar que el archivo 'sudoers.txt' existe y se puede abrir.
    FILE* sudoersFile = fopen("sudoers.txt", "r");
    if(sudoersFile == NULL) {
        cout << "Error: No se puede abrir el fichero 'sudoers.txt'." << endl;
        exit(EXIT_FAILURE);
    }

    // Comprobar que el UID del usuario actual forma parte de la lista.
    uid_t userUID = getuid(); // UID del usuario actual.
    int userUIDlen = longitudNum(userUID); // Longitud del UID del usuario actual.
    bool found = false; // Valor booleano que controla si el UID del usuario actual forma parte de la lista.
    while(!feof(sudoersFile)) { // Se lee el fichero hasta el final del fichero.
        char line[256]; // Buffer para almacenar una línea del fichero.
        fgets(line, 256, sudoersFile); // Se lee una línea del fichero.
        if(strlen(line) > 0) { // Se comprueba que la línea no esté vacía.
            line[strlen(line) - 1] = '\0'; // Se elimina el carácter de fin de línea.
            if(userUID == atoi(line) && userUIDlen == strlen(line)) { // Se comprueba si el UID del usuario actual es igual al UID de la línea.
                found = true;
                break;
            }
        }
    }

    fclose(sudoersFile); // Se cierra el fichero.

    //cout << "UID: " << userUID << endl;

    // Si el usuario actual no forma parte de la lista, salir.
    if(!found) {
        cout << "Error: No tiene permisos para ejecutar el comando 'sudo'." << endl;
        exit(EXIT_FAILURE);
    }

    seteuid(0); // Se establece el UID efectivo al del superusuario.
    execvp(argv[1], argv + 1); // Ejecutar el comando indicado.
    cout << "Error: comando inválido." << endl;
    exit(EXIT_FAILURE);
}
