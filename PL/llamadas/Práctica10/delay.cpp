#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

using namespace std;

int main(int argc, char** argv) {
    // Comprobar que se introducen dos argumentos.
    if (argc != 3) {
        cout << "Uso: " << argv[0] << " <segundos> <orden> " << endl;
        return 1;
    }

    sleep(atoi(argv[1]));
    execvp(argv[2], argv + 2);
}