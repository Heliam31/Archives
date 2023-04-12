#include <stdio.h>
#include "image_ppm.h"

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

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);

   for (int i=1; i < nH; i++){
     for (int j=1; j < nW; j++)
       {
	 int temp = 255;

	for(int i2 = i-1; i2<=i+1; i2++){
	   for (int j2 = j-1; j2<=j+1; j2++){
		if(ImgIn[i2*nW+j2] < temp) temp = ImgIn[i2*nW+j2];
		}
	 }
	 ImgOut[i*nW+j] = temp;
	}
    }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

 return 1;
}
