//#include "Estimation.h"
//#include "GaussianFilter.h"
//#include <math.h>
//#define FILE_NAME "file1.txt"
//#define FILE_NAME2 "file2.txt"
//#define smooth_kernel_size 5
//#define K  1.0
//
//int main(){
//
//    int i, j;
//    /*******************************************************Lecture des images*******************************************************/
//    printf("    /******************************************************* Greetings ************************************************/ \n\n ");
//
//    printf("\t Project 'Motion Estimation Based on Horn-Schunk Optical Flow Algorithm' initiated \n\n");
//
//    BmpImg img1 = readBmpImage("woman1.bmp");
//    BmpImg img2 = readBmpImage("woman2.bmp");
//
//    // Dimension des images
//    int dimX = img1.dimX, dimY = img1.dimY;
//
//    printf(" \n\n **Reading images %s and %s with dimensions %d (dimX) and %d (dimY) ... \n\n", img1.nomImg,img2.nomImg,img1.dimX,img1.dimY );
//
//    /**********************************************************Création tableau de matrices des images*****************************************************/
//
//    float *** images = creerImage(img1,img2);
//
//    /**********************************************************Calcul des derivees*****************************************************/
//
//    printf(" \n\n  **The gradient estimation kernel of the BFB model uses 4-point central differences for differentiation defined as  :\n \t The convolution of the image with the mask [-1 8 0 -8 1]*1/12  , proceeding  ... \n\n");
//    float*** i_derive=calcul_intensite(images,img1);
//
//    /**********************************************************Création des matrices moyennes et vitesses********************************/
//
//    // création matrice : Moyenne de U et V nulles au départ Pour un calcul non echantillone, NOTE : dimension d'allocation : dimX et dimY !
//    float*** Moy_u_v= creerMatrice(2,dimX,dimY);
//
//
//    // création matrice :  U et V nulls au départ, Pour un calcul sans echantillonnage
//    float*** u_v= creerMatrice(2,dimX,dimY);
//
//
//    /*****************************************************ESTIMATION DU MOUVEMENT*********************************************************/
//
//    printf(" \n\n **Estimation of the motion, proceeding  ... \n\n");
//
//    // Minimisation avec 100 itérations
//    i=0;
//    while(i<100){
//        u_v = calcul_vitesse(i_derive,Moy_u_v,0.3, img1);
//        Moy_u_v = calcul_moyenne_vitesse(u_v,img1);
//        i++;
//    }
//
//    /*******************************************************************GESTION DES FICHIERS*************************************************/
//
//    printf(" \n\n **Data inscription in text files, proceeding  ... \n\n");
//
//    FILE *file = fopen(FILE_NAME, "w");
//    FILE *file2 = fopen(FILE_NAME2, "w");
//
//    /****************************************************GESTION DES FICHIERS (NON-ECHANTILLONNAGE)***************************************************/
//
//    // enregistrement des valeurs de u
//    for(i=0; i<dimX; i++)
//    {
//        for(j=0; j<dimY; j++)
//        {
//            fprintf(file,"%f\t",u_v[0][dimX-1-i][j]);
//        }
//        fprintf(file,"\n");
//    }
//    fprintf(file,"\n\n");
//
//
//    // enregistrement des valeurs de v
//    for(i=0; i<dimX; i++)
//    {
//        for(j=0; j<dimY; j++)
//        {
//            fprintf(file2,"%f\t",u_v[1][dimX-1-i][j]);
//        }
//        fprintf(file2,"\n");
//    }
//    fprintf(file2,"\n\n");
//
//    /***********************************************************LIBERATION DE MEMOIRE******************************************************************/
//
//
//    FreeMATX(images,2,dimX);
//    FreeMATX(i_derive,3,dimX);
//    FreeMATX(u_v,2,dimX);
//    FreeMATX(Moy_u_v,2, dimX);
//
//    return 0;
//}
