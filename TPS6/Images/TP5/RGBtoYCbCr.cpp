#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char  cNomImgY[250], cNomImgCb[250], cNomImgCr[250], cNomImgLue[250];
  int nH, nW, nTaille, nTaille3;

  if (argc != 5) 
     {
       printf("Usage: ImageIn.pgm ImageY.pgm ImageCb.pgm ImageCr.pgm  \n"); 
       exit (1) ;
     }
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgY);
    sscanf (argv[3],"%s",cNomImgCb);
    sscanf (argv[4],"%s",cNomImgCr);


   OCTET *ImgIn, *ImgY, *ImgCb, *ImgCr;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   nTaille3 = nTaille*3;
  

   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgY, OCTET, nTaille3);
   allocation_tableau(ImgCb, OCTET, nTaille3);
   allocation_tableau(ImgCr, OCTET, nTaille3);


   for (int i=0; i < nTaille3; i+=3){
    ImgY[i/3]= (0.299*ImgIn[i])+(0.587*ImgIn[i+1])+(0.114*ImgIn[i+2]);
    ImgCb[i/3]= (-0.1687*ImgIn[i])-(0.3313*ImgIn[i+1])+(0.5*ImgIn[i+2])+128;
    ImgCr[i/3]= (0.5*ImgIn[i])-(0.4187*ImgIn[i+1])-(0.0813*ImgIn[i+2])+128;
   }

   ecrire_image_pgm(cNomImgY, ImgY,  nH, nW);     
   ecrire_image_pgm(cNomImgCb, ImgCb,  nH, nW); 
   ecrire_image_pgm(cNomImgCr, ImgCr,  nH, nW);  
   free(ImgIn); free(ImgY); free(ImgCb); free(ImgCr);

 return 1;
}
