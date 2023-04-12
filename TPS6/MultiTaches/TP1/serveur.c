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

  if (argc != 2){
    printf("utilisation : %s port_serveur\n", argv[0]);
    exit(1);
  }

  /* Etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_DGRAM, 0);

  if (ds == -1){
    perror("Serveur : pb creation socket \n");
    close(ds);
    exit(1);
  }
  
  printf("Serveur : creation de la socket réussie \n");
  
  /* Etape 2 : Nommer la socket du seveur */
  struct sockaddr_in server_adress;
  server_adress.sin_family = AF_INET;
  server_adress.sin_port = htons((short) atoi(argv[1]));
  server_adress.sin_addr.s_addr = INADDR_ANY;

  int res = bind(ds, (struct sockaddr*) &server_adress, sizeof(server_adress));

  if (res  == -1){
     perror("erreur bind \n");
     close(ds);
     exit(1);
  }

  printf("bind fait \n");
  char message_recu[200];
  struct sockaddr_in client;
  socklen_t lad_client = sizeof(client);
 do{
  printf("Attente de message... \n");
  /* Etape 4 : recevoir un message du client (voir sujet pour plus de détails)*/


  int n = recvfrom(ds, &message_recu, 200, 0, (struct sockaddr *) &client, &lad_client);

  if (n == -1){
      perror("erreur recvfrom \n");
      close(ds);
      exit(1);
  }

  printf("Message recu de : %s \n", inet_ntoa(client.sin_addr));
  printf("le message recu est : %s \n", message_recu);
  
  /* Etape 5 : envoyer un message au serveur (voir sujet pour plus de détails)*/
  int s = sendto(ds, &n, sizeof (int), 0, (const struct sockaddr*) &client, sizeof(client));

  if (s == -1){
      perror("erreur send to \n");
      close(ds);
      exit(1);
  }}while(strcmp(message_recu,"fin\n") != 0);
  
  /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  close(ds);
  
  printf("Serveur : je termine\n");
  return 0;
}
