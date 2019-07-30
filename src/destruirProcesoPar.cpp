#include "../include/ProcesoPar.h"

#include <sys/types.h>
#include <signal.h>


#include <pthread.h>//Join



int destruirProcesoPar(ProcesoPar_t *procesoPar){
    sleep(1);
    pthread_cancel(procesoPar->thread1);
    close(procesoPar->tuberia1[0]);
    close(procesoPar->tuberia2[1]);
    int resp = kill(procesoPar->id, SIGKILL);
    delete procesoPar;    
    if(resp == -1){        
        perror("Error killing the process: ");
        return -1;
    }    
    return 0;
}
