#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 30

struct{
    char *nombre;
    char *apellido;
    int numero;
} typedef info;

struct{
    info contacto;
    contacto *siguiente;
} typedef contacto;

contacto *agendarContacto();
contacto *borrarContacto();
contacto *CrearAgenda();


int main(){
    srand(time(NULL));
    contacto *agenda;
    agenda = NULL;
    contacto *papelera;
    papelera = NULL;
    


    return 0;
}

contacto *agendarContacto(){

}

contacto *borrarContacto(){

}

contacto *CrearAgenda(){
    contacto *agenda = NULL;
    char nombres[5][MAX] = {"Julia","Paola","Diana","Cesar","Pablo"};
    char apellidos[5][MAX] = {"Paez","Michelli","Caseres","Orsini","Torres"};
    short indice1 = rand()%5;
    short indice2 = rand()%5;

    do{
        contacto *aux = agenda->siguiente;
        agenda->contacto.nombre = (char*)strdup(nombres[indice1]);
        agenda->contacto.apellido = (char*)strdup(nombres[indice1]);
        agenda->siguiente = NULL;    
    } while (aux != NULL);
    
    


    return agenda;
}
