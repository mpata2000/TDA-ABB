#include "pa2mm.h"
#include "abb.h"

#define EXITO 0
#define ERROR -1

void pruebas_null(){
    pa2m_afirmar(arbol_crear(NULL,NULL) == NULL,"No se puede crear un arbol sin comparador.");
    pa2m_afirmar(arbol_insertar(NULL,NULL) == ERROR,"Insertar en un arbol nulo da ERROR.");
    pa2m_afirmar(arbol_borrar(NULL,NULL) == ERROR,"Borrar en un arbol nulo da ERROR.");
    pa2m_afirmar(arbol_buscar(NULL,NULL) == NULL,"Buscar en un arbol nulo devuelve NULL.");
    pa2m_afirmar(arbol_raiz(NULL) == NULL,"Buscar la raiz en un arbol nulo devuelve NULL.");
    pa2m_afirmar(arbol_vacio(NULL),"Arbol nulo esta vacio.");
}

int main(){




    return 0;
}