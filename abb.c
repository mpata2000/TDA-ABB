#include "abb.h"

#define EXITO 0
#define ERROR -1

typedef struct vector{
	void** array;
	size_t contador;
	size_t tamanio;
}vector_t;

/*------------------------------------*/
/*        Crear y Liberar Nodo        */
/*------------------------------------*/

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
 * Recive un nodo y un destructor del elemento.
 * Si hay que liberar el elemento lo libera y despues libera el nodo 
*/
void liberar_nodo(nodo_abb_t* nodo,abb_liberar_elemento destructor){
	if(!nodo) return;
	if(destructor) destructor(nodo->elemento);	
    free(nodo);
}

/*---------------------------*/
/*        Crear Arbol        */
/*---------------------------*/

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
    if(!comparador) return NULL;

    abb_t* arbol = calloc(1,sizeof(abb_t));
    arbol->comparador = comparador;
    arbol->destructor = destructor;
    return arbol;
}


/*-----------------------------*/
/*        Insertar Nodo        */
/*-----------------------------*/

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


int arbol_insertar(abb_t* arbol, void* elemento){
	if(!arbol) return ERROR;
	int retorno = ERROR;
	arbol->nodo_raiz = insertar_nodo_arbol(arbol->nodo_raiz,elemento,arbol->comparador,&retorno);

	return retorno;

}

/*---------------------------*/
/*        Borrar Nodo        */
/*---------------------------*/


/*
 * Pre: Recive un nodo no nulo
 * Post: Devuelve true si el nodo tiene almenos un hijo
 */
bool no_tiene_hijos(nodo_abb_t* raiz){
	return ((!raiz->derecha)&&(!raiz->izquierda));
}

/*
 * Pre: Recive un nodo no nulo
 * Post: Devuelve true si el nodo tiene dos hijos
*/
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
 * Recive un nodo raiz y su arbol valido, el elemento que se quiere borrar
 * y un retorno iniciado como ERROR.
 * Se busca el nodo que se quiere borrar de forma recursiva:
 *   -Si no se encuentra retorno no se actualiza.
 *   -Si se encuentra se actualiza retorno a EXITO y si:
 *      ·No tiene hijos, libero el nodo
 *      ·Si tiene un hijo,libero el nodo y devuelvo el hijo no nulo.
 *      ·Si tiene dos hijos, libero el elemento y lo remplazo con el elemento predecesor inorden
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


/*---------------------------*/
/*        Buscar Nodo        */
/*---------------------------*/

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

void* arbol_buscar(abb_t* arbol, void* elemento){
	if(arbol_vacio(arbol)) return NULL;
	return buscar_nodo(arbol->nodo_raiz,elemento,arbol->comparador);
}


/*---------------------------*/
/*        Arbol Raiz         */
/*---------------------------*/

void* arbol_raiz(abb_t* arbol){
	if(arbol_vacio(arbol)) return NULL;
	return arbol->nodo_raiz->elemento;
}

/*---------------------------*/
/*        Arbol vacio        */
/*---------------------------*/

bool arbol_vacio(abb_t* arbol){
    if(!arbol) return true;
    return ((!arbol->nodo_raiz));
}

/*------------------------------------*/
/*        Recorridos Recursivos       */
/*------------------------------------*/

/*
 * Recive un nodo raiz, una funcion valida,un extra mandado por el usuario,
 * un contador y un estado inicializado en false.
 * Recorre el arbol en inorden de forma recursiva y se corta cuando se 
 * hayan recorrido todos los nodos o la funcion deuvelva true.
 * Por cada vez que se entre a la funcion el contador aumenta en 1
 * y el estado es igualado al retorno de la funcion.
*/
void recorrido_inorden(nodo_abb_t* raiz,bool (*funcion)(void*,void*),void* extra,size_t* contador,bool* estado){
	if(!raiz||*estado) return;
	recorrido_inorden(raiz->izquierda,funcion,extra,contador,estado);
	if(!(*estado)){
		(*estado) = funcion(raiz->elemento,extra);
		(*contador)++;
	}
	recorrido_inorden(raiz->derecha,funcion,extra,contador,estado);
}

/*
 * Recive un nodo raiz, una funcion valida,un extra mandado por el usuario,
 * un contador y un estado inicializado en false.
 * Recorre el arbol en preorden de forma recursiva y se corta cuando se 
 * hayan recorrido todos los nodos o la funcion deuvelva true.
 * Por cada vez que se entre a la funcion el contador aumenta en 1
 * y el estado es igualado al retorno de la funcion.
*/
void recorrido_preorden(nodo_abb_t* raiz,bool (*funcion)(void*,void*),void* extra,size_t* contador,bool* estado){
	if(!raiz||*estado) return;
	if(!(*estado)){
		(*estado) = funcion(raiz->elemento,extra);
		(*contador)++;
	}
	recorrido_preorden(raiz->izquierda,funcion,extra,contador,estado);
	recorrido_preorden(raiz->derecha,funcion,extra,contador,estado);
}

/*
 * Recive un nodo raiz, una funcion valida,un extra mandado por el usuario,
 * un contador y un estado inicializado en false.
 * Recorre el arbol en postorden de forma recursiva y se corta cuando se 
 * hayan recorrido todos los nodos o la funcion deuvelva true.
 * Por cada vez que se entre a la funcion el contador aumenta en 1
 * y el estado es igualado al retorno de la funcion.
*/
void recorrido_postorden(nodo_abb_t* raiz,bool (*funcion)(void*,void*),void* extra,size_t* contador,bool* estado){
	if(!raiz||*estado) return;
	recorrido_postorden(raiz->izquierda,funcion,extra,contador,estado);
	recorrido_postorden(raiz->derecha,funcion,extra,contador,estado);  
	if(!(*estado)){
		(*estado) = funcion(raiz->elemento,extra);
		(*contador)++;
	}
}

/*-------------------------------*/
/*        Recorridos Arbol       */
/*-------------------------------*/

/*
 * La funcion recive el elemento que se quiere agregar y un vecto_t
 * Si el contador es mayor igual al tamanio devuelve true
 * Sino agrega el elemento en el tope del vector y se amuenta en uno el tope
 * tope == contador 
*/
bool funcion_llenar_array_iterador(void* elemento,void* extra){
	if(((vector_t*)extra)->contador >= ((vector_t*)extra)->tamanio) return true;
	((vector_t*)extra)->array[((vector_t*)extra)->contador] = elemento;
	(((vector_t*)extra)->contador)++;
	return false;
}

/*
 * Recive un vector_t y lo inicializa con los valores dados 
 * y contador en 0
*/
void inicializar_vector_t(vector_t* vector,size_t tamanio,void** array){
	vector->array=array;
	vector->tamanio = tamanio;
	vector->contador=0;
}

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(arbol_vacio(arbol)||!tamanio_array||!array) return 0;
	size_t aux = 0;  //Auxiliar para que funcione recorrido
	bool estado=false;
	vector_t vector;
	inicializar_vector_t(&vector,tamanio_array,array);
	recorrido_inorden(arbol->nodo_raiz,funcion_llenar_array_iterador,&vector,&aux,&estado);
	return vector.contador;
}

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(arbol_vacio(arbol)||!tamanio_array||!array) return 0;
	size_t aux = 0;  //Auxiliar para que funcione recorrido
	bool estado=false;
	vector_t vector;
	inicializar_vector_t(&vector,tamanio_array,array);
	recorrido_preorden(arbol->nodo_raiz,funcion_llenar_array_iterador,&vector,&aux,&estado);
	return vector.contador;
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(arbol_vacio(arbol)||!tamanio_array||!array) return 0;
	size_t aux = 0;  //Auxiliar para que funcione recorrido
	bool estado=false;
	vector_t vector;
	inicializar_vector_t(&vector,tamanio_array,array);
	recorrido_postorden(arbol->nodo_raiz,funcion_llenar_array_iterador,&vector,&aux,&estado);
	return vector.contador;
}

/*-------------------------------*/
/*        Destruir Arbol         */
/*-------------------------------*/

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

/*--------------------------------*/
/*        Iterador Interno        */
/*--------------------------------*/

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