#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>

/* Programme serveur */

int main(int argc, char *argv[]) {

  if (argc != 1){
    printf("utilisation : %s port_serveur\n", argv[0]);
    exit(1);
  }

  /* Etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_STREAM, 0);

  if (ds == -1){
    perror("Serveur : pb creation socket \n");
    close(ds);
    exit(1);
  }
  
  printf("Serveur : creation de la socket réussie \n");
  
  /* Etape 2 : Nommer la socket du seveur */
  struct sockaddr_in server_adress;
  server_adress.sin_family = AF_INET;
  server_adress.sin_addr.s_addr = INADDR_ANY;

  int res = bind(ds, (struct sockaddr*) &server_adress, sizeof(server_adress));

  socklen_t lgSad = sizeof(server_adress);


  if (res  == -1){
     perror("erreur bind \n");
     close(ds);
     exit(1);
  }

  printf("bind fait \n");

  int sock = getsockname(ds, (struct sockaddr*) &server_adress, &lgSad);

    if (sock  == -1){
     perror("erreur bind \n");
     close(ds);
     exit(1);
  }
  printf("Le socket est : %i \n",(int)ntohs(server_adress.sin_port));

  int ecoute = listen(ds, 10);


  if (ecoute == -1){
    perror("erreur listen\n");
    close(ds);
    exit(1);
  }

  printf("écoute...\n");

  struct sockaddr_in Client;
  socklen_t lgClient = sizeof(server_adress);

  int dsClient = accept(ds, (struct sockaddr*) &Client, &lgClient);

  char message_recu[4000];
  printf("Attente de message... \n");

  int n = recv(dsClient, message_recu, sizeof(message_recu) ,0);

  if (n == -1){
      perror("erreur recv \n");
      close(ds);
      exit(1);
  }

  printf("Message recu de : %s \n", inet_ntoa(Client.sin_addr));
  printf("le message recu est : %s \n", message_recu);
  


  /* Etape 5bis : envoie message au client */

  int message_envoie=strlen(message_recu);
  int j= send(dsClient, &message_envoie, message_envoie,0);
  if (j == -1){
      perror("erreur send \n");
      close(ds);
      exit(1);
  }

  printf("le message envoyé est : %i \n", message_envoie);
  
  /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  close(ds);
  
  printf("Serveur : je termine\n");
  return 0;
}
