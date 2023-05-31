#include "Estimation.h"
#include "GaussianFilter.h"
#include <math.h>
#define FILE_smooth_NAME "file_lisse1.txt"
#define FILE_smooth_NAME2 "file_lisse2.txt"
#define FILE_NAME "file1_echan.txt"
#define FILE_NAME2 "file2_echan.txt"

#define smooth_kernel_size 5
#define K  1.0

int main(){

    int i,j;
    /*******************************************************Lecture des images*******************************************************/
    printf("    /******************************************************* Greetings ************************************************/ \n\n ");

    printf("\t Project 'Motion Estimation Based on Horn-Schunk Optical Flow Algorithm' initiated \n\n");

    BmpImg img1 = readBmpImage("woman1.bmp");
    BmpImg img2 = readBmpImage("woman2.bmp");

    printf(" \n\n **Reading images %s and %s with dimensions %d (dimX) and %d (dimY) ... \n\n", img1.nomImg,img2.nomImg,img1.dimX,img1.dimY );

    /**********************************************************Création tableau de matrices des images*****************************************************/

    float *** images = creerImage(img1, img2);

    /**********************************************************SOUS-ECHANT des images *****************************************************/

     printf(" \n\n **Sampling images, proceeding  ... \n\n");

    float*** minimisation = sous_echan(images, img1);

    // dimension des images sous-échantillonnées
    int dimX1=img1.dimX/2, dimY1=img1.dimY/2;

    /**********************************************************Calcul des derivees*****************************************************/

    // CALCUL DES DERIVES AVEC UNE IMAGE ECHANTILLONEE
    printf(" \n\n  **The gradient estimation kernel of the BFB model uses 4-point central differences for differentiation defined as  :\n \t The convolution of the image with the mask [-1 8 0 -8 1]*1/12  , proceeding  ... \n\n");

    float*** i_derive_echan=calcul_intensite_echant(minimisation,img1);


    /**********************************************************Création des matrices moyennes et vitesses********************************/

    // création matrice : Moyenne de U et V nulles au départ Pour un calcul echantillone, NOTE : dimension d'allocation : dimX/2 et dimY/2 !
    float*** Moy_u_v_echan = creerMatrice(2,dimX1,dimY1);

    // création matrice :  U et V nulls au départ, Pour un calcul echantillonnage
    float*** u_v_echan= creerMatrice(2,img1.dimX/2,img1.dimY/2);

    //Adaptation des dimensions
    // Lors du sous-echantilonnage nous perdons certaines lignes ou colonnes
    // Nous adaptons alors les dimensions des matrices u_v en créant la matrice dimX2 et dimY2
    int dimX2=(dimX1*2)-1;
    int dimY2=(dimY1*2)-1;
    // création matrice :  U et V nulls au départ, Pour un calcul avec echantillonnage
    float*** u_v_sur = creerMatrice(2,dimX2,dimY2);

    /*****************************************************ESTIMATION DU MOUVEMENT*********************************************************/

    printf(" \n\n **Estimation of the motion, proceeding  ... \n\n");

    // Minimisation avec 100 itérations
    i=0;
    while(i<100)
    {
        u_v_echan = calcul_vitesse_echant( i_derive_echan, Moy_u_v_echan, 0.3,img1);      // ALPHA = 0.3 doit être entre 0.1 et 0.5
        Moy_u_v_echan=calcul_moyenne_vitesse_echant(u_v_sur,img1);
        i++;
    }
    // sur-echantillonnage des vecteurs vitesses u et v
    u_v_sur=sur_echan(u_v_echan,img1);     // ALPHA = 0.3 doit être entre 0.1 et 0.5

    /**********************************************************************FILTRE GAUSSIEN**************************************/

    float** gauss = Filtre_Gausse_5_5();

    // FILTRE_GAUSSIEN_SIGMA_0.8
    // application du filtre sur nos images

    printf("\n\n **Smoothing the images (I.e. Applying a Gaussian filter on our images) , proceeding  ... \n\n");

    float** image_1_lisse = produit_Conv(images[0],img1.dimX,img1.dimY,gauss);
    float** image_2_lisse = produit_Conv(images[1],img1.dimX,img1.dimY,gauss);



    /************************************************************************Calcul des vecteurs vitesses de l'image lissée***************/

    printf(" \n\n **Estimation of the motion (applied on a smoothed image) , proceeding  ... \n\n");

    float*** images_lisses = creerMatrice(2,img1.dimX,img1.dimY);

    images_lisses[0]=image_1_lisse;
    images_lisses[1]=image_2_lisse;

    float*** u_v_lisse= creerMatrice(2,img1.dimX/2,img1.dimY/2);
    float*** Moyenne_u_v_lisse= creerMatrice(2,img1.dimX/2,img1.dimY/2);

    // Echanitllonnage des images lissees
    float*** minimisation_lisse = sous_echan(images_lisses, img1);

    float*** i_derive_lisse=calcul_intensite_echant(minimisation_lisse,img1);

    // Minimisation avec 100 itérations
    i=0;
    while(i<100){
        CalcU_V_Conv(u_v_lisse,Moyenne_u_v_lisse,gauss,i_derive_lisse,img1.dimX/2,img1.dimY/2);
        Moyenne_u_v_lisse=calcul_moyenne_vitesse_echant(u_v_sur,img1);
        i++;
    }

    // sur-echantillonnage des vecteurs vitesses u et v
    float*** u_v_lisse_sur=sur_echan(u_v_lisse,img1);

    /*******************************************************************GESTION DES FICHIERS*************************************************/

        printf(" \n\n **Data inscription in text files, proceeding  ... \n\n");

    FILE *file = fopen(FILE_NAME, "w");
    FILE *file2 = fopen(FILE_NAME2, "w");


    FILE *file_smooth = fopen(FILE_smooth_NAME, "w");
    FILE *file_smooth2 = fopen(FILE_smooth_NAME2, "w");


    /****************************************************GESTION DES FICHIERS (ECHANTILLONNAGE)***************************************************/

    //symetrie echant

    for(i=0; i<dimX2; i++)
    {
        for(j=0; j<dimY2; j++)
        {
            fprintf(file,"%f\t",u_v_sur[1][dimX2-1-i][j]);
        }
        fprintf(file,"\n");
    }
    fprintf(file,"\n\n");


    //symetrie echant
    for(i=0; i<dimX2; i++)
    {
        for(j=0; j<dimY2; j++)
        {
            fprintf(file2,"%f\t",u_v_sur[0][dimX2-1-i][j]);
        }
        fprintf(file2,"\n");
    }
    fprintf(file2,"\n\n");


    /****************************************************GESTION DES FICHIERS (ECHANTILLONNAGE+ Smooth)***************************************************/

    //symetrie echant
    for(i=0; i<dimX2; i++)
    {
        for(j=0; j<dimY2; j++)
        {
            fprintf(file_smooth,"%f\t",u_v_lisse_sur[1][dimX2-1-i][j]);
        }
        fprintf(file_smooth,"\n");
    }
    fprintf(file_smooth,"\n\n");



    //symetrie echant
    for(i=0; i<dimX2; i++)
    {
        for(j=0; j<dimY2; j++)
        {
            fprintf(file_smooth2,"%f\t",u_v_lisse_sur[0][dimX2-1-i][j]);
        }
        fprintf(file_smooth2,"\n");
    }
    fprintf(file2,"\n\n");



    fclose(file2);
    fclose(file);

    printf("Data already written in text files, generated in the folder where this project is located. Gratitude for your patience. \n");
    printf("\t \t project 'Motion Estimation Based on Horn-Schunk Optical Flow Algorithm' finished proceeding \n");

    /***********************************************************LIBERATION DE MEMOIRE******************************************************************/


    FreeMATX(images,2,img1.dimX);
    FreeMATX(i_derive_echan,2,dimX1);

    FreeMATX(images_lisses,2,img1.dimX/2);
    FreeMATX(u_v_lisse,2,img1.dimX/2);
    FreeMATX(Moyenne_u_v_lisse,2,img1.dimX/2);

    FreeMATX(u_v_sur,2,dimX1);
    FreeMATX(Moy_u_v_echan,2,img1.dimX/2);


    return 0;
}
