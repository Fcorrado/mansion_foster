#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mansion_foster.h"

#define NOMBRE_ARCHIVO_TEXTO 50
#define MAX_REQUISITOS_NINIO 300
#define EXIGENCIAS_NINIO 4

int crear_archivo_binario(amigo_t lista_de_amigos[MAX_AMIGOS], int tope_amigos) {
    FILE * fPtr;
    fPtr = fopen("amigos_mansion.dat", "w");

    if (fPtr == NULL) {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    fwrite(lista_de_amigos, sizeof(amigo_t), tope_amigos, fPtr);

    fclose(fPtr);

    printf("File created and saved successfully. :) \n");

    return 0;
}


void poner_en_minusculas(char string[MAX_NOMBRE]) {
    int tope = strlen(string);
    for (int i = 0; i < tope; i++) {
        if (string[i] >= 'A' && string[i] <= 'Z') string[i] += 32;
    }
    
}

bool buscar_virtud(char* lista_descripcion_virtudes_amigos, int tope_virtudes, char* requisito_virtud) {
    int indice_virtud = 0;
    bool encontre_virtud;
    while ((indice_virtud < tope_virtudes) && (!encontre_virtud)) {
        if (strcmp(lista_descripcion_virtudes_amigos, requisito_virtud) == 0) { 
            encontre_virtud = true;
            indice_virtud++;
        }
    }
}

bool encontre_defecto_amigo(int tope_defectos, char* lista_descripcion_defectos_amigos, char* defecto_no_requerido_ninio) {
    bool encontre_defecto = false;
    int indice_defecto = 0;
    while ((indice_defecto < tope_defectos) && (!encontre_defecto)) {
        if (strcmp(lista_descripcion_defectos_amigos, defecto_no_requerido_ninio) == 0) {
            encontre_defecto = true;
        }
        indice_defecto++;
    }
    return encontre_defecto;
}

void escribir_amigo_en_lista_ninio(char* nombre_amigo_seleccionado, char* nombre_archivo, char lista_amigos_pasados_del_ninio[MAX_AMIGOS][MAX_AMIGOS],
    char lista_requisitos_ninio[EXIGENCIAS_NINIO][MAX_AMIGOS], int tope_amigos_pasados_del_ninio) {
    FILE* archivo_de_texto = fopen(nombre_archivo, "w");

    int i = 0;
    while (i < 4) {
        if(i==3){
            fprintf(archivo_de_texto, "%s\n", lista_requisitos_ninio[i]);
        }else{
            fprintf(archivo_de_texto, "%s;", lista_requisitos_ninio[i]);
        }
        i++;
    }
    int j = 0;
    while( j < tope_amigos_pasados_del_ninio) {
        fprintf(archivo_de_texto, "%s\n", lista_amigos_pasados_del_ninio[j]);
        j++;
    }

    fprintf(archivo_de_texto, "%s", nombre_amigo_seleccionado);
    fclose(archivo_de_texto);
    
}

void manejo_archivo_txt(char* nombre_archivo,  char lista_requisitos_ninio[EXIGENCIAS_NINIO][MAX_AMIGOS],
    char lista_amigos_pasados_del_ninio[MAX_AMIGOS][MAX_AMIGOS], int* tope_lista_amigos_pasados) {

    printf("open file txt\n");
    FILE* archivo_de_texto = fopen(nombre_archivo, "r");
    char amigo_pasado_del_ninio[MAX_AMIGOS];
    char requisitos_ninio[MAX_REQUISITOS_NINIO];
    int len;

    printf("primer get\n");
    fgets(requisitos_ninio, MAX_REQUISITOS_NINIO, archivo_de_texto);
    len = strlen(requisitos_ninio);
    requisitos_ninio[len-1] = 0;

    printf("primer strtok\n");
    char *requisito = strtok(requisitos_ninio, ";");
    int i = 0;
    while (requisito){
        strcpy(lista_requisitos_ninio[i], requisito);
        requisito = strtok (NULL, ";");
        poner_en_minusculas(lista_requisitos_ninio[i]);
        i++;
    }

    printf("loop fgets\n");
    int j = 0;
    while (fgets(amigo_pasado_del_ninio, 50, archivo_de_texto) != NULL) {
        len = strlen(amigo_pasado_del_ninio);
        if (amigo_pasado_del_ninio[len-1] == '\n' ) {
            amigo_pasado_del_ninio[len-1] = 0;
        }
        strcpy(lista_amigos_pasados_del_ninio[j], amigo_pasado_del_ninio);
        j++;
    }

    printf("post loop\n");
    *tope_lista_amigos_pasados = j; 
    fclose(archivo_de_texto);

    printf("cierro archivo txt\n");
} 

void elegir_amigo(char* nombre_archivo) {

    printf("inicio elegir amigo\n");
    char lista_requisitos_ninio[EXIGENCIAS_NINIO][MAX_AMIGOS];
    char lista_amigos_pasados_del_ninio[MAX_AMIGOS][MAX_AMIGOS];
    int tope_lista_amigos_pasados_del_ninio;

    printf("Pre archivo txt\n");
    manejo_archivo_txt(nombre_archivo, lista_requisitos_ninio, lista_amigos_pasados_del_ninio, &tope_lista_amigos_pasados_del_ninio);    

    printf("POST archivo txt\n");
    amigo_t lista_de_amigos[MAX_AMIGOS];
    amigo_t amigo_seleccionado;
    int tope_amigos = 0;

    printf("Pre archivo binario\n");
    traer_los_amigos(lista_de_amigos, &tope_amigos);

    printf("post archivo binario\n");
    int indice_amigo = 0;
    bool encontre_amigo = false;
    char* requerimiento_altura = lista_requisitos_ninio[1];

    while ((indice_amigo < tope_amigos) && (!encontre_amigo)) { //primer while
        if (lista_de_amigos[indice_amigo].esta_en_mansion) {
            if (strcmp(lista_de_amigos[indice_amigo].color, lista_requisitos_ninio[0]) == 0) {
                bool encontre_virtud = false;
                encontre_virtud = buscar_virtud(lista_de_amigos[indice_amigo].virtudes->descripcion, lista_de_amigos[indice_amigo].tope_virtudes, lista_requisitos_ninio[2]);
               
                if (encontre_virtud) {
                    bool encontre_defecto = false;
                    encontre_defecto = encontre_defecto_amigo(lista_de_amigos[indice_amigo].tope_defectos, lista_de_amigos[indice_amigo].defectos->descripcion, lista_requisitos_ninio[3]);
                   
                    if (!encontre_defecto) {
                        char* requerimiento_altura = lista_requisitos_ninio[1];
                        char signo_altura = *requerimiento_altura;               
                        requerimiento_altura++;
                        int altura_pedida = atoi(requerimiento_altura);

                        if (signo_altura == '<'){
                            if (lista_de_amigos[indice_amigo].altura < altura_pedida) {   
                                bool ninio_ya_tuvo_amigo = false;
                                int indice_amigo_pasado = 0;
                                while (indice_amigo_pasado < tope_lista_amigos_pasados_del_ninio && !ninio_ya_tuvo_amigo) {
                                    if (strcmp(lista_amigos_pasados_del_ninio[indice_amigo_pasado], lista_de_amigos[indice_amigo].nombre)==0) {
                                        ninio_ya_tuvo_amigo = true;
                                    }
                                    indice_amigo_pasado++;
                                }

                                if (!ninio_ya_tuvo_amigo) {
                                    amigo_seleccionado = lista_de_amigos[indice_amigo];
                                    amigo_seleccionado.esta_en_mansion = false;
                                    lista_de_amigos[indice_amigo] = amigo_seleccionado;
                                    encontre_amigo = true;
                                    escribir_amigo_en_lista_ninio(amigo_seleccionado.nombre, nombre_archivo, lista_amigos_pasados_del_ninio, lista_requisitos_ninio, tope_lista_amigos_pasados_del_ninio);
                                    crear_archivo_binario(lista_de_amigos, tope_amigos);
                                    
                                    printf("El amigo asignado al ninio por menor es: %s\n", amigo_seleccionado.nombre);

                                }   
                            }
                        } else if (signo_altura == '>') {
                            if (lista_de_amigos[indice_amigo].altura > altura_pedida) {
                                bool ninio_ya_tuvo_amigo = false;
                                int indice_amigo_pasado = 0;
                                while (indice_amigo_pasado < tope_lista_amigos_pasados_del_ninio && !ninio_ya_tuvo_amigo) {
                                    if (strcmp(lista_amigos_pasados_del_ninio[indice_amigo_pasado], lista_de_amigos[indice_amigo].nombre)==0) {
                                        ninio_ya_tuvo_amigo = true;
                                    }
                                    indice_amigo_pasado++;
                                }

                                if (!ninio_ya_tuvo_amigo) {
                                    amigo_seleccionado = lista_de_amigos[indice_amigo];
                                    amigo_seleccionado.esta_en_mansion = false;
                                    lista_de_amigos[indice_amigo] = amigo_seleccionado;
                                    encontre_amigo = true;
                                    escribir_amigo_en_lista_ninio(amigo_seleccionado.nombre, nombre_archivo, lista_amigos_pasados_del_ninio, lista_requisitos_ninio, tope_lista_amigos_pasados_del_ninio);
                                    crear_archivo_binario(lista_de_amigos, tope_amigos);
                                    printf("El amigo asignado al ninio por mayor es: %s\n", amigo_seleccionado.nombre);
                                }
                            }
                        } else {
                            if (lista_de_amigos[indice_amigo].altura == altura_pedida) {
                                bool ninio_ya_tuvo_amigo = false;
                                int indice_amigo_pasado = 0;
                                while (indice_amigo_pasado < tope_lista_amigos_pasados_del_ninio && !ninio_ya_tuvo_amigo) {
                                    if (strcmp(lista_amigos_pasados_del_ninio[indice_amigo_pasado], lista_de_amigos[indice_amigo].nombre)==0) {
                                        ninio_ya_tuvo_amigo = true;
                                    }
                                    indice_amigo_pasado++;
                                }
                                if (!ninio_ya_tuvo_amigo) {
                                    amigo_seleccionado = lista_de_amigos[indice_amigo];
                                    amigo_seleccionado.esta_en_mansion = false;
                                    lista_de_amigos[indice_amigo] = amigo_seleccionado;
                                    encontre_amigo = true;
                                    escribir_amigo_en_lista_ninio(amigo_seleccionado.nombre, nombre_archivo, lista_amigos_pasados_del_ninio, lista_requisitos_ninio, tope_lista_amigos_pasados_del_ninio);
                                    crear_archivo_binario(lista_de_amigos, tope_amigos);

                                    printf("El amigo asignado al ninio por igual es: %s\n", amigo_seleccionado.nombre);
                                }   
                            }                           
                        }
                    }
                }
            }
        }
        indice_amigo++;
    }
}

void traer_los_amigos (amigo_t lista_de_amigos[MAX_AMIGOS], int* tope_amigos) {
    FILE* amigos_mansion = fopen("amigos_mansion.dat", "r");
    amigo_t el_amigo;
    int i = 0;
    while (fread(&el_amigo, sizeof(amigo_t), 1, amigos_mansion) > 0) {
        lista_de_amigos[i] = el_amigo;
        i++;
    }

    *tope_amigos = i;
    fclose(amigos_mansion);
}

void listar_amigos() {
    amigo_t lista_de_amigos[MAX_AMIGOS];
    int tope_amigos;
    traer_los_amigos(lista_de_amigos, &tope_amigos);
    int i = 0;
    while (i < tope_amigos) {
        if (lista_de_amigos[i].esta_en_mansion) {
            printf("%s\n", lista_de_amigos[i].nombre);
        }
        i++;
    }
}

void devolver_amigo(char* nombre_amigo) {
    amigo_t lista_de_amigos[MAX_AMIGOS];
    int tope_amigos;
    traer_los_amigos(lista_de_amigos, &tope_amigos);

    int i = 0;
    bool encontre_amigo;

    while (i < tope_amigos && !encontre_amigo){
        encontre_amigo = strcmp(lista_de_amigos[i].nombre, nombre_amigo) == 0;
        i++;
    }

    if (encontre_amigo) {
        amigo_t amigo = lista_de_amigos[i-1];
        if (!amigo.esta_en_mansion) {
            amigo.esta_en_mansion = true;
            lista_de_amigos[i-1] = amigo;
            crear_archivo_binario(lista_de_amigos, tope_amigos);
        } else {
            printf("%s ya esta en la mansion, no puede ser devuelto\n", amigo.nombre);
        }
    } else {
        printf("%s no esta en la lista de amigos\n", nombre_amigo);
    }
}