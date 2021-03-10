#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mansion_foster.h"

#define NOMBRE_ARCHIVO_TEXTO 50
#define MAX_REQUISITOS_NINIO 300
#define EXIGENCIAS_NINIO 4

void manejo_archivo_txt(char* nombre_archivo,  char lista_requisitos_ninio[EXIGENCIAS_NINIO][MAX_AMIGOS],
        char lista_amigos_pasados_del_ninio[MAX_AMIGOS][MAX_AMIGOS], int* tope_lista_amigos_pasados) {

    FILE* archivo_de_texto = fopen(nombre_archivo, "r");
    char amigo_pasado_del_ninio[MAX_AMIGOS];
    char requisitos_ninio[MAX_REQUISITOS_NINIO];

    fgets(requisitos_ninio, MAX_REQUISITOS_NINIO, archivo_de_texto);

    char *requisito = strtok(requisitos_ninio, ";");
    int i = 0;
    while (requisito){
        strcpy(lista_requisitos_ninio[i], requisito);
        requisito = strtok (NULL, ";");
        i++;
    }

    int j = 0;
    while (fgets(amigo_pasado_del_ninio, 50, archivo_de_texto) != NULL) {
        strcpy(lista_amigos_pasados_del_ninio[j], amigo_pasado_del_ninio);
        j++;
    }
    *tope_lista_amigos_pasados = j; 
    fclose(archivo_de_texto);
} 

void elegir_amigo(char* nombre_archivo) {
    char lista_requisitos_ninio[EXIGENCIAS_NINIO][MAX_AMIGOS]; //array de punteros de exigencias
    char lista_amigos_pasados_del_ninio[MAX_AMIGOS][MAX_AMIGOS]; //array de STRINGS de amigos pasados
    int tope_lista_amigos_pasados_del_ninio;

    manejo_archivo_txt(nombre_archivo, lista_requisitos_ninio, lista_amigos_pasados_del_ninio, &tope_lista_amigos_pasados_del_ninio);

    /*FILE* archivo_de_texto = fopen(nombre_archivo, "r");
    char amigo_pasado_del_ninio[MAX_AMIGOS]; //String con el nombre del amigo
    char requisitos_ninio[MAX_REQUISITOS_NINIO]; //array que va a guardar la primera linea del archivo

    fgets(requisitos_ninio, MAX_REQUISITOS_NINIO, archivo_de_texto);

    char *requisito = strtok(requisitos_ninio, ";");
    int i = 0;
    while (requisito){
        lista_requisitos_ninio[i] = requisito;
        requisito = strtok (NULL, ";");
        i++;
    }

    int j = 0;
    while (fgets(amigo_pasado_del_ninio, 100, archivo_de_texto) != NULL) {
        strcpy(lista_amigos_pasados_del_ninio[j], amigo_pasado_del_ninio);
        j++;
    } 


    //HASTA ACA FUNCIONA BIEN
   

    tope_lista_amigos_pasados_del_ninio = j; 
    fclose(archivo_de_texto);
*/

    for (int i = 0; i < tope_lista_amigos_pasados_del_ninio; i++){
        printf("El amigo en la posicion %i es %s\n", i, lista_amigos_pasados_del_ninio[i]);
    }
    
      for (int i = 0; i < 4; i++){
        printf("El requisito en la posicion %i es %s\n", i, lista_requisitos_ninio[i]);
    }

    amigo_t lista_de_amigos[MAX_AMIGOS];
    amigo_t amigo_seleccionado;
    int tope_amigos = 0;

    traer_los_amigos(lista_de_amigos, &tope_amigos);

    int indice_amigo = 0;
    bool encontre_amigo;
    char* requerimiento_altura = lista_requisitos_ninio[1];

    while (indice_amigo < tope_amigos && !encontre_amigo){
        if(lista_de_amigos[indice_amigo].esta_en_mansion){
            if (strcmp(lista_de_amigos[indice_amigo].color, lista_requisitos_ninio[0]) == 0){
                char* requerimiento_altura = lista_requisitos_ninio[1];
                char signo_altura = *requerimiento_altura;
                
                requerimiento_altura++;
                int altura_pedida = atoi(requerimiento_altura);
                int indice_virtud = 0;
                bool encontre_virtud = false;
                while (indice_virtud < lista_de_amigos[indice_amigo].tope_virtudes && !encontre_virtud ) {
                    encontre_virtud = strcmp(lista_de_amigos[indice_amigo].virtudes[indice_virtud].descripcion, lista_requisitos_ninio[2]) == 0; 
                    indice_virtud++;
                }
                if(encontre_virtud){
                    bool encontre_defecto = false;
                    int indice_defecto = 0;
                    while (indice_defecto < lista_de_amigos[indice_amigo].tope_defectos && !encontre_defecto) {
                        if (strcmp(lista_de_amigos[indice_amigo].defectos[indice_defecto].descripcion, lista_requisitos_ninio[3])==0) {
                            encontre_defecto = true;
                        }
                        indice_defecto++;
                    }
                    if(!encontre_defecto){
                        if (signo_altura == '<'){
                            if (lista_de_amigos[indice_amigo].altura < altura_pedida){   
                                bool ninio_ya_tuvo_amigo = false;
                                int indice_amigo_pasado = 0;
                                while(indice_amigo_pasado < tope_lista_amigos_pasados_del_ninio && !ninio_ya_tuvo_amigo){
                                    if(strcmp(lista_amigos_pasados_del_ninio[indice_amigo_pasado], lista_de_amigos[indice_amigo].nombre)==0){
                                        ninio_ya_tuvo_amigo = true;
                                    }
                                    indice_amigo_pasado++;
                                }

                                if(!ninio_ya_tuvo_amigo){
                                    amigo_seleccionado = lista_de_amigos[indice_amigo-1];
                                    amigo_seleccionado.esta_en_mansion = false;
                                    lista_de_amigos[indice_amigo] = amigo_seleccionado;
                                    
                                    /*
                                        GUARDAR TODOS LOS ARCHIVOS
                                    */

                                }   
                            }
                        } else if (signo_altura == '>'){
                            if (lista_de_amigos[indice_amigo].altura > altura_pedida) {
                                bool ninio_ya_tuvo_amigo = false;
                                int indice_amigo_pasado = 0;
                                while(indice_amigo_pasado < tope_lista_amigos_pasados_del_ninio){
                                    if(strcmp(lista_amigos_pasados_del_ninio[indice_amigo_pasado], lista_de_amigos[indice_amigo].nombre)==0){
                                        ninio_ya_tuvo_amigo = true;
                                    }
                                }

                                if(!ninio_ya_tuvo_amigo){
                                    amigo_seleccionado = lista_de_amigos[indice_amigo];
                                    amigo_seleccionado.esta_en_mansion = false;
                                    lista_de_amigos[indice_amigo] = amigo_seleccionado;
                                    
                                    /*
                                        GUARDAR TODOS LOS ARCHIVOS
                                    */

                                    printf("El amigo asignado al ninio es: %s\n", amigo_seleccionado.nombre);
                                }
                            }
                        } else {
                            if (lista_de_amigos[indice_amigo].altura == altura_pedida) {
                                bool ninio_ya_tuvo_amigo = false;
                                int indice_amigo_pasado = 0;
                                while(indice_amigo_pasado < tope_lista_amigos_pasados_del_ninio){
                                    if(strcmp(lista_amigos_pasados_del_ninio[indice_amigo_pasado], lista_de_amigos[indice_amigo].nombre)==0){
                                        ninio_ya_tuvo_amigo = true;
                                    }
                                }

                                if(!ninio_ya_tuvo_amigo){
                                    amigo_seleccionado = lista_de_amigos[indice_amigo];
                                    amigo_seleccionado.esta_en_mansion = false;
                                    lista_de_amigos[indice_amigo] = amigo_seleccionado;
                                    
                                    /*
                                        GUARDAR TODOS LOS ARCHIVOS
                                    */

                                    printf("El amigo asignado al ninio es: %s\n", amigo_seleccionado.nombre);
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

void eliminar_amigo_de_mansion(amigo_t amigo_a_eleminar) {

}


void listar_amigos() {
    amigo_t lista_de_amigos[MAX_AMIGOS];
    int tope_amigos;
    traer_los_amigos(lista_de_amigos, &tope_amigos);
    int i = 0;
    while (i < tope_amigos) {
        if (lista_de_amigos[i].esta_en_mansion) {
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
        } else {
            printf("%s ya esta en la mansion, no puede ser devuelto\n", amigo.nombre);
        }
    } else {
        printf("%s no esta en la lista de amigos\n", nombre_amigo);
    }
}