#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgSeuil[250],cNomImgDill[250] , cNomImgEcrite[250];
  int nH, nW, nTaille;

  if (argc != 4) 
     {
       printf("Usage: ImageSeuil.pgm ImageDill.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }

   sscanf (argv[1],"%s",cNomImgSeuil) ;
   sscanf (argv[2],"%s",cNomImgDill) ;
   sscanf (argv[3],"%s",cNomImgEcrite);

   OCTET *ImgSeuil, *ImgDill, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgSeuil, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgSeuil, OCTET, nTaille);
   lire_image_pgm(cNomImgSeuil, ImgSeuil, nH * nW);
   allocation_tableau(ImgDill, OCTET, nTaille);
   allocation_tableau(ImgOut, OCTET, nTaille);

   for (int i=0; i < nH; i++){
     for (int j=0; j < nW; j++)
       {
	if (ImgSeuil[i*nW+j]<130 && ImgDill[i*nW+j] <130 ){ ImgOut[i*nW+j] = 255;}
	else if (ImgSeuil[i*nW+j]>130 && ImgDill[i*nW+j] >130) {ImgOut[i*nW+j] = 255;}
	else {ImgOut[i*nW+j] = 0;}

	 }
	}
    

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgSeuil); free(ImgDill); free(ImgOut);

 return 1;
}
