#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "proc.h"

int open_input_image(char * path){
	src = cvLoadImage(path,1);
	if ( src ){
		return PROC_SUCCESS;
	} else {
		return PROC_ERROR;
	}
}


void close_input_image(){
	cvReleaseImage(&src);
	cvReleaseImage(&gray);
	cvReleaseImage(&thresholded);
}


int proc_image(float compactness, int min_area){
	/* convertir la imagen a escalas de gris */
	gray = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
	cvCvtColor(src, gray, CV_BGR2GRAY);
	/* aplicar threshold sobre la imagen en gris */
	thresholded = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
	cvThreshold(gray, thresholded, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU );
	/* buscar perímetros */
	perimeters = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
	get_perimeters(thresholded,perimeters);
	detect_circles(perimeters,src);
	return PROC_SUCCESS;
}


char get_pixel_value(IplImage *img, int x, int y){
	if (img->nChannels == 1){
		return img->imageData[img->widthStep * y + x];
	} else {
		return 0;
	}
}

void set_pixel_value(IplImage *img, int x, int y, char value){
	if (img->nChannels == 1){
		img->imageData[img->widthStep * y + x] = value;
	}
}

int get_perimeters(IplImage *input, IplImage *output){
	CvMemStorage * g_storage = cvCreateMemStorage(0);
	CvSeq* contours = 0;
	IplImage *img;
	img = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
	cvNot(input,img);
	int error;
	cvFindContours( img, g_storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
	if( contours ){
		cvDrawContours(output, contours, cvScalarAll(255), cvScalarAll(255), 100, 1, 8, cvPoint(0,0));
		error = PROC_SUCCESS;
	} else {
		error = PROC_ERROR;
	}
	cvReleaseImage(&img);
	return error;
}

void detect_circles(IplImage *input, IplImage *output){
	CvMemStorage * g_storage = cvCreateMemStorage(0);
	IplImage *smoothed;
	CvSeq * circles;
	int i;
	smoothed = cvCreateImage(cvSize(input->width, input->height), IPL_DEPTH_8U, 1);
	cvSmooth(input, smoothed, CV_BLUR, 3, 0, 0, 0);
	circles = cvHoughCircles(smoothed, g_storage, CV_HOUGH_GRADIENT, 3, input->width/10, 100, 100, 15, input->width/5);
	printf("círculos encontrados: %i\n", circles->total);
	for (i = 0; i < circles->total; i++){
			float * p = (float *) cvGetSeqElem(circles, i);
			cvCircle(output, cvPoint(cvRound(p[0]),cvRound(p[1])), cvRound(p[2]), CV_RGB(255,0,0), 10, 8, 0);
			printf ("circulo en %f,%f\n", p[1], p[2]);
	}
}

char get_neighborhood_max(IplImage *img, int x, int y){
	int i, j, X, Y, radius = 1;
	X = x + radius;
	Y = y + radius;
	char aux, max_val=0;
	for (i = x - radius; i <= X; i++){
		for (j = y - radius; j <= Y; j++){
			if ( (i >= 0) && ( j >= 0) && (i < img->width) && (j < img->height) ){
				aux = get_pixel_value(img,i,j);
				if (aux > max_val){
					max_val = aux;
				}
			}
		}
	}
	return max_val;
}

char get_neighborhood_min(IplImage *img, int x, int y){
	int i, j, X, Y, radius = 1;
	X = x + radius;
	Y = y + radius;
	char aux, min_val=255;
	for (i = x - radius; i <= X; i++){
		for (j = y - radius; j <= Y; j++){
			if ( (i >= 0) && ( j >= 0) && (i < img->width) && (j < img->height) ){
				aux = get_pixel_value(img,i,j);
				if (aux == 0){
					return 0;
				}else if (aux < min_val){
					min_val = aux;
				}
			}
		}
	}
	return min_val;
}
