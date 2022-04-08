#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define MAX_ARGUMENTOS 20

unsigned ObtieneArgumentos(string comando, char *argv[]) {
  // NECESITA: Una linea de entrada (o comando de usuario)
  // MODIFICA: argv para que tenga el comando en forma de ARGV
  // PRODUCE: El número de argumentos de la orden

  string separadores=" \t";
  int comienzo, fin, n_argumento=0;

  // Vacía y libera el contenido de argv
  for (int i=0; argv[i] != NULL; i++) {
    free(argv[i]);
    argv[i]=NULL;
  }

  // Se salta los separadores iniciales
  comienzo=comando.find_first_not_of(separadores);
  while (comienzo >= 0 && comienzo < comando.size()) {
    // Localiza el comienzo del siguiente separador
    fin=comando.find_first_of(separadores, comienzo);
    // Comprueba si llego al final
    if (fin < 0)
      // pone fin al siguiente al último
      fin=comando.size();
    // Entre comienzo y fin (excluido) esta el argumento
    argv[n_argumento] = (char *)malloc(fin-comienzo+1);
    strcpy(argv[n_argumento], comando.substr(comienzo, fin-comienzo).c_str());
    // Un argumento más
    n_argumento++;
    // Se salta los separadores actuales
    comienzo=comando.find_first_not_of(separadores, fin+1);
  }
  // Pone el indicador de fin de argumentos
  argv[n_argumento] = NULL;
  // Retorna el número de argumentos
  return n_argumento;
}

int main() {
  string comando;
  string el_prompt="$";
  char *comando_argv[MAX_ARGUMENTOS];
  int n_args, pid_hijo;

  // Inicializa comando_argv
  for (int i=0; i<MAX_ARGUMENTOS; i++)
    comando_argv[i]=NULL;

  // Bucle principal del shell. Siempre lee de la entrada estándar el siguiente comando
  // hasta que encuentre fin de fichero
  while (!cin.eof()) {
    // Imprime el prompt
    cout << el_prompt << " ";

    // Lee una linea desde la entrada estándar
    getline(cin, comando);

    // Separa el comando en ejecutable más argumentos.
    n_args = ObtieneArgumentos(comando, comando_argv);
    
    if (n_args != 0) {
       // Ejecuta el comando indicado por el usuario
       pid_hijo = fork();
       if (pid_hijo == 0) {
          // Código del hijo
          execvp(comando_argv[0], comando_argv);
       }
    }
  }
} 
