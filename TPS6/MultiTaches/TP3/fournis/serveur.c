#include <stdio.h>//perror
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>//close
#include <stdlib.h>
#include <string.h>


#define MAX_BUFFER_SIZE 146980


int main(int argc, char *argv[])
{
  /* etape 0 : gestion des paramètres si vous souhaitez en passer */


  
  /* etape 1 : creer une socket d'écoute des demandes de connexions*/

   int ds = socket(PF_INET, SOCK_STREAM, 0);

  if (ds == -1){
    perror("Serveur : pb creation socket \n");
    close(ds);
    exit(1);
  }
  
  printf("Serveur : creation de la socket réussie \n");
  
  /* etape 2 : nommage de la socket */
 
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

  /* etape 3 : mise en ecoute des demandes de connexions */
 
   int ecoute = listen(ds, 10);


  if (ecoute == -1){
    perror("erreur listen\n");
    close(ds);
    exit(1);
  }

  printf("écoute...\n");

  /* etape 4 : plus qu'a attendre la demande d'un client */
 
 struct sockaddr_in Client;
  socklen_t lgClient = sizeof(server_adress);

  int dsClient = accept(ds, (struct sockaddr*) &Client, &lgClient);

  int tailleFichier;
  int r = recv(dsClient, &tailleFichier, MAX_BUFFER_SIZE ,0);


  int totalRecv = 0; // un compteur du nombre total d'octets recus d'un client

  
  /* le protocol d'echange avec un client pour recevoir un fichier est à définir. Ici seul un exemple de code pour l'écriture dans un fichier est founi*/
  char* nomFichier;
  int tailleNom;
  int rn = recv(dsClient, &tailleNom, sizeof(int), 0);
  int rc =  recv(dsClient, &nomFichier, tailleNom ,0);
  char* filepath = "../reception/"; // cette ligne n'est bien-sur qu'un exemple et doit être modifiée : le nom du fichier doit être reçu.
   strcat(filepath, nomFichier);

  printf("fichier va etre ecris dans %s", nomFichier);
   
  // On ouvre le fichier dans lequel on va écrire
  FILE* file = fopen(filepath, "wb");
  if(file == NULL){
    perror("Serveur : erreur ouverture fichier: \n");
    exit(1);  
  }

  char * buffer;
  int tailleRecu=0;

  while(tailleRecu<tailleFichier){
    int r = recv(dsClient, &buffer, MAX_BUFFER_SIZE, 0);
    size_t written = fwrite(buffer, sizeof(char), strlen(buffer)+1, file); 
    tailleRecu += r;
      if(written < strlen(buffer)+1){  // cette ligne est valide uniquement pour ce simple exemple
    perror("Serveur : Erreur a l'ecriture du fichier \n");
    fclose(file); 
  }

  }

  printf("Serveur : ecriture dans fichier reussie. Vous pouvez vérifier la création du fichier et son contenu.\n");
  // fermeture du fichier
  fclose(file);
    
  printf("Serveur : c'est fini\n");
}








