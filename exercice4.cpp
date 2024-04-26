#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void*thread_func1(void*arg){// Fonction exécutée par le premier thread
	printf("Bonjour ! \n");
	return NULL;
}
void*thread_func2(void*arg){// Fonction exécutée par le deuxième thread
	printf("Salut ! \n");
	return NULL;
}
int main(int argC, char *argv[]){
	pthread_t thread1,thread2;
	pthread_create(&thread1, NULL,thread_func1,NULL); // Création du premier thread pour exécuter thread_func1
	pthread_create(&thread1, NULL,thread_func2,NULL);// Création du deuxième thread pour exécuter thread_func2
	pthread_join(thread1,NULL);   // Attente de la fin du premier thread
	pthread_join(thread2,NULL);   // Attente de la fin du deuxième thread
	return EXIT_SUCCESS;
}


