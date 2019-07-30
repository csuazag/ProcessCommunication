#include "../include/ProcesoPar.h"


int establecerFuncionDeEscucha(ProcesoPar_t *procesoPar, int(*f)(const void *, unsigned int )){
  
  if(!(procesoPar->f = f)){
    perror("Error when you try to assigment the function to the structure: ");
    return -1;
  }
  return 0;
}



