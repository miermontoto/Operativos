#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main() {
    // Cambiar privilegios del proceso a superusuario.
    setuid(0);
    setgid(0);

    // Verificar por pantalla que se han obtenido privilegios de superusuario.
    cout << "¿Privilegios de superusuario obtenidos? " << (geteuid() == 0 ? "Sí." : "No.") << endl;

    // Es imposible que el proceso obtenga privilegios de superusuario sin haber sido
    // ejecutado por el propio root, en cuyo caso el usuario efectivo del fichero ya
    // sería root y ya tendría privilegios de superusuario antes de cambiarlos.

    // Por lo tanto, en el único caso en el que la salida de arriba mostrará "Sí."
    // será cuando el proceso se ejecute mediante "sudo" o desde root, pero no se
    // habrá cambiado el uid del proceso.
}