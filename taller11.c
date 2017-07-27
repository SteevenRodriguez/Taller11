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

int main (int argc, char *argv[]){

srand(time(0));
if (argc!=3){
	printf("No se ingreso bien los parametros");
}

int size =atoi(argv[1]);
int num_hilos = atoi(argv[2]);

int *arreglo=NULL;
arreglo= (int *) malloc(size * sizeof(int));

int i=0;

for (i;i<size;i++){
	int num= aleatorio(1,200);
	arreglo[i]=num;

}


}
