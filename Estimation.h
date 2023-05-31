#ifndef _Estimation_h_
#define _Estimation_h_


#include "MatrixToolBox.h"


float*** gradient(float*** images,BmpImg bmpImg);

/** Fonction calcul les dérivées partielles des intensités de tous les pixel
    *@param bmpImg une image bmp BmpImg
    *@param bmpImg_copy une image bmp BmpImg (image déplacée)
    *@return un tableau de matrice de nombre réel
*/

float*** calcul_intensite(float*** images, BmpImg img);

/** Fonction qui calcul les derivees partielles des intensités (Ix, Iy, It) d'une image échantillionnee
    *@param echant un tableau de matrices contenant notre image echantillionnee
    *@param img une image
    *@return un tableau de deux matrices de nombre réel
*/

float*** calcul_intensite_echant(float*** echant,BmpImg img );

/** Fonction qui calcul les  vecteurs vitesses u = dx/dt et v=dy/dt
    *@param i_derive un tableau de matrice de nombre réel, les matrices contiennent les valeurs des dérivées pour chaque pixel
    *@param Moyenne un tableau de matrice de nombre réel, les matrices continnent les valeurs des moyennes
    *@param alpha un réel qui représente le poids de douceur (alpha, cf. Document descriptif équation (10)
    *@param img une image
    *@return un tableau de deux matrices de nombre réel
*/

float*** calcul_vitesse(float*** i_derive, float*** Moyenne, float alpha,BmpImg img);

/** Fonction qui calcul les  vecteurs vitesses u = dx/dt et v=dy/dt pour une image qui a subi un echantillonnage
    *@param un tableau de matrice de nombre réel, les matrices contiennent les valeurs des dérivées pour chaque pixel
    *@param un tableau de matrice de nombre réel, les matrices continnent les valeurs des moyennes
    *@param un réel qui représente le poids de douceur (alpha, cf. Document descriptif équation (10)
    *@param une image
    *@return un tableau de deux matrices de nombre réel
*/

float*** calcul_vitesse_echant(float*** i_derive, float*** Moyenne, float alpha,BmpImg img);

/**Fonction qui calcul les moyennes des vecteurs u et v
  *@param vitesses un tableau de matrices contenant les valeurs des vecteurs des vitesses
  *@param img une image bmp
  *@return un tableau de matrices contenant les valeurs des moyennes
*/

float*** calcul_moyenne_vitesse(float*** vitesses,BmpImg img);

/**Fonction qui calcul les moyennes des vecteurs u et v pour une image qui a subi un echantillonnage
  *@param vect_u_v un tableau de matrices contenant les valeurs des vecteurs des vitesses
  *@param img une image bmp
  *@return un tableau de matrices contenant les valeurs des moyennes
*/

float*** calcul_moyenne_vitesse_echant(float*** vect_u_v,BmpImg img);


/**Fonction qui retourne un tableau de matrices sous_echantillonnées
  *@param u_v un tableau de matrices
  *@param img une image bmpImge
  *@return un tableau de matrices sous écchantillonées
*/

float*** sous_echan(float*** u_v, BmpImg img);

/**Fonction qui retourne un tableau de matrices sur_echantillonnées
  *@param u_v un tableau de matrices
  *@param img une image bmpImge
  *@return un tableau de matrices sur écchantillonées
*/

float*** sur_echan(float*** sous_echan, BmpImg img);


#endif



