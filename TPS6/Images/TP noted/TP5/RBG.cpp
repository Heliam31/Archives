#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char  cNomImgY[250], cNomImgCb[250], cNomImgCr[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nTaille3;

  if (argc != 5) 
     {
       printf("Usage: ImageY.pgm ImageCb.pgm ImageCr.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }

   sscanf (argv[1],"%s",cNomImgY);
    sscanf (argv[2],"%s",cNomImgCb);
    sscanf (argv[3],"%s",cNomImgCr);
   sscanf (argv[4],"%s",cNomImgEcrite) ;

   OCTET *ImgOut, *ImgY, *ImgCb, *ImgCr;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgY, &nH, &nW);
   nTaille = nH * nW;
   nTaille3 = nTaille*3;
  

   allocation_tableau(ImgY, OCTET, nTaille);
   lire_image_pgm(cNomImgY, ImgY, nH * nW);
   allocation_tableau(ImgCb, OCTET, nTaille);
      lire_image_pgm(cNomImgCb, ImgCb, nH * nW);
   allocation_tableau(ImgCr, OCTET, nTaille);
      lire_image_pgm(cNomImgCr, ImgCr, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

   for (int i=0; i < nTaille3; i+=3){
          ImgOut[i]= ImgY[i/3]+(1.402*(ImgCr[i/3]-128));
          ImgOut[i+1]= ImgY[i/3] + (1.772*(ImgCb[i/3]-128));
          ImgOut[i+2]= ImgY[i/3] - (0.34414 * (ImgCb[i/3]-128)) - (0.714414*(ImgCr[i/3]-128));
        }

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);      
   free(ImgOut); free(ImgY); free(ImgCb); free(ImgCr);

 return 1;
}
