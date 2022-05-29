#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

// La acción más flexible (e interesante) al recibir
// una señal es ejecutar un código (una función).
// Este programa ejecuta la función SuenaTelefono()
// cuando recibe la señal SIGUSR1

void SuenaTelefono(int sig) 
{
   struct sigaction act;
   
   std::cout << "Voy a atender al teléfono que está sonando" << std::endl;
   sleep(5);
   std::cout << "Me vuelvo al sofá" << std::endl;

   // Es necesario volver a capturar la señal
   // para que funcione la próxima vez que se envíe
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
   
   // Me paso el día tirado en el sofá
   while (true)
   {
      std::cout << "zzzzzZZZZZzzzzz" << std::endl;
      sleep(3);
   }
}