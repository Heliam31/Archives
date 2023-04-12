#include <stdio.h>
#include "image_ppm.h"
#include <math.h>
int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;

  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }

   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut, *ContourVert, *ContourHor;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille);
  allocation_tableau(ContourVert, OCTET, nTaille);
  allocation_tableau(ContourHor, OCTET, nTaille);

   for (int i=0; i < nH; i++){
     for (int j=0; j < nW; j++)
       {
        if(i==0||j==0||i==(nH-1)||j==(nW-1)){
        ContourHor[i*nW+j]=ImgIn[i*nW+j];
        ContourVert[i*nW+j]=ImgIn[i*nW+j];
        }
        else{
        ContourHor[i*nW+j]=abs(ImgIn[i*nW+(j+1)]-ImgIn[i*nW+j]);
        ContourVert[i*nW+j]=abs(ImgIn[(i+1)*nW+j]-ImgIn[i*nW+j]);
      }
        }
      }

    for (int i=0; i < nH; i++){
      for (int j=0; j < nW; j++)
       {
        ImgOut[i*nW+j]= ((ContourHor[i*nW+j])^2+(ContourVert[i*nW+j])^2)^(1/2);
       }
     }

  ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
  free(ImgIn); free(ImgOut), free(ContourVert), free(ContourHor);

 return 1;
}
