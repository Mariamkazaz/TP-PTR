#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10  // Taille du tableau
#define NUM_THREADS 4    // Nombre de threads


int totalSum = 0;// Somme totale des éléments du tableau

// Structure pour passer les arguments aux threads
typedef struct {
    int *start;// Pointeur vers le début de la section du tableau
    int *end;// Pointeur vers le FIN de la section du tableau
    pthread_mutex_t *lock;// Verrou pour synchroniser l'accès 
} PartialSumArgs;

// Fonction exécutée par chaque thread pour calculer la somme partielle
void *sum_partial(void *args) {
    PartialSumArgs *partialArgs = (PartialSumArgs *)args;

    int partialSum = 0;
    // Calcul de la somme partielle de la section du tableau
    int *p;
    for (p = partialArgs->start; p < partialArgs->end; p++) {
        partialSum += *p;
    }

    // Verrouillage de la section  pour mettre à jour totalSum
    pthread_mutex_lock(partialArgs->lock);

    totalSum += partialSum;

    pthread_mutex_unlock(partialArgs->lock);

    pthread_exit(NULL);
}

int main() {
	 // Initialisation du tableau
    int array[ARRAY_SIZE];
    int i;

    for (i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i + 1;
    }
   // Initialisation du verrou
    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);


    pthread_t threads[NUM_THREADS];  // Tableau de threads

    PartialSumArgs threadArgs[NUM_THREADS]; // Tableau d'arguments pour chaque thread

    int sectionSize = ARRAY_SIZE / NUM_THREADS; // Calcul de la taille de chaque section du tableau
    for (i = 0; i < NUM_THREADS; ++i) {
    	 // Configuration des arguments pour chaque thread
        threadArgs[i].start = (array+i * sectionSize);
        threadArgs[i].end = (array + ((i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * sectionSize));
        threadArgs[i].lock = &lock;
// Création du thread
        if (pthread_create(&threads[i], NULL, sum_partial, (void *)&threadArgs[i]) != 0) {
            fprintf(stderr, "Erreur lors de la creation du thread %d\n", i);
            return 1;
        }
    }

    for (i = 0; i < NUM_THREADS; ++i) {// Attente de la fin de chaque thread
        pthread_join(threads[i], NULL);
    }

    printf("Somme totale : %d\n", totalSum); // Affichage de la somme totale

    pthread_mutex_destroy(&lock);

    return 0;
}
