#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, SB, SH;
  
  if (argc != 5) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm Seuil \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%d",&SB);
     sscanf (argv[4],"%d",&SH);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
	


 for (int i=1; i < nH-1; i++){
   for (int j=1; j < nW-1; j++)
     {
      

       if ( ImgIn[i*nW+j] <= SB) ImgOut[i*nW+j]=0; 
       else if(ImgIn[i*nW+j]>=SH) ImgOut[i*nW+j]=255;
       
   }
 }

 for (int i=1; i < nH-1; i++){
   for (int j=1; j < nW-1; j++)
     {
      int vois = 0;
        for(int x = i-1; x<=i+1; x++){
          for (int y = j-1; y <= j+1; y++)
          {
            if(ImgIn[x*nW+y]==255) vois++;
          }
        }
        if(ImgIn[i*nW+j]>SB && ImgIn[i*nW+j]<SH) {
        if(vois>=1) ImgOut[i*nW+j] = 255;
        else ImgOut[i*nW+j]=0;
     }
   }
 }




   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}