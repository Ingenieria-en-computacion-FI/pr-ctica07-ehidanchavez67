#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lista_simple.h"

Lista* crearLista() {
    Lista* l = (Lista*)malloc(sizeof(Lista));
    l->head = l->tail = NULL;
    return l;
}

int esVacia(Lista* l) { return (l == NULL || l->head == NULL); }

static Nodo* crearNodo(void* dato, size_t size) {
    Nodo* n = (Nodo*)malloc(sizeof(Nodo));
    n->dato = malloc(size);
    memcpy(n->dato, dato, size);
    n->siguiente = NULL;
    return n;
}

void insertarInicio(Lista* l, void* d, size_t s) {
    Nodo* n = crearNodo(d, s);
    if (esVacia(l)) l->head = l->tail = n;
    else { n->siguiente = l->head; l->head = n; }
}

void insertarFinal(Lista* l, void* d, size_t s) {
    Nodo* n = crearNodo(d, s);
    if (esVacia(l)) l->head = l->tail = n;
    else { l->tail->siguiente = n; l->tail = n; }
}

void eliminarPorPosicion(Lista* l, int pos) {
    if (esVacia(l)) return;
    Nodo *temp = l->head, *ant = NULL;
    if (pos == 0) {
        l->head = temp->siguiente;
        if (!l->head) l->tail = NULL;
    } else {
        for (int i = 0; temp && i < pos; i++) { ant = temp; temp = temp->siguiente; }
        if (!temp) return;
        ant->siguiente = temp->siguiente;
        if (temp == l->tail) l->tail = ant;
    }
    free(temp->dato); free(temp);
}

void eliminarPorElemento(Lista* l, void* d, CompararFunc cmp) {
    Nodo* aux = l->head;
    for (int i = 0; aux; i++) {
        if (cmp(aux->dato, d) == 0) { eliminarPorPosicion(l, i); return; }
        aux = aux->siguiente;
    }
}

void* buscarPorPosicion(Lista* l, int pos) {
    Nodo* t = l->head;
    for (int i = 0; t && i < pos; i++) t = t->siguiente;
    return (t) ? t->dato : NULL;
}

int buscarPorElemento(Lista* l, void* d, CompararFunc cmp) {
    Nodo* t = l->head;
    while (t) { if (cmp(t->dato, d) == 0) return 1; t = t->siguiente; }
    return 0;
}

void modificar(Lista* l, int pos, void* d, size_t s) {
    Nodo* t = l->head;
    for (int i = 0; t && i < pos; i++) t = t->siguiente;
    if (t) { free(t->dato); t->dato = malloc(s); memcpy(t->dato, d, s); }
}

void imprimirLista(Lista* l, ImprimirFunc imp) {
    Nodo* a = l->head;
    while (a) { imp(a->dato); a = a->siguiente; }
    printf("NULL\n");
}

void vaciarLista(Lista* l) { while (!esVacia(l)) eliminarPorPosicion(l, 0); }
void borrarLista(Lista* l) { vaciarLista(l); free(l); }

Nodo* primero(Lista* l) { return l->head; }
Nodo* ultimo(Lista* l) { return l->tail; }
Nodo* siguiente(Nodo* n) { return n->siguiente; }