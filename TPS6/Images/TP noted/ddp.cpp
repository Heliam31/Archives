#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[]){

    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;
    FILE* f;

    if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm nomFichierDestination.dat \n"); 
       exit (1) ;
     }

    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);

    OCTET *ImgIn;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);
    
    float occurences_de_couleurs_gris[256] = {0};

    //on boucle l'image
    for(int i = 0; i < nH; i++){
        for(int j = 0; j < nW; j++){
            
            //on incremente le nbr de pixel pour la valeur de niveau de gris associée
            occurences_de_couleurs_gris[ImgIn[i*nW+j]]++;   
        }
    }

    if((f = fopen(cNomImgEcrite, "w")) == NULL){
        printf("On a un probleme pour ouvrir le fichier %s...", cNomImgEcrite);
        exit(EXIT_FAILURE);
    }

    //on ecrit le tableau dans le fichier cible .dat
    for(int indice = 0; indice < 256; indice++){
        fprintf(f, "%d\t%f\n", indice, (occurences_de_couleurs_gris[indice]/nTaille));
    }

    fclose(f);
    free(ImgIn);
    return 1;

}