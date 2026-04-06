#include <stdio.h>
#include "lista_simple.h"

// Funciones para que la lista sepa qué hacer con los INT
void impInt(void* d) { printf("%d -> ", *(int*)d); }
int cmpInt(void* a, void* b) { return (*(int*)a - *(int*)b); }

int main() {
    Lista* l = crearLista();
    int a=10, b=20, c=30, x=99;

    // 1. Inserciones
    insertarInicio(l, &b, sizeof(int)); 
    insertarInicio(l, &a, sizeof(int)); 
    insertarFinal(l, &c, sizeof(int));  
    printf("Lista inicial: "); imprimirLista(l, impInt);

    // 2. Modificar y Buscar
    modificar(l, 1, &x, sizeof(int)); // Cambia el 20 por 99
    printf("Pos 1 modificada: "); imprimirLista(l, impInt);
    printf("¿Esta el 99?: %s\n", buscarPorElemento(l, &x, cmpInt) ? "Si" : "No");

    // 3. Eliminaciones
    eliminarPorPosicion(l, 0);
    eliminarPorElemento(l, &c, cmpInt); 
    printf("Tras borrar pos 0 y el dato 30: "); imprimirLista(l, impInt);

    // 4. Navegación
    Nodo* p = primero(l);
    if(p) printf("El primer dato es: %d\n", *(int*)p->dato);

    // 5. Limpiar
    borrarLista(l);
    printf("Lista borrada.\n");

    return 0;
}