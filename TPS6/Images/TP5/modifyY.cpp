#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char  cNomImgY[250], cNomImgLue[250];
  int nH, nW, nTaille, k;

  if (argc != 4) 
     {
       printf("Usage: ImageIn.pgm ImageY.pgm k:(-128<k<128)\n"); 
       exit (1) ;
     }
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgY);
   sscanf (argv[3],"%i",&k);

   OCTET *ImgIn, *ImgY;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  int nTaille3=3*nTaille;

   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgY, OCTET, nTaille3);


   for (int i=0; i < nH; i++){
       for(int j =0;j <nW; j++){
        if((ImgIn[i*nW+j]+k)>255) ImgY[i*nW+j]=255;
        else if((ImgIn[i*nW+j]+k)<0)ImgY[i*nW+j]=0;
        else ImgY[i*nW+j]= ImgIn[i*nW+j] + k;
        }
   }

   ecrire_image_pgm(cNomImgY, ImgY,  nH, nW);     
   free(ImgIn); free(ImgY);

 return 1;
}
