#ifndef __LISTA_SIMPLE_H__
#define __LISTA_SIMPLE_H__

#include <stddef.h>

typedef struct Nodo {
    void* dato;
    struct Nodo* siguiente;
} Nodo;

typedef struct {
    Nodo* head;
    Nodo* tail;
} Lista;

typedef int (*CompararFunc)(void*, void*);
typedef void (*ImprimirFunc)(void*);

Lista* crearLista();
int esVacia(Lista* lista);
void insertarInicio(Lista* lista, void* dato, size_t size);
void insertarFinal(Lista* lista, void* dato, size_t size);
void eliminarPorPosicion(Lista* lista, int pos);
void eliminarPorElemento(Lista* lista, void* dato, CompararFunc cmp);
void* buscarPorPosicion(Lista* lista, int pos);
int buscarPorElemento(Lista* lista, void* dato, CompararFunc cmp);
Nodo* primero(Lista* lista);
Nodo* ultimo(Lista* lista);
Nodo* siguiente(Nodo* actual);
void modificar(Lista* lista, int pos, void* dato, size_t size);
void imprimirLista(Lista* lista, ImprimirFunc imprimir);
void vaciarLista(Lista* lista);
void borrarLista(Lista* lista);

#endif