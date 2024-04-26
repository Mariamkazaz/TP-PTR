#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_TASKS 3
// Structure pour stocker les informations sur une t�che p�riodique
typedef struct {
    int id;
    int period;
} PeriodicTask;

void *taskFunction(void *arg) {// Fonction ex�cut�e par chaque thread
    PeriodicTask *task = (PeriodicTask *)arg;
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);    // Autoriser  ou declarer l'annulation du thread

    while (1) {  // Boucle infinie pour ex�cuter la t�che p�riodique
        sleep(task->period);// Attendre la p�riode de la t�che
        printf("Task %d executed\n", task->id);// Afficher un message indiquant que la t�che a �t� ex�cut�e
        pthread_testcancel();// Tester si que le thread �tre annul�
    }
    return NULL;
}

int main() {
    int TASK_PERIODS[] = {1, 2, 3};
    pthread_t threads[NUM_TASKS];// Tableau de threads
    PeriodicTask tasks[NUM_TASKS];// Tableau de task
    int i;

    for (i = 0; i < NUM_TASKS; ++i) {  // Cr�ation des threads pour chaque t�che p�riodique
        tasks[i].id = i + 1;
        tasks[i].period = TASK_PERIODS[i];
        pthread_create(&threads[i], NULL, taskFunction, (void *)&tasks[i]);// Cr�ation du thread pour ex�cuter la t�che
    }

    sleep(2);

    for (i = 0; i < NUM_TASKS; i++) {// Annulation et attente de la terminaison de chaque thread
        pthread_cancel(threads[i]);// Annulation du thread
        pthread_join(threads[i], NULL); // Attente de la terminaison du thread
    }
    return 0;
}

