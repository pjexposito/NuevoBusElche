#pragma once

#define LINEA_A 0
#define LINEA_B 1
#define LINEA_C 2
#define LINEA_D 3
#define LINEA_E 4
#define LINEA_F 5
#define LINEA_G 6
#define LINEA_H 7
#define LINEA_I 8
#define LINEA_J 9
#define LINEA_K 10
#define LINEA_L 11
#define LINEA_R1 12
#define LINEA_R2 13
  
// Valor por defecto de el número de parada y la linea
#define NUM_DEFAULT 0

// Claves donde se guardarán los datos del programa
#define PRINCIPAL_PKEY 1
#define FAV1_PKEY 2
#define FAV2_PKEY 3
#define FAV3_PKEY 4 
#define FAV4_PKEY 5  
#define FAV5_PKEY 6  
  
#define TOTAL_KEY_PARADAS 13

struct estructura_bus {
    char linea;//Linea. Si es 0, se debe descartar
    int tiempo1;//Primer valor de tiempo
    int tiempo2;//Segundo valor de tiempo
    int parada; // Parada a la que pertenecen los valores. Debe ser igual en todo el array.
}; 

struct estructura_bus valores_parada[15];// Pongo 15 por que existen 16 líneas disponibles (el array empieza en 0, por eso es 15) 