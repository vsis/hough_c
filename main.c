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
		printf("Número inválido de parámetros\n");
		return EXIT_FAILURE;
	}
	/* abrir la imagen */
	error = open_input_image(path);
	if (error == PROC_ERROR){
		printf("no se pudo abrir la imagen\n");
		return EXIT_FAILURE;
	}
	/* procesar la imagen */
	proc_image();
	/* mostrar las imagenes usadas para procesar (gray, thresholded, perimeters) */
	cvNamedWindow ("imagen gris", CV_WINDOW_AUTOSIZE);
	cvShowImage ("imagen gris", gray);
	cvNamedWindow ("imagen threshold", CV_WINDOW_AUTOSIZE);
	cvShowImage ("imagen threshold", thresholded);
	cvNamedWindow ("perímetros", CV_WINDOW_AUTOSIZE);
	cvShowImage ("perímetros", perimeters);
	/* mostrar la imagen original con los círculos marcados */
	cvNamedWindow ("imagen original", CV_WINDOW_AUTOSIZE);
	cvShowImage ("imagen original", src);
	/* esperar a que el usuario presione una tecla para cerrar */
	cvWaitKey(0);
	release_images();
	return EXIT_SUCCESS;
}

