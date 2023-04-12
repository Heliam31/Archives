#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[]){

    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;
    FILE* f;

    if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }

    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);
    
    float occurences_de_couleurs_gris[256] = {0};

    //on boucle l'image
    for(int i = 0; i < nH; i++){
        for(int j = 0; j < nW; j++){
            occurences_de_couleurs_gris[ImgIn[i*nW+j]]++;   
        }
    }

    //on ecrit le tableau dans le fichier cible .dat
    float tab[256] = {0};
    float temp=0;
    for(int indice = 0; indice < 256; indice++){
        tab[indice]=((occurences_de_couleurs_gris[indice]/nTaille)+temp);
        temp = ((occurences_de_couleurs_gris[indice]/nTaille)+temp);
    }

    for(int i = 0; i < nH; i++){
        for(int j = 0; j < nW; j++){ 
            ImgOut[i*nW+j]=floor(tab[ImgIn[i*nW+j]]*255);
        }
    }    

    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn), free(ImgOut);
    return 1;

}