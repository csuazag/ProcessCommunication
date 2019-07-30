#include "../include/ProcesoPar.h"


int enviarMensajeProcesoPar( ProcesoPar_t *procesoPar,
                             const void   *mensaje,
                             unsigned int longitud ){


    if( (write(procesoPar->tuberia2[1], mensaje, longitud)) == -1){
        perror("Error sending the message: ");
        return -1;
    }
    sleep(1);    
    return 0;
}


