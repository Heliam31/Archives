#include <string.h>
#include <stdio.h>//perror
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "calcul.h"


struct paramsFonctionThread {
  int idThread;
};


void * fonctionThread (void * params){

  struct paramsFonctionThread * args = (struct paramsFonctionThread *) params;
  pthread_t moi =pthread_self();
  printf("mon Thread %ld ,proc %i \n", (long int)moi,  getpid());
  calcul(3);
  printf("calculed\n");
  pthread_exit(NULL);
}


int main(int argc, char * argv[]){

  if (argc < 2 ){
    printf("utilisation: %s  nombre_threads  \n", argv[0]);
    return 1;
  }     

  
  pthread_t threads[atoi(argv[1])];
  int donnee = 15;
  // creation des threads 
  for (int i = 0; i < atoi(argv[1]); i++){

    // Le passage de parametre est fortement conseille (eviter les
    // variables globles).

     // completer pour initialiser les parametres
    if (pthread_create(&threads[i], NULL,fonctionThread,(void*)donnee) != 0){
      perror("erreur creation thread");
      exit(1);
    }

    //int res = pthread_join(threads[i], NULL);
  }


// garder cette saisie et modifier le code en temps venu.
  char c; 
  printf("saisir un caractere \n");
  fgets(&c, 5, stdin);

  return 0;
 
}
 
