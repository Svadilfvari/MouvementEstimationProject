# ifndef GaussianFilter_h_
# define GaussianFilter_h_
#include"MatrixToolBox.h"
#include <math.h>
#define pi 3.14159265358979323846
#define N_pyr 100
#define alpha_u 0.3
#define  filter_gauss_dim 3
#define sigma 0.8
#define smooth_kernel_size 5


/** Methode de création de matrice de GAUSS
  * @param x Point 1
  * @param y Point 2
  * @return return une matrice 5x5 de GAUSS
  */
float** Filtre_Gausse_5_5();

/** Methode de produit de convolution
  * @param mat matrice pour produit de convolution
  * @param dimX nombre de lignes de matrice mat
  * @param dimY nombre de colonnes de matrice mat
  * @param MatDeGauss Filtre de GAUSS 5*5
  * @return Produit de convolution [ mat '*' Filtre de GAUSS ]
  */
float** produit_Conv(float** I, int dimX,int dimY,float** K);



/** Methode de calcul U et V
    *@param u_v tableau de matrices u et v
    *@param u_v tableau de matrices des moyennnes des matrices u et v
    *@param u_v tableau de matrices des derivees
    *@param lignes nombre de lignes
    *@param cols nombre de colonnes
*/
void CalcU_V_Conv(float*** u_v,float*** u_v_moyenne, float** W , float*** I_derive,int dimX,int dimY);


# endif

