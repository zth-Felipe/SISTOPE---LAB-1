#include "funciones.h"


int main(int argc, char *argv[])
{
    // Validar argumentos de línea de comando
    int option;
    char* archivo_entrada = NULL;
    int filtros = 3;
    float factor_saturacion = 1.3;
    float umbral_binarizacion = 0.5;
    float umbral_clasificacion = 0.5;
    char* carpeta = NULL;
    char* archivo_csv = NULL;

    int c = 0;


    while ((option = getopt(argc, argv, "N:f:p:u:v:C:R:k")) != -1) {
        switch (option) {
            case 'N':
                archivo_entrada = optarg;
                break;
            case 'f':
                filtros = atoi(optarg);
                break;
            case 'p':
                factor_saturacion = atof(optarg);
                break;
            case 'u':
                umbral_binarizacion = atof(optarg);
                break;
            case 'v':
                umbral_clasificacion = atof(optarg);
                break;
            case 'C':
                carpeta = optarg;
                break;
            case 'R':
                archivo_csv = optarg;
                break;
            case 'k':
                c = 1;
                break;
        }
    }
    if (archivo_entrada == NULL) {
        printf("Error: falta cantidad de celdas.\n");
        return 1;
    }

    if (carpeta == NULL) {
        printf("Error: falta nombre de archivo de entrada.\n");
        return 1;
    }

    if (archivo_csv == NULL) {
        printf("Error: falta nombre de archivo CSV.\n");
        return 1;
    }

    int cantidadImagenes = contarImagen(archivo_entrada);
    printf("cantidadImagenes: %d\n", cantidadImagenes);
    int i = 1 ;
    char numero[10];

    crear_carpeta(carpeta);


    while (i<=cantidadImagenes){
        sprintf(numero, "%d", i);
        const char* prefijo = archivo_entrada;
        const char* extencion = ".bmp";
        
        // Se 
        char nombreImagen[50];
        strcpy(nombreImagen, prefijo); 
        strcat(nombreImagen, "_"); 
        strcat(nombreImagen, numero); 
        strcat(nombreImagen, extencion);
        const char* nombre = nombreImagen;
        //printf("nombreImagen: %s\n", nombreImagen);
        //aqui tiene que ir todo lo que se le quiere hacer a esa imagen// 

        BMPImage* image = read_bmp(nombre);
        if (!image) {
            return 1;
        }

        if (filtros >= 1)
        {

            BMPImage* new_image = saturate_bmp(image, factor_saturacion);
            char saturado[50];
            strcpy(saturado, carpeta);
            strcat(saturado, "/"); 
            strcat(saturado, prefijo); 
            strcat(saturado, "_"); 
            strcat(saturado, numero); 
            strcat(saturado, "_saturate");
            strcat(saturado, extencion);
            char* saturado_name = saturado;
            write_bmp(saturado_name, new_image);
        }

        if (filtros >= 2)
        {
            BMPImage* new_image_gris = grises_bmp(image);
            char grises[50];
            strcpy(grises, carpeta);
            strcat(grises, "/"); 
            strcat(grises, prefijo);
            strcat(grises, "_"); 
            strcat(grises, numero);
            strcat(grises, "_grises"); 
            strcat(grises, extencion);
            char* grises_name = grises;
            write_bmp(grises_name, new_image_gris);
        }

        if (filtros >= 3)
        {
            BMPImage* new_image_binarize = binarize_bmp(image, umbral_binarizacion*250.0f);
            char binario[50];
            strcpy(binario, carpeta);
            strcat(binario, "/"); 
            strcat(binario, prefijo); 
            strcat(binario, "_"); 
            strcat(binario, numero); 
            strcat(binario, "_binarize");
            strcat(binario, extencion);
            char* binario_name = binario;
            write_bmp(binario_name, new_image_binarize);
        }
            

        int clasificacion = is_nearly_black(image, umbral_clasificacion);
        printf("clasificacion: %d\n", clasificacion); 

        escribir_resultados_csv(nombre, clasificacion);

        //free_bmp(new_image);
        //free_bmp(new_image_gris);
        //free_bmp(new_image_binarize);
        free_bmp(image);

        i = i + 1;
    }


    return 0;
}


