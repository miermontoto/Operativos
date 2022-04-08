int main() {
    int var;
    pid_t pid;
    cout << "Comienzo la ejecución" << endl;
    var = 88;
    if ((pid = fork()) == EXIT_FAILURE) exit(EXIT_FAILURE);
    if (!pid) { glob++; var++; }
    else // Se asegura que padre espera a que termine hijo
    sleep(2);
    cout << "pid = " << getpid() << ", glob = " << glob
    << ", var = " << var << endl;
    exit(EXIT_SUCCESS);
}