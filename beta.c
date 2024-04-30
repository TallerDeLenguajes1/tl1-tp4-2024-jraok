#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 30

struct{
    char *nombre;
    int numero;
} typedef contacto;

struct{
    contacto contacto;
    NodoAgenda *siguiente;
} typedef NodoAgenda;

NodoAgenda *nodoVacio();
NodoAgenda *crearNodo();


int main(){
    srand(time(NULL));
    NodoAgenda *start = crearNodo;
    


    return 0;
}

NodoAgenda *crearNodo(){
    int indice = rand() % 5;
    char nombres[5][MAX]={"Roman Arancibia","Santiago Ponce","Gonzalo Payrola","Nicolas Jimenez","Aldo Juarez"};
    NodoAgenda *nuevoContacto = (NodoAgenda*)malloc(sizeof(NodoAgenda));
    nuevoContacto->contacto.nombre = (char*)strdup(nombres[indice]);
    nuevoContacto->contacto.numero = 381363500 + rand() % 10;;
    nuevoContacto->siguiente=NULL;

    return nuevoContacto;
}

NodoAgenda *nodoVacio(){
    NodoAgenda *nuevo = (NodoAgenda*)malloc(sizeof(NodoAgenda));

    return nuevo;
}
