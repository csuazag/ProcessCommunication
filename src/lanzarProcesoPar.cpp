#include "../include/ProcesoPar.h"

#include <stdlib.h> //exit
#include <pthread.h> //pthread
#include <sys/types.h> //Fork + wait


ProcesoPar_t * 
lanzarProcesoPar(const  char  *nombreArchivoEjecutable ,
                 char *const  *listListaComando,
                 char *const  *env){

  ProcesoPar_t *processB = (ProcesoPar_t*) malloc(sizeof (ProcesoPar_t)); 
  
  int respPipe1 = pipe(processB->tuberia1);
  int respPipe2 = pipe(processB->tuberia2);
  if(respPipe1 || respPipe2  == -1){
    perror("Error creating the pipes: ");
    exit(EXIT_FAILURE);
  }
  
  if((processB->id = fork()) == 0){    
    dup2( processB->tuberia1[1],1);
    close(processB->tuberia1[0]);
    close(processB->tuberia1[1]);
    dup2( processB->tuberia2[0],0);
    close(processB->tuberia2[0]);
    close(processB->tuberia2[1]);
    execve((const char*)nombreArchivoEjecutable,(char * const *)listListaComando,(char* const *)env);
    perror("Error executing commandxxx: ");
    exit(EXIT_FAILURE);

  }else if(processB->id == -1){
    perror("Error creating the process B. Msg: ");
    return nullptr;
  }

  close(processB->tuberia1[1]);
  close(processB->tuberia2[0]);
  if((pthread_create(&processB->thread1, NULL, hilo, processB) < 0)){
    perror("Error creating pthread: ");
    exit(EXIT_FAILURE);
  }
  return  processB;
}

void*
hilo(void *args) {

  ProcesoPar_t *processB = (ProcesoPar_t *) args;
  char buffer[10240];
  while(true){
    int resp = read(processB->tuberia1[0], buffer, sizeof(buffer));
    if (resp > 0){   
      processB->f(buffer, resp);
    }else if(resp == -1){
      perror("Error reading from Hilo: ");
      exit(EXIT_FAILURE);      
    }
  }
  return nullptr;
}




