#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

// Cuando se pulsa CTRL-C en el teclado se envía
// al proceso en primer plano la señal SIGINT, que
// aborta al proceso.

// Vamos a hacer que nuestro proceso ignore esa señal
// y lo vamos a INMUNIZAR!!

int main()
{
   // Declaro una variable de tipo struct sigaction
   // donde se indica la acción (de las tres posibles)
   // a realizar cuando llegue la señal (en este caso
   // será ignorarla).
   struct sigaction act;
   
   // Relleno la información en la variable
   act.sa_handler = SIG_IGN; // Para decir que la ignore

   // Uso la llamada al sistema sigaction para indicar
   // la señal que quiero ignorar y le paso la variable 
   // anterior
   sigaction(SIGINT, &act, NULL);
   
   // Espero 30 segundos y no se me va a poder
   // interrumpir con CTRL-C
   std::cout << "Vas a estar 30 segundos sin prompt ¡y no me vas a poder abortar!" << std::endl;
   std::cout << "¡¡SOY INMUNE!!" << std::endl;
   sleep(30);

   // Le vamos a quitar la inmunidad
   act.sa_handler = SIG_DFL; // Para realizar la acción por defecto
                             // del SO (que es abortarlo)
   sigaction(SIGINT, &act, NULL);
   
   // Espero 1000 segundos, ¡lástima que ahora no sea inmune! :-(
   std::cout << "¿Cansaste de esperar? ¡¡Pues ahora te lo quito 1000 segundos más!!" << std::endl;
   sleep(1000);
}