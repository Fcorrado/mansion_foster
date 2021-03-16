#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mansion_foster.h"

int main(int argc, char *argv[]) {

    if (argv[1]) {
        if (strcmp(argv[1], "elegir_amigo") == 0) {
            if (argv[2]) {
                printf("Vamos a elegir amigo para %s \n", argv[2]);
                elegir_amigo(argv[2]);
            } else {
                printf("No se encuentra el archivo necesario para realizar la operacion");
            }
        } else if (strcmp(argv[1], "listar_amigos") == 0) {
            listar_amigos();
        } else if (strcmp(argv[1], "devolver_amigo") == 0) {
            if (argv[2]) {
                devolver_amigo(argv[2]);
            } else {
                printf("No se encuentra parametro con nombre del amigo");
            }
        }
    }
    return 1;
}
