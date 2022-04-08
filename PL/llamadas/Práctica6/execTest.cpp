#include <iostream>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;

int main() {
    pid_t pid = fork();
    switch (pid) {
        case -1: // Error del fork
            perror("fork");
            break;
        case 0: // Proceso hijo
            execlp("ls", "ls", "-l", NULL);
            perror("exec");
            break;
        default: // Proceso padre
            break;
    }
}