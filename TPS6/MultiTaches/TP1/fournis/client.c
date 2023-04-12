#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>

/* Programme client */

int main(int argc, char *argv[]) {

  if (argc != 3){
    printf("utilisation : %s ip_serveur port_serveur port_client\n", argv[0]);
    exit(1);
  }

  /* Etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_DGRAM, 0);

  if (ds == -1){
    perror("Client : pb creation socket \n");
    close(ds);
    exit(1);
  }

  printf("Client : creation de la socket réussie \n");
  
  /* Etape 2 : Nommer la socket du client */
  struct sockaddr_in client;
  client.sin_family = AF_INET;
  client.sin_addr.s_addr = INADDR_ANY;

  int res = bind(ds, (struct sockaddr*) &client, sizeof(client));

  if (res  == -1){
     perror("erreur bind \n");
     close(ds);
     exit(1);
  }

  printf("bind fait, adresse + port %i:%i \n",client.sin_addr.s_addr,client.sin_port);


  socklen_t lgSad = sizeof(client);
  int sock = getsockname(ds, (struct sockaddr*) &client, &lgSad);

    if (sock  == -1){
     perror("erreur bind \n");
     close(ds);
     exit(1);
  }
  printf("Le socket est : %i \n",(int)ntohs(client.sin_port));
  
  /* Etape 3 : Désigner la socket du serveur */
  struct sockaddr_in serveur;
  serveur.sin_family = AF_INET;
  serveur.sin_port = htons((short) atoi(argv[2]));
  serveur.sin_addr.s_addr = inet_addr(argv[1]);
  socklen_t lad_serveur = sizeof(serveur);
  
  /* Etape 4 : envoyer un message au serveur  (voir sujet pour plus de détails)*/
  char message [100];
  printf("Entrez votre message: ");
  fgets(message, 100, stdin);
  int conf = sendto(ds, message, strlen(message)+1, 0, (const struct sockaddr*)&serveur, lad_serveur);

  if (conf == -1){
      perror("message pas envoyé \n");
      close(ds);
      exit(1);
  }

  /* Etape 5 : recevoir un message du serveur (voir sujet pour plus de détails)*/
  char recu[200];
  char recu_s = recvfrom(ds, &recu, 200, 0, (struct sockaddr *) &serveur, &lad_serveur);

  if (recu_s == -1){
      perror("pb recvfrom \n");
      close(ds);
      exit(1);
  }

  printf("reponse du serveur : %s \n", recu);

  /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  close(ds);
  
  printf("Client : je termine\n");

  return 0;
}
