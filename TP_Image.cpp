
// TP_Image.cpp : définit le point d'entrée pour l'application console.
//
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;

using namespace cv;
#include "Affiche_histo.h"

unsigned char *pixelsArray;
short nbCols, nbRows;


int main()
{
	/********************************************************************/
	/* PARTIE A NE PAS MODIFIER						*********************/
	/********************************************************************/
	
	// Définition des variables spécifiques à Open CV
	Mat image;
	 
	// Chargement de l'image
	string Name;

	//cout << "Entrer le nom de l'image à traiter sous la forme ****.jpg:   "; cin >> Name;
	image = imread("passerelle_NG.jpg", 0);
		
	if (image.data == NULL)
	{
		cerr << "Impossible d'ouvrir l'image ! ";
		return -1;
	}

	// Utiliser dans le cadre de la séquence n°3
	Mat image_bin;						// Nouvelle instance de Mat pour éviter d'écraser l'histogramme source
	image_bin = image.clone();			// Clonage de l'image pour utilisation en traitement ponctuel
	//pixelsArrayTrait = &image_bin.data[0];	// Pointeur résultat de la binarisation

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
	void calcHisto(void);
	int pixelNGplusRep(void);

	calcHisto();
	AfficheHisto("passerelle_NG.jpg", "Affiche histo");

	int Max = pixelNGplusRep();

	cout << "Le niveau de gris le plus present est : " << Max << endl;

	waitKey(0);
	return 0;
}

void calcHisto()
{
	unsigned int histogramme[256] = {0};

	for (int Ndg = 0; Ndg < 256; Ndg++)
	{
		for (int i = 0; i < nbCols * nbRows; i++)
		{
			if (pixelsArray[i] == Ndg)
			{
				histogramme[Ndg] = histogramme[Ndg] + 1;
			}
		}

		cout << "Niveau [" << Ndg << "] : " << histogramme[Ndg] << endl;
	}
}

int pixelNGplusRep()
{
	int Max = 0;
	unsigned int histogramme[256] = { 0 };

	for (int Ndg = 0; Ndg < 256; Ndg++)
	{
		for (int i = 0; i < nbCols * nbRows; i++)
		{
			if (pixelsArray[i] == Ndg)
			{
				histogramme[Ndg] = histogramme[Ndg] + 1;
			}
		}

		if (histogramme[Ndg] > histogramme[Max])
		{
			Max = Ndg;
		}
	}

	return Max;
}