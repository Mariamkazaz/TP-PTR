#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// Fonction exécutée par le thread
void *print_message(void *ptr) {
    char *message = (char *) ptr;
      // Affichage du message
    printf("%s \n", message);
    pthread_exit(NULL);
}
int main() {
   // Message à afficher
    char message[] = "Bonjour tous le monde  !";
     
    // Déclaration de la variable de thread
    
    pthread_t thread;
     // Création du thread
     pthread_create(&thread, NULL, (void *(*)(void *))printf, (void *)message);
        // Attente de la fin du thread
       pthread_join(thread,NULL);
    // Sortie du programme avec succès
        return EXIT_SUCCESS;
}

