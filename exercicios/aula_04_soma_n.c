#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>


void soma_1(int *a){
    printf("Executando filho...\n");
    *a += 1;
}

int main(int argc, char *argv []){
    // converter o numero em char para inteiro
    int num = atoi(argv[1]);
    
    // armazenar os PIDs dos processos
    int pid[num]; 

    // memoria compartilhada
    int *mem;

    int id_da_memoria = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666); 
    mem  = shmat(id_da_memoria, NULL, 0);

    if(mem < 0){
        printf("Erro de alocacao da memoria compartilhada!\n");
        return 0;
    }

    *mem = 0;

    for(int i=0; i<num; i++){
        pid[i] = fork();

        if(pid[i] == 0){
            mem  = shmat(id_da_memoria, NULL, 0);
            sleep(1);
            soma_1(mem);
            shmdt(mem);
            exit(0);
        }
        else if(pid[i]<0){
            printf("Erro no fork!\n");
        }
    }

    for(int i=0; i<num; i++) wait(NULL);

    printf("Valor ao final: %d\n", *mem);

    shmdt(mem); // havia esquecido de liberar do pai
    shmctl(id_da_memoria, IPC_RMID, NULL); // deleta o espaco compartilhado

    return 0;
}