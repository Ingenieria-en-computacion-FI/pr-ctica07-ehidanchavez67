#include "lista_simple.h"

Lista* crearLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    if (lista) {
        lista->head = NULL;
        lista->tail = NULL;
    }
    return lista;
}

int esVacia(Lista* lista) {
    return (lista == NULL || lista->head == NULL);
}

// Función interna para crear nodos
static Nodo* crearNodo(void* dato, size_t size) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo) {
        nuevo->dato = malloc(size); // Espacio para el valor real
        if (nuevo->dato) {
            memcpy(nuevo->dato, dato, size); // Clonación bit a bit
        }
        nuevo->siguiente = NULL;
    }
    return nuevo;
}

void insertarInicio(Lista* lista, void* dato, size_t size) {
    Nodo* nuevo = crearNodo(dato, size);
    if (!nuevo) return;

    if (esVacia(lista)) {
        lista->head = lista->tail = nuevo;
    } else {
        nuevo->siguiente = lista->head;
        lista->head = nuevo;
    }
}

void insertarFinal(Lista* lista, void* dato, size_t size) {
    Nodo* nuevo = crearNodo(dato, size);
    if (!nuevo) return;

    if (esVacia(lista)) {
        lista->head = lista->tail = nuevo;
    } else {
        lista->tail->siguiente = nuevo;
        lista->tail = nuevo;
    }
}

void* buscarPorPosicion(Lista* lista, int pos) {
    if (esVacia(lista) || pos < 0) return NULL;
    Nodo* temp = lista->head;
    for (int i = 0; temp != NULL && i < pos; i++) {
        temp = temp->siguiente;
    }
    return (temp) ? temp->dato : NULL;
}

void eliminarPorPosicion(Lista* lista, int pos) {
    if (esVacia(lista) || pos < 0) return;
    Nodo* temp = lista->head;

    if (pos == 0) {
        lista->head = temp->siguiente;
        if (lista->head == NULL) lista->tail = NULL;
        free(temp->dato);
        free(temp);
        return;
    }

    Nodo* ant = NULL;
    for (int i = 0; temp != NULL && i < pos; i++) {
        ant = temp;
        temp = temp->siguiente;
    }

    if (temp) {
        ant->siguiente = temp->siguiente;
        if (temp == lista->tail) lista->tail = ant;
        free(temp->dato);
        free(temp);
    }
}

void modificar(Lista* lista, int pos, void* dato, size_t size) {
    if (esVacia(lista) || pos < 0) return;
    Nodo* temp = lista->head;
    for (int i = 0; temp != NULL && i < pos; i++) {
        temp = temp->siguiente;
    }
    if (temp) {
        free(temp->dato);
        temp->dato = malloc(size);
        memcpy(temp->dato, dato, size);
    }
}

void imprimirLista(Lista* lista, ImprimirFunc imprimir) {
    Nodo* actual = lista->head;
    while (actual) {
        imprimir(actual->dato);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}

void vaciarLista(Lista* lista) {
    while (!esVacia(lista)) eliminarPorPosicion(lista, 0);
}

void borrarLista(Lista* lista) {
    if (!lista) return;
    vaciarLista(lista);
    free(lista);
}

// Navegación básica
Nodo* primero(Lista* lista) { return lista->head; }
Nodo* ultimo(Lista* lista) { return lista->tail; }
Nodo* siguiente(Nodo* actual) { return (actual) ? actual->siguiente : NULL; }