#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>



#pragma pack(push, 1) 
//cuando se trabaja con uint se usa para leer directamente los bytes de la imagen, push hace que la estructura se lea byte por byte y pop hace que se lea de forma normal
typedef struct {
    // BMP Header | Tipo de dato por bits | Descripción
    uint16_t type; // Tipo de dato, tiene 2 bytes y es un número que indica si el archivo es BMP a través de las siglas BM
    uint32_t size; // Tamaño del archivo, tiene 4 bytes y es un número que indica el tamaño del archivo en bytes
    uint16_t reserved1; // Reservado, tiene 2 bytes y es un número que no se utiliza
    uint16_t reserved2; // Reservado, tiene 2 bytes y es un número que no se utiliza
    uint32_t offset; // Offset, tiene 4 bytes y es un número que indica la posición en bytes donde comienza la información de la imagen
} BMPHeader;

typedef struct {
    uint32_t size; // Tamaño de la información de la imagen, tiene 4 bytes y es un número que indica el tamaño de la información de la imagen en bytes
    int32_t width; // Ancho de la imagen, tiene 4 bytes y es un número que indica el ancho de la imagen en píxeles
    int32_t height; // Alto de la imagen, tiene 4 bytes y es un número que indica el alto de la imagen en píxeles
    uint16_t planes; // Planos, tiene 2 bytes y es un número que indica la cantidad de planos de color, debe valer 1
    uint16_t bit_count; // Bits por píxel, tiene 2 bytes y es un número que indica la cantidad de bits por píxel, debe valer 1, 4, 8, 16, 24, or 32
    uint32_t compression; // Compresión, tiene 4 bytes y es un número que indica el tipo de compresión, puede ser 0 (sin compresión), 1 (RLE 8-bit/píxel), 2 (RLE 4-bit/píxel), 3 (bitfields), 4 (JPEG), 5 (PNG)
    uint32_t size_image; // Tamaño de la imagen, tiene 4 bytes y es un número que indica el tamaño de la imagen en bytes
    int32_t x_pixels_per_meter; // Píxeles por metro en el eje X, tiene 4 bytes y es un número que indica la cantidad de píxeles por metro en el eje X
    int32_t y_pixels_per_meter; // Píxeles por metro en el eje Y, tiene 4 bytes y es un número que indica la cantidad de píxeles por metro en el eje Y
    uint32_t colors_used; // Colores usados, tiene 4 bytes y es un número que indica la cantidad de colores usados
    uint32_t colors_important; // Colores importantes, tiene 4 bytes y es un número que indica la cantidad de colores importantes
} BMPInfoHeader;
#pragma pack(pop)

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGBPixel;

typedef struct {
    int width;
    int height;
    RGBPixel *data; // Puntero a los píxeles de la imagen 
} BMPImage;



// Entrada: texto constante correspondiente al nombre de la imagen procesada y un entero el cual es 0 o 1
// Salida: un archivo .csv que se alojara en la direccion actual
// Descripcion: funcion que recopila la clasificacion a base del umbral de oscuridad de cada imagen y los almacena en un archivo.csv
void escribir_resultados_csv(const char* nombre_imagen, int clasificacion);

// Entrada: texto constante correspondiente a un nombre para carpeta
// Salida: entero indicando si se creo correctamente y con los permisos correspondinetes
// Descpripcion: crear una carpeta en la direccion actual de ejecucion con el nombre que se pasa en nombre_carpeta 
int crear_carpeta(const char* nombre_carpeta);

// Entrada: tecto constante correspondiente al prefijo de entrada (img,imagen,photo)
// Salida: numero entero positivo o 0 
// Descripcion: funcion que accede al directorio o ruta actual y cuenta todos los archivos que coincidand con el prefijo indicado y que tengan extencion .bmp
int contarImagen(const char *prefijo);

//
//
//
BMPImage* read_bmp(const char* filename);

//
//
//
void free_bmp(BMPImage* image);

//
//
//
BMPImage* saturate_bmp(BMPImage* image, float factor);

//
//
//
BMPImage* grises_bmp(BMPImage* image);

//
//
//
BMPImage* binarize_bmp(BMPImage* image, float threshold);

//
//
//
int is_nearly_black(BMPImage* image, float threshold);

// Entrada: texto constante correspondiente a nombre identificativo y una imagen
// Salida: funcion tipo void, ejecuta serie de instruccion sin un retrono especifico 
// Descripcion: "guarda" la imagen ya procesada en una ruta especifica.
void write_bmp(const char* filename, BMPImage* image);


