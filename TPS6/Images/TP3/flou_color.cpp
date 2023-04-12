#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;

  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm \n"); 
       exit (1) ;
     }

   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);

   for (int i=0; i < nH; i++){
     for (int j=0; j < nW; j++)
       {
          ImgOut[i*nW+j] = (ImgIn[i*nW+j] + ImgIn[(i-1)*nW+j] + ImgIn[(i+1)*nW+j] + ImgIn[i*nW+(j-1)] + ImgIn[i*nW+(j+1)]+ImgIn[(i-1)*nW+(j+1)]+ImgIn[(i+1)*nW+(j+1)]+ImgIn[(i-1)*nW+(j-1)]+ImgIn[(i+1)*nW+(j-1)])/9;
          if(i==0 || j==0 || i == nH-1 || j == nW-1 ){
            ImgOut[i*nW+j]=ImgIn[i*nW+j];
          }
       }
     }
   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);
 return 1;
}
