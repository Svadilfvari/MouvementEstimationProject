#include"MatrixToolBox.h"
#include "Estimation.h"


/** Fonction qui creer une matrice
    *@param Z différents valeurs
    *@param dimX lignes par valeur
    *@param dimY colonnes par valeur
*/

float*** creerMatrice(int Z, int dimX, int dimY){

    float*** matrice = calloc(Z,sizeof(float**));
    for(int i=0; i<Z; i++)
    {
        matrice[i] = calloc(dimX,sizeof(float*));
        for(int j=0; j<dimX; j++)
        {
            matrice[i][j] = calloc(dimY,sizeof(float));
        }
    }

    return matrice;
}

/** Fonction qui creer une matrice de 2 images
    *@param img1 image 1
    *@param img2 image 2
    *@return une matrice contenant les pixels des images img1 et img2
*/

float*** creerImage(BmpImg img1, BmpImg img2){
    int z = 2;  // nombre d'image
    float *** images = creerMatrice(z,img1.dimX,img1.dimY);

    for(int i=0; i<img1.dimX; i++)
    {
        for(int j=0; j<img1.dimY; j++)
        {
            images [0][i][j]= getPixel(img1,i,j);
            images [1][i][j]= getPixel(img2,i,j);
        }
    }
    return images;
}

/** Methode de creation d'une matrice des flottans
  * @param rows nombre de lignes de la matrice
  * @param cols nombre de colonnes de la matrice
  * @return une matrice de taille rows*cols prete a l'emploi
  */

 float** CreateTable(int dimX,int  dimY)
{
    float ** matReel ;
    matReel = malloc ( dimX * sizeof ( float* ) );
    int i;
    for ( i = 0; i < dimX; i++ )
    {
        matReel [i] = calloc ( dimY, sizeof ( float ) );
    }
    return matReel;
}

/** Methode de Produit des matrices terme par terme
  * @param matrice terme1
  * @param matrice terme2
  * @param dimX nombre de lignes de matrice terme 1( resp terme 2)
  * @param dimY nombre de colonnes de matrice terme 1( resp terme 2)
  * @return Matrice de taille dimX*dimY
  */

float** ProduitMatTermeParTerme(float** terme1,float** terme2,int dimX,int dimY)
{
    int i,j;
    float**result=CreateTable(dimX,dimY);
    for(i=0;i<dimX;i++)
        for(j=0;j<dimY;j++)
            result[i][j]=terme1[i][j]*terme2[i][j];

    return result;
}

 /** Methode de destruction d'une image
  * @param matrice  tableau de matrices à detruire / desallouer
  * @param DimZ dimension suivant l'axe des Z (nombre de matrices dans notre tableau)
  * @param DimX dimension suivant l'axe des Y
  */

void FreeMATX(float*** matrices,int DimZ, int DimX)
{

    int z,i;
     for ( z = 0; z <DimZ ; z ++ )
    {
        for (i=0; i<DimX; i++)
        {

            free (matrices [z][i ] ) ;

        }
        free(matrices [z]);
    }
//  Liberation de l’espace memoire du tableau de matrices
    free ( matrices  );
//  Par securite, on fait pointer matrices  vers NULL
    matrices = NULL ;
}


