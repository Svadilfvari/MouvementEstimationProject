#include "Estimation.h"



float*** gradient(float*** images,BmpImg bmpImg)
{
    int dimX= bmpImg.dimX/2,dimY= bmpImg.dimY/2;
    float*** i_derive = creerMatrice(3, dimX+1,dimY+1);
    int i,j;
    for(i = 1; i <=dimX-2; i++)
    {
        for(j = 1; j <= dimY-2; j++)
        {
            if(j==1) i_derive[0][i][j]=images[0][i][1]-images[0][i][0];
            else if(j==dimY-2) i_derive[0][i][j]=images[0][i][dimY-1]-images[0][i][dimY-2];
            else i_derive[0][i][j]=0.5*(images[0][i][j+1]-images[0][i][j-1]);

            if(i==1) i_derive[1][i][j]=images[0][1][j]-images[0][0][j];
            else if(j==dimY-2) i_derive[1][i][j]=images[0][dimX-1][j]-images[0][dimX-2][j];
            else
            {
                i_derive[1][i][j]=0.5*(images[0][i+1][j]-images[0][i-1][j]);
            }
            i_derive[2][i][j]= images[1][i][j]-images[0][i][j];
        }
    }
    return i_derive;
}

/** Fonction calcul les dérivées partielles des intensités de tous les pixel
    *@param une image bmp BmpImg
    *@param une image bmp BmpImg (image déplacée)
    *@return un tableau de matrice de nombre réel
*/

float*** calcul_intensite(float*** images, BmpImg img)
{
    //Initialisation des variables utilisées dans la fonction
    int i,j;
    // Initialisation des dimensions de l'image
    int dimX = img.dimX, dimY = img.dimY;
    // tableau de matrice de dérivé, chaque case du tableau est une matrice donc chaque représente les dérivées de chaque
    float*** i_derive = creerMatrice(3, dimX, dimY);

    for (i = 0; i < dimX ; i ++ )
    {
        for (j = 0; j < dimY ; j ++)
        {
            // t : Imag
            // t+1 : CopyImag ie Image après déplacement
            // Calcul de It
            i_derive[2][i][j] = images[1][i][j] - images[0][i][j] ;
            // Calcul de Ix : i_derive[0][i][j]
            if(j==0)
            {
                i_derive[0][i][j] = (0*images[0][i][j] - 8*images[0][i][j+1] + images[0][i][j+2]) / 12. ;
            }
            if(j==1)
            {
                i_derive[0][i][j] = (8*images[0][i][j-1] + 0*images[0][i][j] - 8*images[0][i][j+1] + images[0][i][j+2]) / 12. ;
            }
            if(j>=2 && j<dimY-2)
            {
                i_derive[0][i][j] = (-1*images[0][i][j-2] + 8*images[0][i][j-1] + 0*images[0][i][j] - 8*images[0][i][j+1] + images[0][i][j+2]) / 12. ;
            }
            if(j==dimY-2)
            {
                i_derive[0][i][j] = (-1*images[0][i][j-2] + 8*images[0][i][j-1] + 0*images[0][i][j] - 8*images[0][i][j+1]) / 12. ;
            }
            if(j==dimY-1)
            {
                i_derive[0][i][j] = (-1*images[0][i][j-2] + 8*images[0][i][j-1] + 0*images[0][i][j]) / 12. ;
            }
            // Calcul de Iy : i_derive[1][i][j]
            if(i==0)
            {
                i_derive[1][i][j] = (0*images[0][i][j] - 8*images[0][i+1][j] + images[0][i+2][j]  ) / 12. ;
            }
            if(i==1)
            {
                i_derive[1][i][j] = (8*images[0][i-1][j] + 0*images[0][i][j] - 8*images[0][i+1][j] + images[0][i+2][j]  ) / 12. ;
            }
            if(2<=i && i<dimX-2)
            {
                i_derive[1][i][j] = (-1*images[0][i-2][j] + 8*images[0][i-1][j] + 0*images[0][i][j] - 8*images[0][i+1][j] + images[0][i+2][j]) / 12. ;
            }
            if(i == dimX-2)
            {
                i_derive[1][i][j] = (-1*images[0][i-2][j] + 8*images[0][i-1][j] + 0*images[0][i][j] - 8*images[0][i+1][j] ) / 12. ;
            }
            if(i == dimX-1)
            {
                i_derive[1][i][j] = (-1*images[0][i-2][j] + 8*images[0][i-1][j] + 0*images[0][i][j] ) / 12. ;
            }

        }
    }
    return i_derive;
}

/** Fonction qui calcul les derivees partielles des intensités (Ix, Iy, It) d'une image échantillionnee
    *@param echant un tableau de matrices contenant notre image echantillionnee
    *@param img une image
    *@return un tableau de deux matrices de nombre réel
*/

float*** calcul_intensite_echant(float*** echant,BmpImg img)
{
    //Initialisation des variables utilisées dans la fonction
    int i,j;
    int dimX = img.dimX/2, dimY = img.dimY/2;
// tableau de matrice de dérivé, chaque case du tableau est une matrice donc chaque représente les dérivées de chaque
    float*** i_derive = creerMatrice(3, dimX, dimY);

    //Tableau de matrices qui contient les images echantillonées
    // La première case(0) contient la matrice de la première image et la seconde case (1) celle de la deuxième image
    float*** minisation = creerMatrice(2, dimX, dimY);

    minisation=echant;

    for (i = 0; i < dimX ; i ++ )
    {
        for (j = 0; j < dimY ; j ++)
        {
            // t : Imag
            // t+1 : CopyImag ie Image après déplacement

            // Calcul de Ix
            if(j==0)
            {
                i_derive[0][i][j] = (0*minisation[0][i][j] - 8*minisation[0][i][j+1] + minisation[0][i][j+2]) / 12 ;
            }
            if(j==1)
            {
                i_derive[0][i][j] = (8*minisation[0][i][j-1] + 0*minisation[0][i][j] - 8*minisation[0][i][j+1] + minisation[0][i][j+2]) / 12 ;
            }
            if(j>=2 && j<dimY-2)
            {
                i_derive[0][i][j] = (-1*minisation[0][i][j-2] + 8*minisation[0][i][j-1] + 0*minisation[0][i][j] - 8*minisation[0][i][j+1] + minisation[0][i][j+2]) / 12 ;
            }
            if(j==dimY-2)
            {
                i_derive[0][i][j] = (-1*minisation[0][i][j-2] + 8*minisation[0][i][j-1] + 0*minisation[0][i][j] - 8*minisation[0][i][j+1]) / 12 ;
            }
            if(j==dimY-1)
            {
                i_derive[0][i][j] = (-1*minisation[0][i][j-2] + 8*minisation[0][i][j-1] + 0*minisation[0][i][j]) / 12 ;
            }
            // Calcul de Iy
            if(i==0)
            {
                i_derive[1][i][j] = (0*(minisation[0][i][j]) - 8*(minisation[0][i+1][j]) + minisation[0][i+2][j] ) / 12 ;
            }
            if(i==1)
            {
                i_derive[1][i][j] = (8*(minisation[0][i-1][j]) + 0*(minisation[0][i][j]) - 8*(minisation[0][i+1][j]) + minisation[0][i+2][j]  ) / 12 ;
            }
            if(i>=2 && i<dimX-2)
            {
                i_derive[1][i][j] = (-1*(minisation[0][i-2][j]) + 8*(minisation[0][i-1][j]) + 0*(minisation[0][i][j]) - 8*(minisation[0][i+1][j]) + minisation[0][i+2][j]) / 12 ;
            }
            if(i== dimX-2)
            {
                i_derive[1][i][j] = (-1*(minisation[0][i-2][j]) + 8*(minisation[0][i-1][j]) + 0*(minisation[0][i][j]) - 8*(minisation[0][i+1][j]) ) / 12 ;
            }
            if(i == dimX-1)
            {
                i_derive[1][i][j] = (-1*(minisation[0][i-2][j]) + 8*(minisation[0][i-1][j]) + 0*(minisation[0][i][j]) ) / 12 ;
            }
            // Calcul de It
            i_derive[2][i][j] = minisation[1][i][j] - minisation[0][i][j] ;
        }
    }
    return i_derive;
}

/** Fonction qui calcul les  vecteurs vitesses u = dx/dt et v=dy/dt
    *@param un tableau de matrice de nombre réel, les matrices contiennent les valeurs des dérivées pour chaque pixel
    *@param un tableau de matrice de nombre réel, les matrices continnent les valeurs des moyennes
    *@param un réel qui représente le poids de douceur (alpha, cf. Document descriptif équation (10)
    *@param une image
    *@return un tableau de deux matrices de nombre réel
*/

float*** calcul_vitesse(float*** i_derive, float*** Moyenne, float alpha,BmpImg img)
{
    //Initialisation des variables utilisées dans la fonction
    int i,j;
    // tableau de matrice de dérivé, chaque case du tableau est une matrice donc chaque représente les dérivées de chaque
    float*** vect_u_v = creerMatrice(2, img.dimX, img.dimY);

    for(i=0; i<img.dimX; i++)
    {
        for(j=0; j<img.dimY; j++)
        {
            // calcul de Uk+1
            vect_u_v [0][i][j] = Moyenne[0][i][j] - ((i_derive[0][i][j] * (i_derive[0][i][j]*Moyenne[0][i][j] + i_derive[1][i][j]*Moyenne[1][i][j] + i_derive[2][i][j])) / ( alpha*alpha + i_derive[0][i][j]*i_derive[0][i][j] + i_derive[1][i][j]*i_derive[1][i][j] )) ;
            // calcul de Vk+1
            vect_u_v [1][i][j] = Moyenne[1][i][j] - ((i_derive[1][i][j] * (i_derive[0][i][j]*Moyenne[0][i][j] + i_derive[1][i][j]*Moyenne[1][i][j] + i_derive[2][i][j])) / ( alpha*alpha + i_derive[0][i][j]*i_derive[0][i][j] + i_derive[1][i][j]*i_derive[1][i][j]  )) ;
        }
    }
    return vect_u_v;
}

/** Fonction qui calcul les  vecteurs vitesses u = dx/dt et v=dy/dt pour une image qui a subi un echantillonnage
    *@param un tableau de matrice de nombre réel, les matrices contiennent les valeurs des dérivées pour chaque pixel
    *@param un tableau de matrice de nombre réel, les matrices continnent les valeurs des moyennes
    *@param un réel qui représente le poids de douceur (alpha, cf. Document descriptif équation (10)
    *@param une image
    *@return un tableau de deux matrices de nombre réel
*/

float*** calcul_vitesse_echant(float*** i_derive, float*** Moyenne, float alpha,BmpImg img)
{
    //Initialisation des variables utilisées dans la fonction
    int i,j;
    int dimX = img.dimX/2, dimY = img.dimY/2;
    // tableau de matrice de dérivé, chaque case du tableau est une matrice donc chaque représente les dérivées de chaque
    float*** vect_u_v = creerMatrice(2, dimX, dimY);

    for(i=0; i<dimX; i++)
    {
        for(j=0; j<dimY; j++)
        {
            // calcul de Uk+1
            vect_u_v [0][i][j] = Moyenne[0][i][j] - ((i_derive[0][i][j] * (i_derive[0][i][j]*Moyenne[0][i][j] + i_derive[1][i][j]*Moyenne[1][i][j] + i_derive[2][i][j])) / ( alpha*alpha + i_derive[0][i][j]*i_derive[0][i][j] + i_derive[1][i][j]*i_derive[1][i][j] )) ;
            // calcul de Vk+1
            vect_u_v [1][i][j] = Moyenne[1][i][j] - ((i_derive[1][i][j] * (i_derive[0][i][j]*Moyenne[0][i][j] + i_derive[1][i][j]*Moyenne[1][i][j] + i_derive[2][i][j])) / ( alpha*alpha + i_derive[0][i][j]*i_derive[0][i][j] + i_derive[1][i][j]*i_derive[1][i][j]  )) ;
        }
    }
    return vect_u_v;
}

/**Fonction qui calcul les moyennes des vecteurs u et v
  *@param un tableau de matrices contenant les valeurs des vecteurs des vitesses
  *@param une image bmp
  *@return un tableau de matrices contenant les valeurs des moyennes

*/

float*** calcul_moyenne_vitesse(float*** vect_u_v,BmpImg img)
{
    int i,j;
    int dimX=img.dimX;
    int dimY=img.dimY;
// tableau de matrice de moyenne de vecteurs vitesse, chaque case du tableau est une matrice donc chaque représente les moyennes de chaque vitesse
// la case 0 du tableau contient la matrice du vecteur vitesse U (horizontal), la case 1 du tableau contient la matrice du vecteur vitesse V (Vertical)
    float*** vect_moyenne = creerMatrice(2, dimX, dimY);

// Boucle for afin de calculer la moyenne de tous les vecteurs vitesse liés à un pixel
// Les if gérent les exceptions (bord à droite ou à gauche et les 4 coins de l'image)
    for(i=0; i<dimX; i++)
    {
        for(j=0; j<dimY; j++)
        {
            if(i==0)
            {
                if(j==0)
                {
                    vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i][j+1] + vect_u_v [0][i+1][j+1]+ vect_u_v [0][i+1][j])/ 4 ;
                    vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i][j+1] + vect_u_v [1][i+1][j+1]+ vect_u_v [1][i+1][j])/ 4 ;
                }
                else if(0<j && j<dimY-1)
                {
                    vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i][j+1] + vect_u_v [0][i+1][j+1]+ vect_u_v [0][i+1][j]+vect_u_v [0][i+1][j-1]+vect_u_v [0][i][j-1])/ 6 ;
                    vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i][j+1] + vect_u_v [1][i+1][j+1]+ vect_u_v [1][i+1][j]+vect_u_v [1][i+1][j-1]+vect_u_v [1][i][j-1])/ 6 ;
                }
                else
                {
                    vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i+1][j] + vect_u_v [0][i+1][j-1]+ vect_u_v [0][i][j-1])/ 4 ;
                    vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i+1][j] + vect_u_v [1][i+1][j-1]+ vect_u_v [1][i][j-1])/ 4 ;
                }
            }
            else if(i==dimX-1)
            {
                if(j==0)
                {
                    vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i][j+1] + vect_u_v [0][i-1][j+1]+ vect_u_v [0][i-1][j])/ 4 ;
                    vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i][j+1] + vect_u_v [1][i-1][j+1]+ vect_u_v [1][i-1][j])/ 4 ;
                }
                else if(0<j && j<dimY-1)
                {
                    vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i][j+1] + vect_u_v [0][i-1][j+1]+ vect_u_v [0][i-1][j]+vect_u_v [0][i-1][j-1]+vect_u_v [0][i][j-1])/ 6 ;
                    vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i][j+1] + vect_u_v [1][i-1][j+1]+ vect_u_v [1][i-1][j]+vect_u_v [1][i-1][j-1]+vect_u_v [1][i][j-1])/ 6 ;
                }
                else
                {
                    vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i-1][j] + vect_u_v [0][i-1][j-1]+ vect_u_v [0][i][j-1])/ 4 ;
                    vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i-1][j] + vect_u_v [1][i-1][j-1]+ vect_u_v [1][i][j-1])/ 4 ;
                }
            }
            else if(j==0)
            {
                vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i-1][j] + vect_u_v [0][i-1][j+1]+ vect_u_v [0][i][j+1]+vect_u_v [0][i+1][j]+vect_u_v [0][i+1][j+1])/ 6 ;
                vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i-1][j] + vect_u_v [1][i-1][j+1]+ vect_u_v [1][i][j+1]+vect_u_v [1][i+1][j]+vect_u_v [1][i+1][j+1])/ 6 ;
            }
            else if(j==dimY-1)
            {
                vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i-1][j] + vect_u_v [0][i-1][j-1]+ vect_u_v [0][i][j-1]+vect_u_v [0][i+1][j-1]+vect_u_v [0][i+1][j])/ 6 ;
                vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i-1][j] + vect_u_v [1][i-1][j-1]+ vect_u_v [1][i][j-1]+vect_u_v [1][i+1][j-1]+vect_u_v [1][i+1][j])/ 6 ;
            }
            else
            {
                vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i-1][j-1] + vect_u_v [0][i-1][j]+ vect_u_v [0][i-1][j+1]+vect_u_v [0][i][j+1]+vect_u_v [0][i+1][j+1]+vect_u_v [0][i+1][j]+vect_u_v [0][i+1][j-1]+vect_u_v [0][i][j-1])/ 9 ;
                vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i-1][j-1] + vect_u_v [1][i-1][j]+ vect_u_v [1][i-1][j+1]+vect_u_v [1][i][j+1]+vect_u_v [1][i+1][j+1]+vect_u_v [1][i+1][j]+vect_u_v [1][i+1][j-1]+vect_u_v [1][i][j-1])/ 9 ;
            }
        }
    }
    return vect_moyenne;
}

/**Fonction qui calcul les moyennes des vecteurs u et v pour une image qui a subi un echantillonnage
  *@param vect_u_v un tableau de matrices contenant les valeurs des vecteurs des vitesses
  *@param img une image bmp

  *@return un tableau de matrices contenant les valeurs des moyennes
*/

float*** calcul_moyenne_vitesse_echant(float*** vect_u_v,BmpImg img)
{
    int i,j;
    int dimX=img.dimX/2;
    int dimY=img.dimY/2;
// tableau de matrice de moyenne de vecteurs vitesse, chaque case du tableau est une matrice donc chaque représente les moyennes de chaque vitesse
// la case 0 du tableau contient la matrice du vecteur vitesse U (horizontal), la case 1 du tableau contient la matrice du vecteur vitesse V (Vertical)
    float*** vect_moyenne = creerMatrice(2, dimX, dimY);

// Boucle for afin de calculer la moyenne de tous les vecteurs vitesse liés à un pixel
// Les if gérent les exceptions (bord à droite ou à gauche et les 4 coins de l'image)
//    printf("precheck");
    for(i=0; i<dimX; i++)
    {
        for(j=0; j<dimY; j++)
        {
            if(i==0)
            {
                if(j==0)
                {
                    vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i][j+1] + vect_u_v [0][i+1][j+1]+ vect_u_v [0][i+1][j])/ 4 ;
                    vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i][j+1] + vect_u_v [1][i+1][j+1]+ vect_u_v [1][i+1][j])/ 4 ;
                }
                else if(0<j && j<dimY-1)
                {
                    vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i][j+1] + vect_u_v [0][i+1][j+1]+ vect_u_v [0][i+1][j]+vect_u_v [0][i+1][j-1]+vect_u_v [0][i][j-1])/ 6 ;
                    vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i][j+1] + vect_u_v [1][i+1][j+1]+ vect_u_v [1][i+1][j]+vect_u_v [1][i+1][j-1]+vect_u_v [1][i][j-1])/ 6 ;
                }
                else
                {
                    vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i+1][j] + vect_u_v [0][i+1][j-1]+ vect_u_v [0][i][j-1])/ 4 ;
                    vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i+1][j] + vect_u_v [1][i+1][j-1]+ vect_u_v [1][i][j-1])/ 4 ;
                }
            }
            else if(i==dimX-1)
            {
                if(j==0)
                {
                    vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i][j+1] + vect_u_v [0][i-1][j+1]+ vect_u_v [0][i-1][j])/ 4 ;
                    vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i][j+1] + vect_u_v [1][i-1][j+1]+ vect_u_v [1][i-1][j])/ 4 ;
                }
                else if(0<j && j<dimY-1)
                {
                    vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i][j+1] + vect_u_v [0][i-1][j+1]+ vect_u_v [0][i-1][j]+vect_u_v [0][i-1][j-1]+vect_u_v [0][i][j-1])/ 6 ;
                    vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i][j+1] + vect_u_v [1][i-1][j+1]+ vect_u_v [1][i-1][j]+vect_u_v [1][i-1][j-1]+vect_u_v [1][i][j-1])/ 6 ;
                }
                else
                {
                    vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i-1][j] + vect_u_v [0][i-1][j-1]+ vect_u_v [0][i][j-1])/ 4 ;
                    vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i-1][j] + vect_u_v [1][i-1][j-1]+ vect_u_v [1][i][j-1])/ 4 ;
                }
            }
            else if(j==0)
            {
                vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i-1][j] + vect_u_v [0][i-1][j+1]+ vect_u_v [0][i][j+1]+vect_u_v [0][i+1][j]+vect_u_v [0][i+1][j+1])/ 6 ;
                vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i-1][j] + vect_u_v [1][i-1][j+1]+ vect_u_v [1][i][j+1]+vect_u_v [1][i+1][j]+vect_u_v [1][i+1][j+1])/ 6 ;
            }
            else if(j==dimY-1)
            {
                vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i-1][j] + vect_u_v [0][i-1][j-1]+ vect_u_v [0][i][j-1]+vect_u_v [0][i+1][j-1]+vect_u_v [0][i+1][j])/ 6 ;
                vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i-1][j] + vect_u_v [1][i-1][j-1]+ vect_u_v [1][i][j-1]+vect_u_v [1][i+1][j-1]+vect_u_v [1][i+1][j])/ 6 ;
            }
            else
            {
                vect_moyenne[0][i][j] = (vect_u_v [0][i][j]+vect_u_v [0][i-1][j-1] + vect_u_v [0][i-1][j]+ vect_u_v [0][i-1][j+1]+vect_u_v [0][i][j+1]+vect_u_v [0][i+1][j+1]+vect_u_v [0][i+1][j]+vect_u_v [0][i+1][j-1]+vect_u_v [0][i][j-1])/ 9 ;
                vect_moyenne[1][i][j] = (vect_u_v [1][i][j]+vect_u_v [1][i-1][j-1] + vect_u_v [1][i-1][j]+ vect_u_v [1][i-1][j+1]+vect_u_v [1][i][j+1]+vect_u_v [1][i+1][j+1]+vect_u_v [1][i+1][j]+vect_u_v [1][i+1][j-1]+vect_u_v [1][i][j-1])/ 9 ;
            }
        }
    }
    return vect_moyenne;
}

/**Fonction qui retourne un tableau de matrices sous_echantillonnées
  *@param u_v un tableau de matrices
  *@param img une image bmpImge
  *@return un tableau de matrices sous écchantillonées
*/

float*** sous_echan(float*** u_v, BmpImg img)
{
    int i,j;
    int dimX = img.dimX/2, dimY = img.dimY/2;
    float*** minimisation = creerMatrice(2, dimX, dimY);

    for(i=0; i<dimX; i++)
    {
        for(j=0; j<dimY; j++)
        {
            minimisation[0][i][j] = u_v[0][i*2][j*2];
            minimisation[1][i][j] = u_v[1][i*2][j*2];
        }
    }
    return minimisation;
}

/**Fonction qui retourne un tableau de matrices sur_echantillonnées
  *@param u_v un tableau de matrices
  *@param img une image bmpImge
  *@return un tableau de matrices sur écchantillonées
*/


float*** sur_echan(float*** sous_echan, BmpImg img)
{
    int i,j;
    int dimX = img.dimX/2;
    int tab_dimX = (dimX*2)-1;
    int dimY = img.dimY/2;
    int tab_dimY = (dimY*2)-1;

    float*** grandir = creerMatrice(2,tab_dimX,tab_dimY);

    for(i=0; i<tab_dimX; i=i+2)
    {
        for(j=0; j<tab_dimY; j=j+2)
        {
            grandir[0][i][j] = sous_echan[0][i/2][j/2];
            grandir[1][i][j] = sous_echan[1][i/2][j/2];
            if(i!=0)
            {
                grandir[0][(i)-1][j] = ( grandir[0][i][j] + grandir[0][i-2][j] ) / 2 ;
                grandir[1][(i)-1][j] = ( grandir[1][i][j] + grandir[1][i-2][j] ) / 2 ;
            }
            if(j!=0)
            {
                grandir[0][i][(j)-1] = ( grandir[0][i][j] + grandir[0][i][j-2] ) / 2 ;
                grandir[1][i][(j)-1] = ( grandir[1][i][j] + grandir[1][i][j-2] ) / 2 ;
            }
            if(i!=0 && j!=0){
                grandir[0][i-1][j-1] = ( grandir[0][i-1][j] + grandir[0][i-1][j-2] ) / 2 ;
                grandir[1][i-1][j-1] = ( grandir[1][i-1][j] + grandir[1][i-1][j-2] ) / 2 ;
            }
        }
    }
    return grandir;
}



