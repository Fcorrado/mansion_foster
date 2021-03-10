#ifndef __MANSION_FOSTER_H__
#define __MANSION_FOSTER_H__

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define MAX_NOMBRE 50
#define MAX_COLOR 50
#define MAX_VIRTUDES 10
#define MAX_DEFECTOS 10
#define MAX_DESCRIPCION 200
#define MAX_AMIGOS 1000

typedef struct aspecto {
    char descripcion[MAX_DESCRIPCION];
} aspecto_t;

typedef struct amigo {
    char nombre[MAX_NOMBRE];
    char color[MAX_COLOR];
    int altura;
    aspecto_t virtudes[MAX_VIRTUDES];
    int tope_virtudes;
    aspecto_t defectos[MAX_DEFECTOS];
    int tope_defectos;
    bool esta_en_mansion;
} amigo_t;


void elegir_amigo(char* nombre_archivo);

void listar_amigos();

void devolver_amigo();

void traer_los_amigos();


#endif /*__MANSION_FOSTER_H__*/



