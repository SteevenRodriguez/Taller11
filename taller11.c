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
	int *arreglo;
	int inicio;
	int final;
} estructura;

void * funcion_hilo(void *arg){
	
	estructura *argumentos = (estructura *)arg;		//convertimos al tipo de dato correcto

	int i = 0;

	long suma = 0;
	for(i = argumentos->inicio; i <= argumentos->final; i++){
		
		suma += argumentos->arreglo[i];
	}
	//printf ("La suma de este hilo es %lu\n", suma);
	
	return (void *) suma;

}

int main (int argc, char *argv[]){
	srand(time(NULL));
	if (argc!=3){
		printf("No se ingreso bien los parametros");
	}

	int size =atoi(argv[1]);
	int num_hilos = atoi(argv[2]);

	int *arreglo=NULL;
	arreglo= (int *) malloc(size * sizeof(int));

	int i;

	for (i=0;i<size;i++){
		int num= aleatorio(1,14);
		arreglo[i]=num;

	}
	
	double time1 = obtenerTiempoActual();
	
	pthread_t hilos[num_hilos];
	int j;
	int razon = size/num_hilos;
	int v=0;
	if (size % num_hilos == 0){ //numeros con division exacta
		for (j=0;j<num_hilos;j++){
			estructura *s_hilo = malloc(sizeof(estructura));
			s_hilo -> arreglo=arreglo;
			s_hilo -> inicio=v;
			v += razon;
			s_hilo -> final=v-1; 
			int status=pthread_create(&hilos[j],NULL,funcion_hilo,(void*)s_hilo);
			if(status<0){
				fprintf(stderr,"Error al crear el hilo");
			}
		
		}
	}
	else{
		for (j=0;j<num_hilos;j++){  //numeros con division no exacta
			estructura *s_hilo = malloc(sizeof(estructura));
			s_hilo -> arreglo=arreglo;
			s_hilo -> inicio=v;
			v += razon;
			if(v>size){
				s_hilo -> final=size;
			}else{
				s_hilo -> final=v; 
			}
			v += 1;
			int status=pthread_create(&hilos[j],NULL,funcion_hilo,(void*)s_hilo);
			if(status<0){
				fprintf(stderr,"Error al crear el hilo");
			}
		
		}
	}

	int h;
	long total=0;
	for (h=0;h<num_hilos;h++){
		void *retorno = malloc(sizeof(long));
		
		pthread_join(hilos[h],retorno);
		
		total += *((long *) retorno);
		free(retorno);
		
		
		

	}
	//printf ("La suma total es %lu\n",total);
	double time2 = obtenerTiempoActual();
	double final= time2-time1;
	printf("%.9f\n",final);
	//printf ("El tiempo final de ejecuccion es %.9f\n",final);
	free(arreglo);
	
	return(0);
}
