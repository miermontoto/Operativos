#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

// Este ejemplo amplía el anterior haciendo que un proceso
// hijo envié automáticamente la señal SIGUSR1 cada cierto
// tiempo (utilizando para ello la llamada al sistema kill)

void SuenaTelefono(int sig) 
{
   struct sigaction act;
   
   std::cout << "Padre - Voy a atender al teléfono que está sonando" << std::endl;
   sleep(5);
   std::cout << "Padre - No era nadie, algún gracioso. ¡Me vuelvo al sofá!" << std::endl;

   // ES NECESARIO VOLVER A CAPTURAR LA SEÑAL PARA FUNCIONE LA SIGUIENTE
   // VEZ QUE SE ENVÍE
   // Relleno la información en la variable
   act.sa_handler = SuenaTelefono; // Para decir que llame a la función

   // Uso la llamada al sistema sigaction para indicar
   // la señal que quiero manejar y le paso la variable 
   // anterior
   sigaction(SIGUSR1, &act, NULL);
}

int main()
{
   // Declaro una variable de tipo struct sigaction
   // donde se indica la acción (de las tres posibles)

   // a realizar cuando llegue la señal (en este caso
   // llamar a una función)
   struct sigaction act;
   
   // Relleno la información en la variable
   act.sa_handler = SuenaTelefono; // Para decir que llame a la función

   // Uso la llamada al sistema sigaction para indicar
   // la señal que quiero manejar y le paso la variable 
   // anterior
   sigaction(SIGUSR1, &act, NULL);
   
   // Creo un proceso hijo
   if (fork()) {
      // Código del padre
      // Me paso el día tirado en el sofá
      while (true)
      {
         std::cout << "Padre - zzzzzZZZZZzzzzz" << std::endl;
         sleep(3);
      }
   }
   else {
      // Código del hijo
      while (true)
      {
         // Espero ciertos segundos al azar (entre 0 y 15)
         sleep(rand() % 15);
         std::cout << "Hijo - Me aburro. Voy a molestar un poco al viejo..." << std::endl;
         kill(getppid(), SIGUSR1);
         // El hijo está los 5 segundos que dura la llamada en silencio...
         sleep(5);
      }
   }
}