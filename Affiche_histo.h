// TP_Image.cpp : définit le point d'entrée pour l'application console.
//
#include <String>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"

void AfficheHisto(string Name,string NomFen)
{
	Mat gray = imread(Name, 0);
	
	// Initialize parameters
	int histSize = 256;    // bin size
	float range[] = { 0, 255 };
	const float *ranges[] = { range };

	// Calculate histogram
	MatND hist;
	calcHist(&gray, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);

	// Show the calculated histogram in command window
	double total;
	total = gray.rows * gray.cols;
	for (int h = 0; h < histSize; h++)
	{
		float binVal = hist.at<float>(h);
		//cout << " " << binVal;
	}

	// Plot the histogram
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
		Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
		Scalar(255, 0, 0), 2, 8, 0);
	}

	namedWindow(NomFen, 1);    imshow(NomFen, histImage);
	return;
}