#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main() {
    for (int i=0; i < 3; i++) fork();
    cout << "Proceso " << getpid() << "; padre = " << getppid() << endl;
}