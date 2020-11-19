#include "abb.h"

#define EXITO 0
#define ERROR -1

/*
 * Crea el arbol y reserva la memoria necesaria de la estructura.
 * Comparador se utiliza para comparar dos elementos.
 * Destructor es invocado sobre cada elemento que sale del arbol,
 * puede ser NULL indicando que no se debe utilizar un destructor.
 *
 * Devuelve un puntero al arbol creado o NULL en caso de error.
 */
abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
    if(!comparador) return NULL;
    abb_t* arbol = calloc(1,sizeof(abb_t));
    arbol->comparador = comparador;
    arbol->destructor = destructor;
    return arbol;
}


nodo_abb_t* insertar_nodo_arbol(nodo_abb_t* raiz,void* elemento,abb_comparador comparador,bool* exito){
	if(!raiz){
		raiz = calloc(1,sizeof(nodo_abb_t));
		if(!raiz){
			*exito = false;
			return NULL;
		}
		*exito = true;
		raiz->elemento = elemento;
		return raiz;
	}

	if(comparador(elemento,raiz->elemento) > 0){
		raiz->derecha = insertar_nodo_arbol(raiz->derecha,elemento,comparador,exito);
	}else{
		raiz->izquierda = insertar_nodo_arbol(raiz->derecha,elemento,comparador,exito);
	}

	return raiz;
}
/*
 * Inserta un elemento en el arbol.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 * El arbol admite elementos con valores repetidos.
 */
int arbol_insertar(abb_t* arbol, void* elemento){
	if(!arbol) return ERROR;

	bool exito = false;

	arbol->nodo_raiz = insertar_nodo_arbol(arbol->nodo_raiz,elemento,arbol->comparador,&exito);

	if(exito){
		return EXITO;
	}
	return ERROR;
}

/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación) y si lo encuentra lo quita del arbol.
 * Adicionalmente, si encuentra el elemento, invoca el destructor con
 * dicho elemento.
 * Devuelve 0 si pudo eliminar el elemento o -1 en caso contrario.
 */
int arbol_borrar(abb_t* arbol, void* elemento){
	return EXITO;
}

void* buscar_nodo(nodo_abb_t* raiz,void* elemento,abb_comparador comparador){
	if(!raiz){
		return NULL;
	}

	int comparacion = comparador(elemento,raiz->elemento);

	if(comparacion == 0){
		return raiz->elemento;
	}
	if(comparacion > 0){
		buscar_nodo(raiz->derecha,elemento,comparador);
	}else{
		buscar_nodo(raiz->derecha,elemento,comparador);
	}
}
/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación).
 *
 * Devuelve el elemento encontrado o NULL si no lo encuentra.
 */
void* arbol_buscar(abb_t* arbol, void* elemento){
	if(arbol_vacio) return NULL;
	return buscar_nodo(arbol->nodo_raiz,elemento,arbol->comparador);
}

/*
 * Devuelve el elemento almacenado como raiz o NULL si el árbol está
 * vacío o no existe.
 */
void* arbol_raiz(abb_t* arbol){
	if(arbol_vacio) return NULL;
	return arbol->nodo_raiz;
}

/*
 * Determina si el árbol está vacío.
 * Devuelve true si está vacío o el arbol es NULL, false si el árbol tiene elementos.
 */
bool arbol_vacio(abb_t* arbol){
    if(!arbol) return true;
    return ((!arbol->nodo_raiz)||(!arbol->comparador));
}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia inorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
	return 0;
}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia preorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
	return 0;
}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia postorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
	return 0;
}

void destruir_nodos(nodo_abb_t* raiz,abb_liberar_elemento destructor){
    if(!raiz) return;
    destruir_nodos(raiz->izquierda,destructor);  //Postorden
    destruir_nodos(raiz->derecha,destructor);

    if(!destructor) destructor(raiz->elemento);
    free(raiz);
}
/*
 * Destruye el arbol liberando la memoria reservada por el mismo.
 * Adicionalmente invoca el destructor con cada elemento presente en
 * el arbol.
 */
void arbol_destruir(abb_t* arbol){
    if(arbol_vacio(arbol)) return;
	destruir_nodos(arbol->nodo_raiz,arbol->destructor);
}

/*
 * Iterador interno. Recorre el arbol e invoca la funcion con cada
 * elemento del mismo. El puntero 'extra' se pasa como segundo
 * parámetro a la función. Si la función devuelve true, se finaliza el
 * recorrido aun si quedan elementos por recorrer. Si devuelve false
 * se sigue recorriendo mientras queden elementos.
 * El recorrido se realiza de acuerdo al recorrido solicitado.  Los
 * recorridos válidos son: ABB_RECORRER_INORDEN, ABB_RECORRER_PREORDEN
 * y ABB_RECORRER_POSTORDEN.
 * Devuelve la cantidad de elementos que fueron recorridos.
*/

bool recorrido_valido(int recorrido){
	return ((recorrido == ABB_RECORRER_INORDEN)||(recorrido == ABB_RECORRER_PREORDEN)||(recorrido == ABB_RECORRER_POSTORDEN));
}

size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
	if(!recorrido_valido(recorrido)) return 0;

	return 0;

}