# ifndef MatrixToolBox_h_
# define MatrixToolBox_h_
#include "myBmpGris.h"


/** Fonction qui creer une matrice
    *@param Z différents valeurs
    *@param dimX lignes par valeur
    *@param dimY colonnes par valeur
*/
float*** creerMatrice(int Z, int dimX, int dimY);

/** Fonction qui creer une matrice de 2 images
    *@param img1 image 1
    *@param img2 image 2
    *@return une matrice contenant les pixels des images img1 et img2
*/
float*** creerImage(BmpImg img1, BmpImg img2);

/** Methode de creation d'une matrice des flottans
  * @param rows nombre de lignes de la matrice
  * @param cols nombre de colonnes de la matrice
  * @return une matrice de taille rows*cols prete a l'emploi
  */
float** CreateTable(int dimX,int  dimY);

/** Procedure qui afficher les matrices voulues
    *@param M un tableau de matrices
    *@param img une image bmp
    *@param Z un entier pour afficher une certaine matrice : 1 affichage de Ix, Iy, It, 2 affichage de U et V, 3 affichage de Umoy et Vmoy,
            4 affichage du sous_echanti des matrices IX et IY, 5 affichage du sur_echanti des matrices IX et IY
*/
void afficherMax(float*** M, BmpImg img, int Z);

/** Methode de Produit des matrices terme par terme
  * @param matrice terme1
  * @param matrice terme2
  * @param dimX nombre de lignes de matrice terme 1( resp terme 2)
  * @param dimY nombre de colonnes de matrice terme 1( resp terme 2)
  * @return Matrice de taille dimX*dimY
  */
float** ProduitMatTermeParTerme(float** terme1,float** terme2,int dimX,int dimY);


 /** Methode de destruction d'une image
  * @param matrice  tableau de matrices à detruire / desallouer
  * @param DimZ dimension suivant l'axe des Z (nombre de matrices dans notre tableau)
  * @param DimX dimension suivant l'axe des Y
  */
void FreeMATX(float*** matrices,int DimZ, int DimX);



# endif
