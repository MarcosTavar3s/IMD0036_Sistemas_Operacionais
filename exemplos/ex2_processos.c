#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int value = 5;

int main(){
    pid_t pid;

    pid = fork();

    // se for o processo filho
    if(pid == 0){
        value += 15;
        printf("FILHO: value = %d\n", value);
        return 0; // acaba o processo filho aqui
    }

    else if(pid > 0){
        wait(NULL);
        printf("PAI: value = %d\n", value);
    }

    return 0;
}