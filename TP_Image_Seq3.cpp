// TP_Image.cpp�: d�finit le point d'entr�e pour l'application console.
//
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// D�claration des variables de travail
unsigned char *pixelsArray;
short nbCols, nbRows;

#define TAILLEHISTO 256
unsigned int histogramme[TAILLEHISTO];

int main()
{
	/********************************************************************/
	/* PARTIE A NE PAS MODIFIER						*********************/
	/********************************************************************/	
	// D�finition des variables sp�cifiques � Open CV
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
	pixelsArray = &image.data[0];		// Adresse du 1er pixel de l'image en m�moire/ .data valeur du premier pixel 
		
	// Affichage de l'image
	namedWindow("TP Imagerie", WINDOW_AUTOSIZE);
	imshow("TP Imagerie", image);

	/*******************************************************************/
	/* PARTIE A COMPLETER						           *************/
	/* Nombre de pixels en largeur : variable nbCols       *************/
	/* Nombre de pixels en largeur : variable nbRows       *************/
	/* Tableau des pixels organis� ligne par ligne : pixelsArray       */
	/*******************************************************************/
	
	// Calcul de l'histogramme
	void calcHisto(void);
	void TriBulleHisto(void);
	void TriInsertHisto();
	calcHisto();

	// Tri � bulles
	TriBulleHisto();

	// Tri par insertion
	TriInsertHisto();

	waitKey(0);
	return 0;
}

// D�finitions des fonctions
// Fonction Tri � bulles
void TriBulleHisto()
{
	int initPos = 0, memPos = 0, change = 0;
	unsigned int histoTriBulle[TAILLEHISTO];

	for (int i = 0; i < TAILLEHISTO; i++)
	{
		histoTriBulle[i] = histogramme[i];
	}


	do
	{
		int nbPixMIN = nbCols * nbRows;
		int i = initPos;
		do
		{
			if (histoTriBulle[i] < nbPixMIN)
			{
				nbPixMIN = histoTriBulle[i];
				memPos = i;
			}
			i++;
		} while (i < TAILLEHISTO);
		change = histoTriBulle[memPos];
		histoTriBulle[memPos] = histoTriBulle[initPos];
		histoTriBulle[initPos] = change;
		initPos++;
	} while (initPos < TAILLEHISTO);


	cout << "\nValeurs de l'histogramme Tri Bulle : " << endl;
	for (int i = 0; i < TAILLEHISTO; i++)
		cout << "histogramme[" << i << "] : " << histoTriBulle[i]<< endl;

}




// Fonction Tri par insertion
void TriInsertHisto()
{
	int X, j;
	unsigned int histoTriBulle[TAILLEHISTO];

	for (int i = 0; i < TAILLEHISTO; i++)
	{
		histoTriBulle[i] = histogramme[i];
	}


	for (int i = 0; i < 256; i++)
	{
		histoTriBulle[i] = histogramme[i];
	}

	for (int i = 1; i < 256 - 1; i++)
	{
		X = histoTriBulle[i];
		j = i;

		while (j > 0 || histoTriBulle[j - 1] > X)
		{
			histoTriBulle[j] = histoTriBulle[j - 1];
			j = j - 1;
		}

		histoTriBulle[j] = X;
	}

}



//Calcule et affiche le nombre de pixels pour un m�me NdG - histogramme 
void calcHisto(void)
{
	int i;

	cout << "Valeurs de l'histogramme" << endl;
	for (i = 0; i < (nbRows*nbCols); i++)
		histogramme[pixelsArray[i]]++;
	// Affichage
	for (i = 0; i < TAILLEHISTO; i++)
		cout << "histogramme[" << i << "] : " << histogramme[i]<< endl;
		
	return;
}
