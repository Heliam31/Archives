#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[]){

    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, indice, temp ;
    bool isLigne;
    FILE* f;

    if (argc != 5) 
     {
       printf("Usage: ImageIn.pgm nomFichierDestination.dat colonne/ligne(0/1) indice \n"); 
       exit (1) ;
     }

    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);
    sscanf (argv[3],"%d",&temp); //si colonne (= False) si ligne (= True)
    sscanf (argv[4],"%d",&indice);

    isLigne = temp;

    OCTET *ImgIn;
    int *profil;

    //on stocke les dimensions de l'image
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nH;

    //on alloue un tableau d'octets pour l'image et on le rempli avec le contenu de l'image
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);


    if((f = fopen(cNomImgEcrite, "w")) == NULL){
        printf("On a un probleme pour ouvrir le fichier %s...", cNomImgEcrite);
        exit(EXIT_FAILURE);
    }


    //on boucle la ligne/colonne et on rempli le tableau PROFIL avec le niveau de gris de chaqun de ses pixels

    if(isLigne){

        allocation_tableau(profil, int, nW);
        for(int i = 0; i < nW; i++){
                
            profil[ImgIn[i*nW+indice]]++;           //CASSER CORRIGER

            fprintf(f, "%d\t%d\n", i, profil[i]);    
        }
     
    }else{

        allocation_tableau(profil, int, nH);
        for(int j = 0; j < nH; j++){
                
            profil[ImgIn[indice*nW+j]]++;   
        
            fprintf(f, "%d\t%d\n", j, profil[j]);
        }
    }
    
   

   

    //on ecrit le tableau dans le fichier cible .dat
    

    fclose(f);
    free(ImgIn);
    return 1;

}