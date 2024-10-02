#include <stdio.h>    // Para funciones de entrada/salida como printf y scanf
#include <stdlib.h>   // Para EXIT_SUCCESS y EXIT_FAILURE
#include <unistd.h>   // Para fork(), getpid(), getppid(), pause() y usleep()
#include <sys/wait.h> // Para wait()
#include <signal.h>   // Para signal(), SIGUSR1 y kill()

void showtree(){
    char command[50];
    sprintf(command, "pstree %d", getpid);
    system(command);
}

void manejador(int sig) {}

void Kill(pid_t pid, int s){
    usleep(100);
    kill(pid, s);
}
int main(){
    pid_t pids[3], child, root = getpid();
    int idx;

    // Crea los procesos hijos
    for (idx = 0; idx < 3; idx++) {
        pids[idx] = fork();
        if (pids[idx] == -1) {
            perror("fork:");
            exit(EXIT_FAILURE);
        }
        if (pids[idx] == 0) { // Si es un proceso hijo, sale del bucle
            
            if(idx==1){
                child = fork(); //crea el hijo del proceso h2
            }

            break;
        }
    }

    if (root == getpid()) {
        usleep(100);
        showtree();
        printf("proceso: %d\n", getpid());
        kill(pids[2], SIGUSR1);
        pause();
        /
    } else {
        pause();
        printf("proceso: %d\n", getpid());
        if(idx==1){
            if(child){
                Kill(child, SIGUSR1);
                pause();
                printf("proceso: %d\n", getpid());
                Kill(pids[idx-1], SIGUSR1);
            }else{
                Kill(getppid(), SIGUSR1);
            }
        }
        else{
            if(idx==0) Kill(getppid(), SIGUSR1);
            else Kill(pids(idx-1), SIGUSR1);
        }
    }

    return EXIT_SUCCESS;
}
