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
  int ds = socket(PF_INET, SOCK_STREAM, 0);

  if (ds == -1){
    perror("Client : pb creation socket \n");
    close(ds);
    exit(1);
  }

  printf("Client : creation de la socket réussie \n");
  
  /*Désigner la socket du serveur */
  struct sockaddr_in serveur;
  serveur.sin_family = AF_INET;
  serveur.sin_port = htons((short) atoi(argv[2]));
  serveur.sin_addr.s_addr = inet_addr(argv[1]);
  socklen_t lad_serveur = sizeof(serveur);
  connect(ds,(struct sockaddr* )&serveur, lad_serveur );
  
  /* Etape 4 : envoyer un message au serveur  (voir sujet pour plus de détails)*/
  char message1 [1500];
  char message2 [1500];
  printf("Entrez votre message: \n");
  fgets(message1, 1500, stdin);
  fgets(message2, 1500, stdin);

  char *tmp = strchr(message1, '\n');
  if(tmp) *tmp = '\0';

  *tmp = strchr(message2, '\n');
  if(tmp) *tmp = '\0';

  int send1 = send(ds, message1, strlen(message1), 0);
  int send2 = send(ds, message2, strlen(message2), 0);

  if (send1 == -1 || send2==-1){
      perror("message pas envoyé \n");
      close(ds);
      exit(1);
  }

  int taille=strlen(message1)+strlen(message2);

  /* Etape 5bis : recoit message du serveur */

  int message_recu;
  int j= recv(ds, &message_recu, sizeof(int),0);
  if (j == -1){
      perror("erreur recv \n");
      close(ds);
      exit(1);
  }

  printf("message recu : %i\n", message_recu);
  printf("taille: %i\n", taille);

  /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  close(ds);
  
  printf("Client : je termine\n");

  return 0;
}




//Quand on connait la taille
int sendTCP ( int sock, char* msg, int size_msg){
  int reste = size_msg;
  while(reste!= 0){
    int res = send(sock, msg+(size_msg-reste), reste, 0);
    if (res<=0) return res;
    reste -= res;
    }
    return -1;
  }