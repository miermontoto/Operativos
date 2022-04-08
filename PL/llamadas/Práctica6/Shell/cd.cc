#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
   char *newdir;

   // Si no se indica ruta de destino se cambia
   // al directorio personal del usuario, indicado
   // por la variable de entorno HOME
   if (argc == 1) {
      newdir = getenv("HOME");
   }
   else
      newdir = argv[1];

   // Utiliza la llamada al sistema chdir para
   // cambiar el directorio por defecto
   if (chdir(newdir) == -1) 
   {
      // Hubo un error
      perror("Error cd");
      exit(EXIT_FAILURE);
   }
   exit(EXIT_SUCCESS);
}
