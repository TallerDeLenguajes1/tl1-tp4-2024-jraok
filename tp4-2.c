#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define STOCK 5 /* cantidad disponible de productos */

// estructura para las tareas de un empleado
typedef struct{
    int empleadoID, duracion;
    char *descripcion;  
} tarea;

// estructura de lista enlazada
typedef struct{
    tarea t;
    nodo *siguiente;
} nodo;

// estructura para un producto
typedef struct {
    int productoId, cantDisponible;
    char *tipoProducto;
    float precioUnitario;
} producto;

// estructura para un cliente
typedef  struct {
    int clienteId, cantProduPedidos;
    char *nombreCliente;
    producto *lista;
} cliente;

// declaracion de funciones

producto *cargarStock(int cantidad);
cliente *direClientes(int *puntero);
void cargarClientes(cliente *listaClientes, int cantClientes, producto *stockDisponible);
void controlarStock(int *pedido, int *stockDisponible);
char *cadenaDinamica();
float factura(producto producto);
void mostrarPreventa(cliente pedido);
void mostrarProducto(producto producto);

// FUNCION PRINCIPAL
int main(){
    srand(time(NULL));

    puts("\n\t\t\t-----PREVENTA 2024-----");

    // arreglo para los clientes
    int cantClientes = 0;/* variable con la cantidad de clientes */
    cliente *listaClientes = direClientes(&cantClientes);

    // stock de la distribuidora
    producto *stockDisponible = cargarStock(STOCK);

    // llenado de datos con los clientes
    cargarClientes(listaClientes,cantClientes,stockDisponible);

    // muesta la informacion de la preventa
    printf("\n\t\t\t----LISTA DE PREVENTA----\n");
    for (int i = 0; i < cantClientes; i++){
        mostrarPreventa(listaClientes[i]);
    }

    // liberacion de la memoria
    free(stockDisponible->tipoProducto);
    for (int i = 0; i < cantClientes; i++){
        free(listaClientes[i].nombreCliente);
        for (int j = 0; j < listaClientes[i].cantProduPedidos; j++){
            free(listaClientes[i].lista->tipoProducto);
        }
        free(listaClientes[i].lista);
    }
    
    return 0;
}


// retorna una direccion con un arreglo de productos con sus datos correspondientes
producto *cargarStock(int cantidad){
    // arreglo con los tipos de produtos
    char *TiposProductos[]={"Galletas","Snack", "Cigarrillos", "Caramelos", "Bebidas"};
    // direccion de memoria para el arreglo
    producto *listaAux2 = (producto*)malloc(cantidad * sizeof(producto));

    for (short i = 0; i < cantidad; i++){
        listaAux2[i].productoId = i+1;
        listaAux2[i].cantDisponible = 1 + rand()%100;
        listaAux2[i].tipoProducto = (char*)strdup(TiposProductos[i]);
        listaAux2[i].precioUnitario = 1 + ((rand()%10000)*0.01);
    }
    
    return (listaAux2);
}

// crea una direccion de memoria capaz de contener cierta cantidad de clientes
cliente *direClientes(int *puntero){
    // estructura de control
    do{
        printf("\n\tIngrese la cantidad de clientes de hoy:\t ");
        scanf("%d",puntero);
        if (*puntero<=0)/* mesaje de error */
        {
            puts("\t\t\t---Valor invalido---");
            puts("\t\t\t   ---REINGRESE---");
        }
    } while ((*puntero)<=0);
    // asignacion de memoria para el arreglo
    cliente *listaAux = (cliente*)malloc((*puntero)*sizeof(cliente));
    return (listaAux);
}

// crea una cadena de caracteres que se actualiza caracter a caracter, retorna su direccion de memoria
char *cadenaDinamica(){
    
    char caracter;/* variable de entrada para el teclado */
    // limio el buffer
    fflush(stdin); 
    int longitud=0, capacidad = 12; /* variables para comparar y aumentar la memoria de la cadena */
    char *cadena = (char*)malloc(12);  /* puntero para la cadena con un espacio determinado */

    // este bucle se mantiene siempre que la ultima entrada por teclada no sea el ENTER
    while ((caracter = getchar()) != '\n'){
        if (longitud >= capacidad){ /* si la longitud llega al valor de la capacidad aumento la capacidad y reasigno la capacidad de memoria */
            capacidad++;
            // puntero auxiliar para la nueva direccion
            char *aux = (char*)realloc(cadena,sizeof(char)* capacidad);
            cadena = aux;
        }
        // actualizo el valor posicion a posicion de la cadena usando la longitud como indice en el areeglo
        cadena[longitud]=(char)caracter; /* casteo de la variable para guardar el caracter */
        longitud++;
    }
    cadena[longitud] = '\0'; /* agrego marca final a la cadena */

    return cadena;
}

// controla que el pedido no exceda el stock y actualiza el stock
void controlarStock(int *pedido, int *stockDisponible){
    if ((*stockDisponible)>0){ /* control de que hay Stock del producto */
        do{
            (*pedido) = (1+rand()%10); /* le cambio la cantidad para que sea aleatoria */

        } while ((*pedido) > (*stockDisponible)); /* control para no exederme de la cantidad disponible */
    }else{
        (*pedido) = 0; /* si no hay stock asigno un 0 */
    }            
    (*stockDisponible) -= (*pedido); /* descuento el pedido del stock */
};

// llena con datos el arreglo de clientes
void cargarClientes(cliente *listaClientes, int cantClientes, producto *stockDisponible){ 
    for (short i = 0; i < cantClientes; i++){
        printf("\nIngrese el nombre del cliente %d (para terminar presione ENTER):\t", i+1);
        listaClientes[i].nombreCliente = cadenaDinamica();
        listaClientes[i].clienteId = i + 1;
        listaClientes[i].cantProduPedidos = (1 + rand()%5) ;
        listaClientes[i].lista = (producto*)malloc(listaClientes[i].cantProduPedidos * sizeof(producto));

        // llenado de la lista con los productos del cliente, copio la informacion del stock en la lista del cliente
        for (int j = 0; j < listaClientes[i].cantProduPedidos; j++){ /* lo hago tantas veces como productos pida */
            
            int indice = (rand() % listaClientes[i].cantProduPedidos); /* indice aleatorio para tomar un producto del stock */
            listaClientes[i].lista[j].productoId = stockDisponible[indice].productoId; /* asigno el producto con uno del stock */
            // control de que no se pida mas de lo que hay en stock
            controlarStock(&listaClientes[i].lista[j].cantDisponible, &stockDisponible[indice].cantDisponible);
            listaClientes[i].lista[j].precioUnitario = stockDisponible[indice].precioUnitario;
            listaClientes[i].lista[j].tipoProducto = (char*)strdup(stockDisponible[indice].tipoProducto);
        }
    }   
}

//calcula el total a pagar entre precio unitario y la cantidad pedida
float factura(producto producto){
    float total = producto.cantDisponible * producto.precioUnitario;
    return total;
}

// muestra la informacion de un producto
void mostrarProducto(producto producto){
    puts("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\tID producto:\t\t\t %d",producto.productoId);
    if (producto.cantDisponible != 0){
        printf("\n\tCantidad pedida:\t\t %d",producto.cantDisponible);
    }else{
        printf("\n\tCantidad pedida:\t\t Sin Stock");
    }
    
    printf("\n\tTipo de producto:\t\t %s",producto.tipoProducto);
    printf("\n\tPrecio unitario producto:\t %.2f",producto.precioUnitario);
    printf("\n\tTotal:\t\t\t\t %.2f",factura(producto));
    puts("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
}

// muestra la informacion de una preventa
void mostrarPreventa(cliente pedido){
    float total = 0;
    puts("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("|\tNombre del cliente:\t\t %s\t  |",pedido.nombreCliente);
    printf("\n|\tID del cliente:\t\t\t %d\t  |",pedido.clienteId);
    printf("\n|\tCantidad de productos:\t\t %d\t  |",pedido.cantProduPedidos);
    for (int i = 0; i < pedido.cantProduPedidos; i++){
        mostrarProducto(pedido.lista[i]);
        total += factura(pedido.lista[i]);
    }

    printf("\t=====> TOTAL DE LA FACTURA:\t%.2f\n",total);
}