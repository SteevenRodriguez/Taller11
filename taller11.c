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

	int suma = (int) malloc (sizeof(int));
	for(i = argumentos->inicio; i <= argumentos->final; i++){
		
		suma += argumentos->arreglo[i]
	}
	
	return (void *)suma;

}

int main (int argc, char *argv[]){
	double time1 = obtenerTiempoActual();
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
	pthread_t hilos[num_hilos];
	int j=0;
	int razon = size/num_hilos;
	int v=0;
	for (j;j<num_hilo;j++){
		estructura *s_hilo = malloc(sizeof(estructura));
		s_hilo -> arreglo=&arreglo;
		s_hilo -> inicio=v;
		v += razon;
		s_hilo -> final=v-1; 
		int status=pthread_create(&hilos[j],NULL,funcion_hilo,(void*)s_hilo);
		if(status<0){
			fprintf(stderr,"Error al crear el hilo")
				}
		
	}

	int h=0;
	int total=0;
	for (h;h<num_hilo;h++){
		void *retorno = NULL
		int status1= pthread_join(hilos[h]),&retorno);
		total += (int)retorno;
		

	}
	double time2 = obtenerTiempoActual();
	double final= time2-time1;
	printf ("El tiempo final de ejecuccion es %d",final); 
}
