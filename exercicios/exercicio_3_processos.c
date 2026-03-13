#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    pid_t pid[2] = {-1, -1};

    printf("Processo Pai comecou\n");
    pid[0]= fork();

    if(pid[0] < 0){
        printf("Erro na criacao do processo filho 1\n");
        exit(-1);
    }
    else if(pid[0]==0){ // primeiro filho
        for(int i=100; i<=199; ++i){
            printf("FILHO 1: PPID = %d, PID = %d, num = %d\n", getppid(), getpid(), i);
            sleep(1);
        }
        printf("Filho 1 vai morrer\n");
        exit(0);
    }
    else{
        printf("Filho 1 foi criado\n");
        // pai apos criacao do primeiro filho
        pid[1] = fork();
    }

    if(pid[1]<0){
        printf("Erro na criacao do processo filho 1\n");
        exit(-1);
    }
    else if(pid[1]==0){ // segundo filho executando
        for(int i=200; i<=299; ++i){
            printf("FILHO 2: PPID = %d, PID = %d, num = %d\n", getppid(), getpid(), i);
            sleep(1);
        }
        printf("Filho 2 vai morrer\n");
        exit(0);

    }
    else{
        printf("Filho 2 foi criado\n");

        printf("Iniciando a contagem de 0 a 50...\n");
        for(int i=0; i<=50; ++i){
            printf("PAI: PID = %d, num = %d\n", getpid(), i);
            sleep(2);
        }
    }


    return 0;
}
