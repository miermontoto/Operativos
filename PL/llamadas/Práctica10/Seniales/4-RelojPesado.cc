#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

// Si se quiere que un proceso haga algo cada xx segundos
// se puede utilizar la llamada al sistema alarm() que
// transcurridos dichos segundos autoenvía al proceso la
// señal SIGALRM
// Luego solo queda tratar dicha señal de manera que se
// llame a una función...

void MensajeCadaDiezSegundos(int sig) 
{
   std::cout << "¡¡Han pasado otros DIEZ segundos!!" << std::endl;

   // Tengo que volver a llamar a alarm() para que el reloj siga
   // funcionando
   alarm(10);
}

int main()
{
   // Declaro una variable de tipo struct sigaction
   // donde se indica la acción (de las tres posibles)
   // a realizar cuando llegue la señal (en este caso
   // llamar a una función)
   struct sigaction act;
   
   // Relleno la información en la variable
   act.sa_handler = MensajeCadaDiezSegundos; // Para decir que llame a la función

   // Uso la llamada al sistema sigaction para indicar
   // la señal que quiero manejar y le paso la variable 
   // anterior
   sigaction(SIGALRM, &act, NULL);
   
   // Me autoenvío la señal a los 10 segundos
   alarm(10);
   
   // El proceso ejecuta inmediatamente estas líneas de código
   // alarm() NO BLOQUEA AL PROCESO
   while (true)
   {
      std::cout << "Esperando a que pasen 10 segundos..." << std::endl;
      // Esta llamada al sistema SI BLOQUEA al proceso. El cual no se va 
      // a seguir ejecutando hasta que no reciba CUALQUIER señal
      pause();
   }
}