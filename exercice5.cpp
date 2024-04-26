#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_TASKS 3
// Structure pour stocker les informations sur une tâche périodique
typedef struct {
    int id;
    int period;
} PeriodicTask;

void *taskFunction(void *arg) {// Fonction exécutée par chaque thread
    PeriodicTask *task = (PeriodicTask *)arg;
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);    // Autoriser  ou declarer l'annulation du thread

    while (1) {  // Boucle infinie pour exécuter la tâche périodique
        sleep(task->period);// Attendre la période de la tâche
        printf("Task %d executed\n", task->id);// Afficher un message indiquant que la tâche a été exécutée
        pthread_testcancel();// Tester si que le thread être annulé
    }
    return NULL;
}

int main() {
    int TASK_PERIODS[] = {1, 2, 3};
    pthread_t threads[NUM_TASKS];// Tableau de threads
    PeriodicTask tasks[NUM_TASKS];// Tableau de task
    int i;

    for (i = 0; i < NUM_TASKS; ++i) {  // Création des threads pour chaque tâche périodique
        tasks[i].id = i + 1;
        tasks[i].period = TASK_PERIODS[i];
        pthread_create(&threads[i], NULL, taskFunction, (void *)&tasks[i]);// Création du thread pour exécuter la tâche
    }

    sleep(2);

    for (i = 0; i < NUM_TASKS; i++) {// Annulation et attente de la terminaison de chaque thread
        pthread_cancel(threads[i]);// Annulation du thread
        pthread_join(threads[i], NULL); // Attente de la terminaison du thread
    }
    return 0;
}

