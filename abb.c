#include "abb.h"

#define EXITO 0
#define ERROR -1

/*
 * Recive un nodo y un destructor del elemento.
 * Si hay que liberar el elemento lo libera y despues libera el nodo 
*/
void liberar_nodo(nodo_abb_t* nodo,abb_liberar_elemento destructor){
	if(!nodo) return;
	if(destructor) destructor(nodo->elemento);	
    free(nodo);
}

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

/*
 * Recive un elemento y un int retorno por referencia
 * Se crea un nodo_abb_t:
 *         Si falla en retorno se carga con -1 y devuelve NULL
 *         Si se crea en retorno se carga con 0 y se devuelve el nuevo nodo con el elemento
*/
nodo_abb_t* crear_nodo(void* elemento,int* retorno){
	nodo_abb_t* nodo = calloc(1,sizeof(nodo_abb_t));
	if(!nodo){
		*retorno = ERROR;
		return NULL;
	}
	*retorno = EXITO;
	nodo->elemento = elemento;
	return nodo;
}

/*
 * Recive un nodo valido, el elemento a insertar, el comparador del abb y elvalor de retorno de la funcion
 * Se va conparando el elemento hasta llegar a un nodo NULL
 * Se inserta el nuevo nodo como hoja y se carga en retono si fallo(-1) o funciono(0).
 */
nodo_abb_t* insertar_nodo_arbol(nodo_abb_t* raiz,void* elemento,abb_comparador comparador,int* retorno){
	if(!raiz){
		raiz = crear_nodo(elemento,retorno);
		return raiz;
	}

	if(comparador(elemento,raiz->elemento) > 0){
		raiz->derecha = insertar_nodo_arbol(raiz->derecha,elemento,comparador,retorno);
	}else{
		raiz->izquierda = insertar_nodo_arbol(raiz->izquierda,elemento,comparador,retorno);
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
	int retorno = ERROR;
	arbol->nodo_raiz = insertar_nodo_arbol(arbol->nodo_raiz,elemento,arbol->comparador,&retorno);

	return retorno;

}

/*
 * Pre: Recive un nodo no nulo
 * Post: Devuelve true si el nodo tiene almenos un hijo
 */
bool no_tiene_hijos(nodo_abb_t* raiz){
	return ((!raiz->derecha)&&(!raiz->izquierda));
}

//Pre: Recive un nodo no nulo
//Post: Devuelve true si el nodo tiene dos hijos
bool tiene_dos_hijos(nodo_abb_t* raiz){
	return ((raiz->derecha)&&(raiz->izquierda));
}

/*
 * Busca el predecesor inorden recursivamente reciviendo 
 * un nodo hijo izquierdo valido y un *elemento por referencia.
 * Cuando se llega al predecesor inorden se gurada el elemento
 * y se libera el nodo.
 */
nodo_abb_t* predecesor_inorden(nodo_abb_t* raiz,void** elemento){
	if(!raiz->derecha){
		nodo_abb_t* nodo_aux=(raiz->izquierda)?raiz->izquierda:NULL;
		*elemento = raiz->elemento;
		free(raiz);
		return nodo_aux;
	}

	raiz->derecha = predecesor_inorden(raiz->derecha,elemento);
	return raiz;
}

/*
 * 
 */
nodo_abb_t* borrar_nodo(nodo_abb_t* raiz,void* elemento,abb_t* arbol,int* retono){
	if(!raiz) return NULL; //No se encontro
	
	int comparacion = arbol->comparador(elemento,raiz->elemento);

	if(comparacion == 0){
		(*retono) = EXITO;
		if(no_tiene_hijos(raiz)){
			liberar_nodo(raiz,arbol->destructor); //Lo libero y esta

			return NULL;
		}else if (tiene_dos_hijos(raiz)){
			if(arbol->destructor) arbol->destructor(raiz->elemento);
			raiz->izquierda = predecesor_inorden(raiz->izquierda,&raiz->elemento);   //Busco el predecesor inorden gurado su elemento y libero el nodo
			return raiz;
		}

		nodo_abb_t* nodo_hijo = (raiz->derecha)?raiz->derecha:raiz->izquierda;
		liberar_nodo(raiz,arbol->destructor);
		return nodo_hijo;
	}

	if(comparacion > 0){
		raiz->derecha = borrar_nodo(raiz->derecha,elemento,arbol,retono);
	}else if(comparacion < 0){
		raiz->izquierda = borrar_nodo(raiz->izquierda,elemento,arbol,retono);
	}
	return raiz;
}

/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación) y si lo encuentra lo quita del arbol.
 * Adicionalmente, si encuentra el elemento, invoca el destructor con
 * dicho elemento.
 * Devuelve 0 si pudo eliminar el elemento o -1 en caso contrario.
 */
int arbol_borrar(abb_t* arbol, void* elemento){
	if(arbol_vacio(arbol)) return ERROR;
	int retorno = ERROR;

	arbol->nodo_raiz = borrar_nodo(arbol->nodo_raiz,elemento,arbol,&retorno);	
	return retorno;
}

/*
 * Busca de forma recursiva si en el arbol hay un elemento igual con la 
 * funcion comparadora dada.
 * Si lo encuenra devuelve el elemento en el nodo, sino devuelve NULL.
 */
void* buscar_nodo(nodo_abb_t* raiz,void* elemento,abb_comparador comparador){
	if(!raiz) return NULL;
	
	int comparacion = comparador(elemento,raiz->elemento);
	
	if(comparacion > 0){
		return buscar_nodo(raiz->derecha,elemento,comparador);
	}else if(comparacion < 0){
		return buscar_nodo(raiz->izquierda,elemento,comparador);
	}

	return raiz->elemento;
}

/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación).
 *
 * Devuelve el elemento encontrado o NULL si no lo encuentra.
 */
void* arbol_buscar(abb_t* arbol, void* elemento){
	if(arbol_vacio(arbol)) return NULL;
	return buscar_nodo(arbol->nodo_raiz,elemento,arbol->comparador);
}

/*
 * Devuelve el elemento almacenado como raiz o NULL si el árbol está
 * vacío o no existe.
 */
void* arbol_raiz(abb_t* arbol){
	if(arbol_vacio(arbol)) return NULL;
	return arbol->nodo_raiz->elemento;
}

/*
 * Determina si el árbol está vacío.
 * Devuelve true si está vacío o el arbol es NULL, false si el árbol tiene elementos.
 */
bool arbol_vacio(abb_t* arbol){
    if(!arbol) return true;
    return ((!arbol->nodo_raiz));
}

/*        Recorridos llenar vector        */

void llenar_array_inorden(nodo_abb_t* raiz,void* array[],size_t* contador, size_t tamanio){
	if(!raiz||((tamanio <= (*contador)))) return;
	llenar_array_inorden(raiz->izquierda,array,contador, tamanio);
	if(*contador < tamanio){
		array[*contador] = raiz->elemento;
		(*contador)++;
	}
	llenar_array_inorden(raiz->derecha,array,contador, tamanio);
}

void llenar_array_preorden(nodo_abb_t* raiz,void* array[],size_t* contador, size_t tamanio){
	if(!raiz||((tamanio <= (*contador)))) return;
	if(*contador < tamanio){
		array[*contador] = raiz->elemento;
		(*contador)++;
	}
	llenar_array_preorden(raiz->izquierda,array,contador, tamanio);
	llenar_array_preorden(raiz->derecha,array,contador, tamanio);
}

void llenar_array_postorden(nodo_abb_t* raiz,void* array[],size_t* contador, size_t tamanio){
	if(!raiz||((tamanio <= (*contador)))) return;
	llenar_array_postorden(raiz->izquierda,array,contador, tamanio);
	llenar_array_postorden(raiz->derecha,array,contador, tamanio);
	if(*contador < tamanio){
		array[*contador] = raiz->elemento;
		(*contador)++;
	}
}

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(arbol_vacio(arbol)||!tamanio_array||!array) return 0;
	size_t contador = 0;
	llenar_array_inorden(arbol->nodo_raiz,array,&contador, tamanio_array);

	return contador;
}

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(arbol_vacio(arbol)||!tamanio_array||!array) return 0;
	size_t contador = 0;
	llenar_array_preorden(arbol->nodo_raiz,array,&contador, tamanio_array);

	return contador;
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(arbol_vacio(arbol)||!tamanio_array||!array) return 0;
	size_t contador = 0;
	llenar_array_postorden(arbol->nodo_raiz,array,&contador, tamanio_array);

	return contador;
}

/*
 * Recive una raiz y un destructor de raiz->elemento
 * Si la raiz es nula no ocurre nada.
 * Si no lo es, va recorriendo el arbol con un recorrido postorden
 * cuando llega a una hoja, chequea si tiene que liberar el elemento
 * y libera el nodo, recursivamente hata liberar todo el arbol.
 */
void destruir_nodos(nodo_abb_t* raiz,abb_liberar_elemento destructor){
    if(!raiz) return;
    destruir_nodos(raiz->izquierda,destructor);  //Postorden
    destruir_nodos(raiz->derecha,destructor);
    liberar_nodo(raiz,destructor);
}

/*
 * Destruye el arbol liberando la memoria reservada por el mismo.
 * Adicionalmente invoca el destructor con cada elemento presente en
 * el arbol.
 */
void arbol_destruir(abb_t* arbol){
    if(arbol == NULL) return;
	destruir_nodos(arbol->nodo_raiz,arbol->destructor);
	free(arbol);
}


/*        Recorridos iterador interno        */

void recorrido_inorden(nodo_abb_t* raiz,bool (*funcion)(void*,void*),void* extra,size_t* contador,bool* estado){
	if(!raiz||*estado) return;
	recorrido_inorden(raiz->izquierda,funcion,extra,contador,estado);
	if(!(*estado)){
		(*estado) = funcion(raiz->elemento,extra);
		(*contador)++;
	}
	recorrido_inorden(raiz->derecha,funcion,extra,contador,estado);
}

void recorrido_preorden(nodo_abb_t* raiz,bool (*funcion)(void*,void*),void* extra,size_t* contador,bool* estado){
	if(!raiz||*estado) return;
	if(!(*estado)){
		(*estado) = funcion(raiz->elemento,extra);
		(*contador)++;
	}
	recorrido_preorden(raiz->izquierda,funcion,extra,contador,estado);
	recorrido_preorden(raiz->derecha,funcion,extra,contador,estado);
}

void recorrido_postorden(nodo_abb_t* raiz,bool (*funcion)(void*,void*),void* extra,size_t* contador,bool* estado){
	if(!raiz||*estado) return;
	recorrido_postorden(raiz->izquierda,funcion,extra,contador,estado);
	recorrido_postorden(raiz->derecha,funcion,extra,contador,estado);  
	if(!(*estado)){
		(*estado) = funcion(raiz->elemento,extra);
		(*contador)++;
	}
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
size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
	if(arbol_vacio(arbol)||!funcion) return 0;
	bool estado=false;
	size_t contador=0;

	switch (recorrido){
		case ABB_RECORRER_INORDEN:
			recorrido_inorden(arbol->nodo_raiz,funcion,extra,&contador,&estado);
			break;

		case ABB_RECORRER_POSTORDEN:
			recorrido_postorden(arbol->nodo_raiz,funcion,extra,&contador,&estado);
			break;

		case ABB_RECORRER_PREORDEN:
			recorrido_preorden(arbol->nodo_raiz,funcion,extra,&contador,&estado);
			break;

		default:
			break;
	}

	return contador;
}