#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "proc.h"

int main (int argc, char * argv[]){
	char path[32];
	int error;
	/* obtener la ruta del archivo de imagen */
	if (argc == 2){
		strcpy(path, argv[1]);
	} else {
		printf("número inválido de parámetros\n");
		return EXIT_FAILURE;
	}
	/* abrir la imagen */
	error = open_input_image(path);
	if (error == PROC_ERROR){
		printf("no se pudo abrir la imagen\n");
		return EXIT_FAILURE;
	}
	/* procesar la imagen */
	error = proc_image(0,0);
	if (error == PROC_ERROR){
		printf("no se pudo procesar la imagen\n");
		return EXIT_FAILURE;
	}
	/* mostrar las imagenes */
	cvNamedWindow ("imagen original", CV_WINDOW_AUTOSIZE);
	cvShowImage ("imagen original", src);
	cvNamedWindow ("imagen gris", CV_WINDOW_AUTOSIZE);
	cvShowImage ("imagen gris", gray);
	cvNamedWindow ("imagen threshold", CV_WINDOW_AUTOSIZE);
	cvShowImage ("imagen threshold", thresholded);
	cvNamedWindow ("perímetro", CV_WINDOW_AUTOSIZE);
	cvShowImage ("perímetro", perimeters);
	/* esperar para cerrar */
	cvWaitKey(0);
	close_input_image();
	return EXIT_SUCCESS;
}

