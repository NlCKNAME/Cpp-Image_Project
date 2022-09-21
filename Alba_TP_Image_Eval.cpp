
// TP_Image.cpp : définit le point d'entrée pour l'application console.
//

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace std;
using namespace cv;

unsigned char *pixelsArray;
short nbCols, nbRows;
unsigned int histogramme[256];

int main()
{
	/********************************************************************/
	/* PARTIE A NE PAS MODIFIER						*********************/
	/********************************************************************/
	
	// Définition des variables spécifiques à Open CV
	Mat image;
	 
	// Chargement de l'image
	image = imread("fleur.jpg", 0);
		
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
	/* PROJET: Début de zone de programmation ETUDIANT     *************/
	/* Nombre de pixels en largeur : variable nbCols       *************/
	/* Nombre de pixels en largeur : variable nbRows       *************/
	/* Tableau des pixels organisé ligne par ligne : pixelsArray       */
	/*******************************************************************/
	
	// Question 2
	cout << "Hauteur de l'image : " << nbRows << endl;;
	cout << "Largeur de l'image : " << nbCols << endl;;
	cout << "Nombre de pixels dans l'image : " << nbCols * nbRows << endl;

	// Question 3
	for (int i = 0; i < 50; i++)
		cout << "Niveau de gris du pixel [" << i << "] : " << short(pixelsArray[(nbRows * 2) + i]) << endl;

	// Question 4
	void calcHisto(void);
	void pixelMax(void);

	calcHisto();
	pixelMax();
	
	
	// Question 5
	void triJD(void);

	triJD();


	waitKey(0);
	return 0;
}

// Définition des fonctions


// Codage de la fonction calcHisto
void calcHisto(void)
{
	for (int Ndg = 0; Ndg < 256; Ndg++)
	{
		for (int i = 0; i < (nbCols*nbRows); i++)
		{
			if (pixelsArray[i] == Ndg)
				histogramme[Ndg] = histogramme[Ndg] + 1;
		}
		cout << "Histogramme [" << Ndg << "] : " << histogramme[Ndg] << endl;
	}
}

void pixelMax()
{
	int NdG_Max = 0;
	for (int i = 0; i < 256; i++)
	{
		if (histogramme[i] > histogramme[NdG_Max])
			NdG_Max = i;
	}
	cout << "Le niveau de gris le plus present est : " << NdG_Max << " avec " << histogramme[NdG_Max] << " valeurs" << endl;
}

void triJD()
{
	int HistoTriJD[256];

	for (int i = 0; i < 256; i++)
		HistoTriJD[i] = histogramme[i];

	for (int i = 0; i < 256; i++) //sans faire n - 1 sinon il nous manque une valeur 
	{
		for (int j = 0; j < 256; j++)
		{
			if (HistoTriJD[j] > HistoTriJD[i])
			{
				int temp = HistoTriJD[i];
				HistoTriJD[i] = HistoTriJD[j];
				HistoTriJD[j] = temp;
			}
		}
	}

	for (int i = 0; i < 256; i++)
		cout << "\nHistogramme TriJD[" << i << "] : " << HistoTriJD[i];
}