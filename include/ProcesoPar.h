#pragma once

#include <stdio.h> // perror
#include <unistd.h>
#include <pthread.h>

typedef struct ProcesoPar {
    pid_t id;
    pid_t id_father;
    int tuberia1[2];
    int tuberia2[2];
    pthread_t thread1;
    int (*f)(const void *, unsigned int);
    
}ProcesoPar_t;


ProcesoPar_t * lanzarProcesoPar(const  char  *nombreArchivoEjecutable ,
                 char *const *listListaComando,
                 char *const *env);

int destruirProcesoPar(ProcesoPar_t *procesoPar);

int establecerFuncionDeEscucha(ProcesoPar_t *procesoPar, int(*f)(const void *msg, unsigned int longitud));


int enviarMensajeProcesoPar(ProcesoPar_t *procesoPar, 
                            const void *mensaje, 
                            unsigned int longitud);

void *hilo(void *arg);

