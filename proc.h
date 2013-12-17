/*
 *	Aquí se definen los procesos que se llevan a cabo en la imagen
 */

#define PROC_ERROR -1
#define PROC_SUCCESS 0

/* Estas son las variables que almacenan las imagenes */
/* src: la imagen original
 * gray: la imagen en escala de grises
 * thresholded: la imagen luego de aplicar threshold
 */
IplImage *src, *gray, *thresholded, *perimeters;
 
/* abre la imagen que está en 'path' */
/* retorna PROC_ERROR o PROC_SUCCESS dependiendo si puede o no abrirla */
int open_input_image(char * path);

/* cierra el descriptor de archivo */
void close_input_image();

/* transforma la imagen a niveles de gris
 * calcula su threshold, etiqueta componentes y
 * calcula su compactness.
 * para determinar si se trata o no de un círculo */
int proc_image(float compactness, int min_area);

/* detecta círculos en la imagen input, y los dibuja en output*/
void detect_circles(IplImage *input, IplImage *output);

/* obtiene el pixel x,y de la imagen */
char get_pixel_value(IplImage *img, int x, int y);

/* asigna un valor (gris) a un pixel dado */
void set_pixel_value(IplImage *img, int x, int y, char value);

/* retorna el minimo valor del vecindario de un pixel */
char get_neighborhood_min(IplImage *img, int x, int y);

/* retorna le máximo valor del vecindario de un pixel */
char get_neighborhood_max(IplImage *img, int x, int y);

/* component labelling*/
/* etiqueta los bordes encontrados */
int get_perimeters(IplImage *input, IplImage *output);

/* etiqueta las areas encontradas, basándose en el component labelling */
int get_regions();
