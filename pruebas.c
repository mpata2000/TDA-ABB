#include "pa2mm.h"
#include "abb.h"

#define EXITO 0
#define ERROR -1

typedef struct id_persona{
    int id;
    int edad;  
}id_persona_t;

/*
 * Comparador de elementos. Recibe dos elementos del arbol y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
 */
int comparador_de_numeros(id_persona_t* elemento_1,id_persona_t* elemento_2){
    if(elemento_1->id > elemento_2->id){
        return 1;
    }else if(elemento_1->id < elemento_2->id){
       return -1;
    }
    return 0;
}

void destruir_id(id_persona_t* persona){
    free(persona);
}

id_persona_t* crear_id(int id,int edad){
    id_persona_t* persona = malloc(sizeof(id_persona_t));
    if(!persona) return NULL;
    
    persona->id = id;
    persona->edad = edad;
    return persona;
}



void pruebas_null(){
    pa2m_afirmar(arbol_insertar(NULL,NULL) == ERROR,"Insertar en un arbol nulo da ERROR.");
    pa2m_afirmar(arbol_borrar(NULL,NULL) == ERROR,"Borrar en un arbol nulo da ERROR.");
    pa2m_afirmar(arbol_buscar(NULL,NULL) == NULL,"Buscar en un arbol nulo devuelve NULL.");
    pa2m_afirmar(arbol_raiz(NULL) == NULL,"Buscar la raiz en un arbol nulo devuelve NULL.");
    pa2m_afirmar(arbol_vacio(NULL),"Arbol nulo esta vacio.");
    pa2m_afirmar(!arbol_recorrido_inorden(NULL,NULL,NULL),"Recorrido arbol inorden de un arbol nulo devuelve 0.");
    pa2m_afirmar(!arbol_recorrido_postorden(NULL,NULL,NULL),"Recorrido arbol postorden de un arbol nulo devuelve 0.");
    pa2m_afirmar(!arbol_recorrido_preorden(NULL,NULL,NULL),"Recorrido arbol preordeninorden de un arbol nulo devuelve 0.");
    pa2m_afirmar(!abb_con_cada_elemento(NULL,NULL,NULL,NULL),"NO se puede recorrec cada elemento de un arbol nulo(devuelve 0).");
}

void pruebas_crear(){
    pa2m_afirmar(arbol_crear(NULL,NULL) == NULL,"No se puede crear un arbol sin comparador.");
    abb_t* arbol = arbol_crear(comparador_de_numeros,NULL);
    pa2m_afirmar(arbol != NULL,"Se puede crear un arbol sin destructor.");
    arbol_destruir(arbol);

    arbol = arbol_crear(comparador_de_numeros,destruir_id);
    pa2m_afirmar(arbol!= NULL,"Se puede crear un arbol con destructor.");
    arbol_destruir(arbol);
}

void pruebas_insertar(){
    abb_t* arbol = arbol_crear(comparador_de_numeros,destruir_id);
    id_persona_t* id[10];
    for(int i=0;i<10;i++){
        id[i] = crear_id(i,i);
    }

    pa2m_afirmar(arbol_vacio(arbol),"Arbol creado esta vacio");
    pa2m_afirmar(arbol_insertar(arbol,id[4])==EXITO,"Se puede insertar un elemento"); // id 4
    pa2m_afirmar(!arbol_vacio(arbol),"Arbol no esta vacio");
    pa2m_afirmar(arbol_insertar(arbol,id[2])==EXITO,"Se puede insertar un elemento"); // id 2
    pa2m_afirmar(arbol_insertar(arbol,id[3])==EXITO,"Se puede insertar un elemento"); // id 3
    pa2m_afirmar(arbol_insertar(arbol,id[0])==EXITO,"Se puede insertar un elemento"); // id 0
    pa2m_afirmar(arbol_insertar(arbol,id[1])==EXITO,"Se puede insertar un elemento"); // id 1
    pa2m_afirmar(arbol_insertar(arbol,id[7])==EXITO,"Se puede insertar un elemento"); // id 7
    pa2m_afirmar(arbol_insertar(arbol,id[9])==EXITO,"Se puede insertar un elemento"); // id 9
    pa2m_afirmar(arbol_insertar(arbol,id[5])==EXITO,"Se puede insertar un elemento"); // id 5
    pa2m_afirmar(arbol_insertar(arbol,id[6])==EXITO,"Se puede insertar un elemento"); // id 6
    pa2m_afirmar(arbol_insertar(arbol,id[8])==EXITO,"Se puede insertar un elemento"); // id 6
    pa2m_afirmar(arbol_insertar(arbol,id[4])==EXITO,"Se puede insertar un elemento repetido"); // id 4


    arbol_destruir(arbol);
    
}

int main(){




    return 0;
}