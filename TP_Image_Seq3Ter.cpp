// TP_Image.cpp : définit le point d'entrée pour l'application console.
//

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// Déclaration des variables de travail
unsigned char *pixelsArray;
short nbCols, nbRows;

#define TAILLEHISTO 256
unsigned int histogramme[TAILLEHISTO];

int main()
{
	/********************************************************************/
	/* PARTIE A NE PAS MODIFIER						*********************/
	/********************************************************************/	
	// Définition des variables spécifiques à Open CV
	Mat image;

	// Chargement de l'image
	image = imread("passerelle_NG.jpg", 0);
	
	if (image.data == NULL)
	{
		cerr << "Impossible d'ouvrir l'image ! ";
		return -1;
	}

	// Initialisation des variables de travail
	nbRows = image.rows;
	nbCols = image.cols;
	pixelsArray = &image.data[0];		// Adresse du 1er pixel de l'image en mémoire/ .data valeur du premier pixel 
		
	// Affichage de l'image
	namedWindow("TP Imagerie", WINDOW_AUTOSIZE);
	imshow("TP Imagerie", image);

	/*******************************************************************/
	/* PARTIE A COMPLETER				       *************/
	/* Nombre de pixels en largeur : variable nbCols       *************/
	/* Nombre de pixels en largeur : variable nbRows       *************/
	/* Tableau des pixels organisé ligne par ligne : pixelsArray       */
	/*******************************************************************/
	
	// Calcul de l'histogramme
	void calcHisto(void);
	void TriInserHisto(void);
	calcHisto();

	// Tri par insertion - A compléter
	TriInserHisto();

	waitKey(0);
	return 0;
}

// Définitions des fonctions
// Fonction Tri par insertion - A compléter
void TriInserHisto(void)
{
	int x = 0, j = 0;
	unsigned int histoTriInser[TAILLEHISTO];

	for (int i = 0; i < TAILLEHISTO; i++)
	{
		histoTriInser[i] = histogramme[i];
	}

	for (int i = 1; i < TAILLEHISTO; i++)
	{
		x = histoTriInser[i];
		j = i;

		while (j > 0 && histoTriInser[j - 1] > x)
		{
			histoTriInser[j] = histoTriInser[j - 1];
			j = j - 1;
		}

		histoTriInser[j] = x;
	}

	cout << "Valeurs de l'histogramme (TRI)" << endl;
	for (int i = 0; i < TAILLEHISTO; i++)
		cout << "histogramme(TRI)[" << i << "] : " << histoTriInser[i] << endl;

}



//Calcule et affiche le nombre de pixels pour un même NdG - histogramme 
void calcHisto(void)
{
	int i;

	cout << "Valeurs de l'histogramme" << endl;
	for (i = 0; i < (nbRows*nbCols); i++)
		histogramme[pixelsArray[i]]++;
	// Affichage
	for (i = 0; i < TAILLEHISTO; i++)
		cout << "histogramme[" << i << "] : " << histogramme[i] << endl;

	return;
}
