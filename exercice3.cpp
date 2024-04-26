#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Premi�re t�che ex�cut�e par un thread
void* Tache1(void*arg){
	int i=0;
	while(i<5){
		printf("Execution de Tache1\n");
		sleep(1); // Attente d'une seconde
		i++;
	}return NULL;
}
void* Tache2(void*arg){// Deuxi�me t�che ex�cut�e par un thread
	int j=0;
	while(j<5){
		printf("Execution de Tache2\n");
		sleep(2);
		j++;
	}return NULL;
}
//les deux threads sont cr��s simultan�ment sans attendre que l'un ou l'autre se termine. 

/*int main(int argc, char *argv[]){
	pthread_t thread1,thread2;
	pthread_create(&thread1,NULL,Tache1,NULL);
	pthread_create(&thread2,NULL,Tache2,NULL);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	return EXIT_SUCCESS;
}*/
int main(int argc, char *argv[]){
	pthread_t thread1,thread2;   
	pthread_create(&thread1,NULL,Tache1,NULL);// Cr�ation du premier thread pour ex�cuter Tache1
	pthread_join(thread1,NULL); // Attente de la fin du premier thread avant de cr�er le deuxi�me
	pthread_create(&thread2,NULL,Tache2,NULL);// Cr�ation du deuxi�me thread pour ex�cuter Tache2
	pthread_join(thread2,NULL);    // Attente de la fin du deuxi�me thread
	return EXIT_SUCCESS;
}



