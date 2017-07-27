#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

int aleatorio(int min, int max){

	return (rand() % (max-min+1)) + min;
}

double obtenerTiempoActual(){

	struct timespec tsp;
	clock_gettime( CLOCK_REALTIME, &tsp);

	double secs = (double) tsp.tv_sec;
	double nano = (double) tsp.tv_nsec / 1000000000.0;
	return secs + nano;
}

//estructura para pasar el arreglo y los indices
typedef struct arregloindices{
	int arreglo[];
	int inicio;
	int final;
} estructura;

void * funcion_hilo(void *arg){
	
	estructura *argumentos = (estructura *)arg;		//convertimos al tipo de dato correcto

	int i = 0;

	int suma = 0;
	for(i = argumentos->inicio; i < argumentos->final; i++){
		suma += argumentos->arreglo[i]
	}
	
	return (void *)suma;

}


