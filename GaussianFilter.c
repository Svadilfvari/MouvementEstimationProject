#include "GaussianFilter.h"



/** Methode de création de matrice de GAUSS
  * @param x Point 1
  * @param y Point 2
  * @return return une matrice 5x5 de GAUSS
  */
float** Filtre_Gausse_5_5()
{
    float** gauss=CreateTable(smooth_kernel_size,smooth_kernel_size);
    float sum = 0;
    float K = 1.0;
    int i,j;
    for (i = 0; i < smooth_kernel_size; i++) {
        for (j = 0; j < smooth_kernel_size; j++) {
            float x = i - (smooth_kernel_size - 1) / 2.0;
            float y = j - (smooth_kernel_size - 1) / 2.0;
            gauss[i][j] = K * exp(((pow(x, 2) + pow(y, 2)) / ((2 * pow(sigma, 2)))) * (-1));
            sum += gauss[i][j];
        }
    }
    for ( i = 0; i < smooth_kernel_size; i++) {
        for ( j = 0; j < smooth_kernel_size; j++) {
            gauss[i][j] /= sum;
        }
    }
    return gauss;

}

/** Methode de produit de convolution
  * @param mat matrice pour produit de convolution
  * @param img l'image bmp
  * @param K Filtre de GAUSS (kernel) 5*5
  * @return Produit de convolution [ mat conv Filtre de GAUSS ]
  */

float** produit_Conv(float** I, int dimX,int dimY,float** K)
{
    float** produit=CreateTable(dimX,dimY);
    int i,j;

    for(i=2; i<dimX-2; i++){
        for(j=2; j<dimY-2; j++){
            produit[i][j] = I[i-2][j-2]*K[0][0] + I[i-1][j-2]*K[1][0] + I[i][j-2]*K[2][0] + I[i+1][j-2]*K[3][0] + I[i+2][j-2]*K[4][0] +
                            I[i-2][j-1]*K[0][1] + I[i-1][j-1]*K[1][1] + I[i][j-1]*K[2][1] + I[i+1][j-1]*K[3][1] + I[i+2][j-1]*K[4][1] +
                            I[i-2][j]  *K[0][2] + I[i-1][j]  *K[1][2] + I[i][j]  *K[2][2] + I[i+1][j]  *K[3][2] + I[i+2][j]  *K[4][2] +
                            I[i-2][j+1]*K[0][3] + I[i-1][j+1]*K[1][3] + I[i][j+1]*K[2][3] + I[i+1][j+1]*K[3][3] + I[i+2][j+1]*K[4][3] +
                            I[i-2][j+2]*K[0][4] + I[i-1][j+2]*K[1][4] + I[i][j+2]*K[2][4] + I[i+1][j+2]*K[3][4] + I[i+2][j+2]*K[4][4] ;
        }
    }
    return produit;
}

/** Methode de calcul U et V
    *@param u_v tableau de matrices u et v
    *@param u_v tableau de matrices des moyennnes des matrices u et v
    *@param u_v tableau de matrices des derivees
    *@param lignes nombre de lignes
    *@param cols nombre de colonnes
*/
void CalcU_V_Conv(float*** u_v,float*** u_v_moyenne, float** W , float*** I_derive,int lignes,int cols)
{
    //recadrement de l'image
    if(lignes%2!=0)
        lignes--;
    if(cols%2!=0)
        cols--;

    float** XX=ProduitMatTermeParTerme(I_derive[0],I_derive[0],lignes,cols);
    float** YY=ProduitMatTermeParTerme(I_derive[1],I_derive[1],lignes,cols);
    float** XY=ProduitMatTermeParTerme(I_derive[0],I_derive[1],lignes,cols);
    float** XT=ProduitMatTermeParTerme(I_derive[0],I_derive[2],lignes,cols);
    float** YT=ProduitMatTermeParTerme(I_derive[1],I_derive[2],lignes,cols);

    float** T1=produit_Conv(XX,lignes,cols,W);     // T1 = Covolution [ (Ix*Ix) , W ]
    float** T2=produit_Conv(YY,lignes,cols,W);     // T2 = Covolution [ (Iy*Iy) , W ]
    float** T3=produit_Conv(XY,lignes,cols,W);     // T3 = Covolution [ (Ix*Iy) , W ]
    float** T4=produit_Conv(XT,lignes,cols,W);     // T4 = Covolution [ (Ix*It) , W ]
    float** T5=produit_Conv(YT,lignes,cols,W);     // T5 = Covolution [ (Iy*It) , W ]

    int i,j;
    for(i=0;i<lignes;i++)
    {
        for(j=0;j<cols;j++)
        {
            // formule de U
            u_v[0][i][j]=u_v_moyenne[0][i][j]-( ( T4[i][j]+(T3[i][j]* u_v_moyenne[1][i][j])+(T1[i][j]* u_v_moyenne[0][i][j]) ) / ( alpha_u+T1[i][j]+T2[i][j] ) );
            // formule de V
            u_v[1][i][j]=u_v_moyenne[1][i][j]-( ( T5[i][j]+(T2[i][j]*u_v_moyenne[1][i][j])+(T3[i][j]*u_v_moyenne[0][i][j]) ) /( alpha_u+T1[i][j]+T2[i][j] ) );
        }
    }
}


