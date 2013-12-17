/*
 *	Aquí se definen los procesos que se llevan a cabo en la imagen
 */

#define PROC_ERROR -1
#define PROC_SUCCESS 0

/* Estas son las variables que almacenan las imagenes */
/* src: la imagen original
 * gray: la imagen en escala de grises
 * thresholded: la imagen luego de aplicar threshold
 * perimeters: los perímetros calculados desde thresholded
 */
IplImage *src, *gray, *thresholded, *perimeters;
 
/* abre la imagen que está en 'path' */
/* retorna PROC_ERROR o PROC_SUCCESS dependiendo si puede o no abrirla */
int open_input_image(char * path);

/* cierra la imagen abierta y libera memoria usada en las imagenes */
void release_images();

/* transforma la imagen a niveles de gris
 * calcula su threshold y perímetros
 * luego usa el método hough para detectar círculos
 */
void proc_image();

/* detecta círculos en la imagen input, y los dibuja en output*/
void detect_circles(IplImage *input, IplImage *output);

/* dibuja en output los bordes encontrados en input */
int get_perimeters(IplImage *input, IplImage *output);
