#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// Fonction ex�cut�e par le thread
void *print_message(void *ptr) {
    char *message = (char *) ptr;
      // Affichage du message
    printf("%s \n", message);
    pthread_exit(NULL);
}
int main() {
   // Message � afficher
    char message[] = "Bonjour tous le monde  !";
     
    // D�claration de la variable de thread
    
    pthread_t thread;
     // Cr�ation du thread
     pthread_create(&thread, NULL, (void *(*)(void *))printf, (void *)message);
        // Attente de la fin du thread
       pthread_join(thread,NULL);
    // Sortie du programme avec succ�s
        return EXIT_SUCCESS;
}

