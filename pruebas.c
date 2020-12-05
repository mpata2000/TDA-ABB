#include "pa2mm.h"
#include "abb.h"
#include "abb_minipruebas.h"

#define EXITO 0
#define ERROR -1
#define MAX_PRUEBA_VOL 10000
#define MAX_PRUEBAS_INSERTAR 6
#define MAX_INSERTADO 10
#define MAYOR 1
#define MENOR -1
#define IGUALES 0

typedef struct id_persona{
    int id;
    int edad;  
}id_persona_t;

/*
 * Comparador de elementos. Recibe dos elementos del arbol y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
 */
int comparador_de_numeros(void* elemento_1,void* elemento_2){
    if(!elemento_1) return MENOR;
    if(!elemento_2) return MAYOR;
    if(((id_persona_t*)elemento_1)->id > ((id_persona_t*)elemento_2)->id){
        return MAYOR;
    }else if(((id_persona_t*)elemento_1)->id < ((id_persona_t*)elemento_2)->id){
       return MENOR;
    }
    return IGUALES;
}

void destruir_id(void* persona){
    if(!(id_persona_t*)persona) return;  

    free((id_persona_t*)persona);
}

id_persona_t* crear_id(int id,int edad){
    id_persona_t* persona = malloc(sizeof(id_persona_t));
    if(!persona) return NULL;
    
    persona->id = id;
    persona->edad = edad;
    return persona;
}

/*
 * Recive un arbol creado valido, con comparador y destructor de id_persona_t,
 * y un vector de id_persona_t*.
 * Crea los ids, los guarda en el vector y los inserta en el arbol de forma balanceada.
*/
abb_t* insertar_id_arbol(abb_t* arbol, id_persona_t** ids){
    for(int i=0;i<MAX_INSERTADO;i++){
        ids[i]=crear_id(i,i);
    }
    arbol_insertar(arbol,ids[5]);
    arbol_insertar(arbol,ids[3]);
    arbol_insertar(arbol,ids[1]);
    arbol_insertar(arbol,ids[0]);
    arbol_insertar(arbol,ids[2]);
    arbol_insertar(arbol,ids[4]);
    arbol_insertar(arbol,ids[8]);
    arbol_insertar(arbol,ids[7]);
    arbol_insertar(arbol,ids[6]);
    arbol_insertar(arbol,ids[9]);

    /*                     5
     *                   /   \
     *                  3     8
     *                 / \   / \
     *                1  4   7  9
     *               / \    /
     *              0   2  6
    */
    return arbol;
}

abb_t* crear_arbol_de_ids(id_persona_t** id){
    abb_t* arbol = arbol_crear(comparador_de_numeros,destruir_id);
    arbol = insertar_id_arbol(arbol,id);
    return arbol;
}

void pruebas_null(){
    pa2m_afirmar(arbol_insertar(NULL,NULL) == ERROR,"Insertar en un arbol nulo da ERROR.");
    pa2m_afirmar(arbol_borrar(NULL,NULL) == ERROR,"Borrar en un arbol nulo da ERROR.");
    pa2m_afirmar(arbol_buscar(NULL,NULL) == NULL,"Buscar en un arbol nulo devuelve NULL.");
    pa2m_afirmar(arbol_raiz(NULL) == NULL,"Buscar la raiz en un arbol nulo devuelve NULL.");
    pa2m_afirmar(arbol_vacio(NULL),"Arbol nulo esta vacio.");
    pa2m_afirmar(!arbol_recorrido_inorden(NULL,NULL,0),"Recorrido arbol inorden de un arbol nulo devuelve 0.");
    pa2m_afirmar(!arbol_recorrido_postorden(NULL,NULL,0),"Recorrido arbol postorden de un arbol nulo devuelve 0.");
    pa2m_afirmar(!arbol_recorrido_preorden(NULL,NULL,0),"Recorrido arbol preordeninorden de un arbol nulo devuelve 0.");
    pa2m_afirmar(!abb_con_cada_elemento(NULL,0,NULL,NULL),"NO se puede recorrer cada elemento de un arbol nulo(devuelve 0).");
}

void pruebas_crear(){
    pa2m_afirmar(arbol_crear(NULL,NULL) == NULL,"No se puede crear un arbol sin comparador.");
    abb_t* arbol = arbol_crear(comparador_de_numeros,NULL);
    pa2m_afirmar(arbol != NULL,"Se puede crear un arbol sin destructor.");
    pa2m_afirmar(arbol_vacio(arbol),"Arbol creado esta vacio");
    arbol_destruir(arbol);

    arbol = arbol_crear(comparador_de_numeros,destruir_id);
    pa2m_afirmar(arbol!= NULL,"Se puede crear un arbol con destructor.");
    pa2m_afirmar(arbol_vacio(arbol),"Arbol creado esta vacio");
    arbol_destruir(arbol);
}

void pruebas_insertar(){
    abb_t* arbol = arbol_crear(comparador_de_numeros,destruir_id);
    id_persona_t* id[MAX_PRUEBAS_INSERTAR];
    for(int i=0;i<MAX_PRUEBAS_INSERTAR;i++){
        id[i] = crear_id(i,i);
    }

    pa2m_afirmar(arbol_vacio(arbol),"Arbol creado esta vacio");
    pa2m_afirmar(arbol_insertar(arbol,id[4])==EXITO,"Se puede insertar el primer elemento");     
    pa2m_afirmar((id_persona_t*)arbol_raiz(arbol)==id[4],"La raiz es la correcta");
    pa2m_afirmar(!arbol_vacio(arbol),"Arbol no esta vacio");
    pa2m_afirmar(arbol_insertar(arbol,id[2])==EXITO,"Se puede insertar un elemento");          
    pa2m_afirmar(arbol->nodo_raiz->izquierda->elemento==id[2],"Se inserto a la izquierda de la raiz");          
    pa2m_afirmar(arbol_insertar(arbol,id[3])==EXITO,"Se puede insertar un elemento");
    pa2m_afirmar(arbol->nodo_raiz->izquierda->derecha->elemento==id[3],"Se inserto a la derecha del anterior");          
    pa2m_afirmar(arbol_insertar(arbol,id[0])==EXITO,"Se puede insertar un elemento");
    pa2m_afirmar(arbol->nodo_raiz->izquierda->izquierda->elemento==id[0],"Se inserto como primer inorden");          
    pa2m_afirmar(arbol_insertar(arbol,id[1])==EXITO,"Se puede insertar un elemento");  
    pa2m_afirmar(arbol->nodo_raiz->izquierda->izquierda->derecha->elemento==id[1],"Se inserto a la derecha del anterior");          
    pa2m_afirmar(arbol_insertar(arbol,id[5])==EXITO,"Se puede insertar un elemento");          
    pa2m_afirmar(arbol->nodo_raiz->derecha->elemento==id[5],"Se inserto a la derecha de la raiz");          
    id_persona_t* id_aux = crear_id(5,0);
    pa2m_afirmar(arbol_insertar(arbol,id_aux)==EXITO,"Se puede insertar un elemento con la misma \"clave\"");
    pa2m_afirmar(arbol->nodo_raiz->derecha->izquierda->elemento==id_aux,"Se inserto a la izquierda del anterior");                

    pa2m_afirmar(arbol_insertar(arbol,NULL)==EXITO,"Se puede insertar un elemento NULL");

    arbol_destruir(arbol);   //Pruebo que borrar libere todo
}

void pruebas_buscar(){
    id_persona_t* id[MAX_INSERTADO];
    id_persona_t* id_aux = crear_id(0,0);
    abb_t* arbol = crear_arbol_de_ids(id);
    pa2m_afirmar(arbol_raiz(arbol)==id[5],"Arbol raiz devuelve la raiz");
    for (int i = 0; i < 10; i++){
        id_aux->id = i;
        pa2m_afirmar(arbol_buscar(arbol,id_aux) == id[i],"Se puede encontrar elemento insertado");
    }
    id_aux->id = MAX_INSERTADO+1;
    pa2m_afirmar(arbol_buscar(arbol,id_aux) == NULL,"Buscar elemento no insertado devuelve NULL");
    destruir_id(id_aux);
    arbol_destruir(arbol);
}

/*
 * Llega un vectorde id_persona_t* y carga con NULL
 * cada posicion hasta el tope
*/
void limpiar_vetor_id(id_persona_t** ids,int tope){
    for (int i = 0; i < tope; i++){
        ids[i]=NULL;
    }  
}

/*
 *LSe comparan los dos vectores hasta la cantidad recivida
 * SI se encuentra una diferencia devuelve false, si no true
*/
bool comparar_vectores(id_persona_t** id_aux,id_persona_t** id_orden,int cantidad){
    bool exito=true;
    for(int i=0;i<cantidad;i++){
        if(id_aux[i]!=id_orden[i]){
            exito=false;
        }
    }
    return exito;
}



void pruebas_recorrido(){
    id_persona_t* id_aux[MAX_INSERTADO];
    id_persona_t* id_inorden[MAX_INSERTADO];
    abb_t* arbol= crear_arbol_de_ids(id_inorden);
    id_persona_t* id_postorden[MAX_INSERTADO]={id_inorden[0],id_inorden[2],id_inorden[1],id_inorden[4],id_inorden[3],id_inorden[6],id_inorden[7],id_inorden[9],id_inorden[8],id_inorden[5]};
    id_persona_t* id_preorden[MAX_INSERTADO]={id_inorden[5],id_inorden[3],id_inorden[1],id_inorden[0],id_inorden[2],id_inorden[4],id_inorden[8],id_inorden[7],id_inorden[6],id_inorden[9]};

    pa2m_nuevo_grupo("Recorrido Inorden");
    pa2m_afirmar(!arbol_recorrido_inorden(arbol,NULL,0),"Recorrido arbol inorden sin vector devuelve 0.");
    pa2m_afirmar(arbol_recorrido_inorden(arbol,(void**)id_aux,MAX_INSERTADO)==MAX_INSERTADO,"Recorrido arbol inorden de todo el arbol devuelve la cantidad esperada.");
    pa2m_afirmar(comparar_vectores(id_aux,id_inorden,MAX_INSERTADO),"Los elementos estan en el orden correcto");
    limpiar_vetor_id(id_aux,MAX_INSERTADO);
    pa2m_afirmar(arbol_recorrido_inorden(arbol,(void**)id_aux,MAX_INSERTADO/2)==MAX_INSERTADO/2,"Recorrido arbol inorden de menos elementos devuelve la cantidad esperada.");
    pa2m_afirmar(comparar_vectores(id_aux,id_inorden,MAX_INSERTADO/2),"Los elementos estan en el orden correcto");
    limpiar_vetor_id(id_aux,MAX_INSERTADO);
    pa2m_afirmar(arbol_recorrido_inorden(arbol,(void**)id_aux,MAX_INSERTADO*2)==MAX_INSERTADO,"Recorrido arbol inorden de mas elementos que el arbol la cantidad esperada.");
    pa2m_afirmar(comparar_vectores(id_aux,id_inorden,MAX_INSERTADO),"Los elementos estan en el orden correcto");
    limpiar_vetor_id(id_aux,MAX_INSERTADO);

    pa2m_nuevo_grupo("Recorrido Postorden");
    pa2m_afirmar(!arbol_recorrido_postorden(arbol,NULL,0),"Recorrido arbol postorden sin vector devuelve 0.");
    pa2m_afirmar(arbol_recorrido_postorden(arbol,(void**)id_aux,MAX_INSERTADO)==MAX_INSERTADO,"Recorrido arbol postorden de todo el arbol devuelve la cantidad esperada.");
    pa2m_afirmar(comparar_vectores(id_aux,id_postorden,MAX_INSERTADO),"Los elementos estan en el orden correcto");
    limpiar_vetor_id(id_aux,MAX_INSERTADO);
    pa2m_afirmar(arbol_recorrido_postorden(arbol,(void**)id_aux,MAX_INSERTADO/2)==MAX_INSERTADO/2,"Recorrido arbol postorden de menos elementos devuelve la cantidad esperada.");
    pa2m_afirmar(comparar_vectores(id_aux,id_postorden,MAX_INSERTADO/2),"Los elementos estan en el orden correcto");
    limpiar_vetor_id(id_aux,MAX_INSERTADO);
    pa2m_afirmar(arbol_recorrido_postorden(arbol,(void**)id_aux,MAX_INSERTADO*2)==MAX_INSERTADO,"Recorrido arbol postorden de mas elementos que el arbol la cantidad esperada.");
    pa2m_afirmar(comparar_vectores(id_aux,id_postorden,MAX_INSERTADO),"Los elementos estan en el orden correcto");
    limpiar_vetor_id(id_aux,MAX_INSERTADO);

    pa2m_nuevo_grupo("Recorrido Preorden");
    pa2m_afirmar(!arbol_recorrido_preorden(arbol,NULL,0),"Recorrido arbol preorden sin vector devuelve 0.");
    pa2m_afirmar(arbol_recorrido_preorden(arbol,(void**)id_aux,MAX_INSERTADO)==MAX_INSERTADO,"Recorrido arbol preorden de todo el arbol devuelve la cantidad esperada.");
    pa2m_afirmar(comparar_vectores(id_aux,id_preorden,MAX_INSERTADO),"Los elementos estan en el orden correcto");
    limpiar_vetor_id(id_aux,MAX_INSERTADO);
    pa2m_afirmar(arbol_recorrido_preorden(arbol,(void**)id_aux,MAX_INSERTADO/2)==MAX_INSERTADO/2,"Recorrido arbol preorden de menos elementos devuelve la cantidad esperada.");
    pa2m_afirmar(comparar_vectores(id_aux,id_preorden,MAX_INSERTADO/2),"Los elementos estan en el orden correcto");
    limpiar_vetor_id(id_aux,MAX_INSERTADO);
    pa2m_afirmar(arbol_recorrido_preorden(arbol,(void**)id_aux,MAX_INSERTADO*2)==MAX_INSERTADO,"Recorrido arbol preorden de mas elementos que el arbol la cantidad esperada.");
    pa2m_afirmar(comparar_vectores(id_aux,id_preorden,MAX_INSERTADO),"Los elementos estan en el orden correcto");
    
    arbol_destruir(arbol);
}

bool funcion_iterador_orden(void* elemento, void* extra){
    if(*((int*)extra) != ((id_persona_t*)elemento)->id) return true;
    int* p_extra = (int*)extra;
    p_extra++;
    extra = p_extra;

    return false;
}
/*
 * Funcion para el iterador interno que itera la mitad de los elementos
 * El extra tiene que ser un (int*) y se le suma 1 cada vez que se llama la funcion
*/
bool funcion_iterador_cortar(void* elemento, void* extra){

    (*(int*)extra)++;
    if(*((int*)extra) == (MAX_INSERTADO/2)) return true;

    return false;
}
/*
 * Funcion para el iterador interno que itera todos los elementos
 * El extra tiene que ser un (int*) y se le suma 1 cada vez que se llama la funcion
*/
bool funcion_iterador(void* elemento, void* extra){
    if(extra){
        (*(int*)extra)++;
    }
    return false;
}

void pruebas_iterador_interno(){
    id_persona_t* ids[MAX_INSERTADO];
    abb_t* arbol= crear_arbol_de_ids(ids);
    int contador=0;
    int inorden[MAX_INSERTADO]={0,1,2,3,4,5,6,7,8,9};
    int* p_inorden = inorden;
    //int postorden[MAX_INSERTADO]={0,2,1,4,3,6,7,9,8,5};
    //int preorden[MAX_INSERTADO]={5,3,1,0,2,4,8,7,6,9};
    abb_con_cada_elemento(arbol,ABB_RECORRER_INORDEN,funcion_iterador_orden,p_inorden);

    pa2m_afirmar(!abb_con_cada_elemento(arbol,0,NULL,NULL),"NO se puede recorrer cada elemento sin funcion.");
    pa2m_afirmar(!abb_con_cada_elemento(arbol,-1,funcion_iterador,NULL),"NO se puede recorrer cada elemento sin recorrido valido.");
    pa2m_afirmar(abb_con_cada_elemento(arbol,ABB_RECORRER_INORDEN,funcion_iterador,NULL)==MAX_INSERTADO,"Se puede recorrer sin el extra.");

    pa2m_nuevo_grupo("Iterador Recorrido Inorden");
    pa2m_afirmar(abb_con_cada_elemento(arbol,ABB_RECORRER_INORDEN,funcion_iterador,&contador)==MAX_INSERTADO,"Se recorren la cantidad de elementos esperados.");
    pa2m_afirmar(contador==MAX_INSERTADO,"Se llama a la funcion la cantidad correcta")
    pa2m_afirmar(abb_con_cada_elemento(arbol,ABB_RECORRER_INORDEN,funcion_iterador_orden,p_inorden)==MAX_INSERTADO,"Se recorren los elementos en el orden correcto.");
    contador=0;
    pa2m_afirmar(abb_con_cada_elemento(arbol,ABB_RECORRER_INORDEN,funcion_iterador_cortar,&contador)==MAX_INSERTADO/2,"Se recorren la cantidad de elementos esperados sin la funcion devuelve true.");
    pa2m_afirmar(contador==(MAX_INSERTADO/2),"Se llama a la funcion la cantidad correcta")
    contador=0;

    pa2m_nuevo_grupo("Iterador Recorrido Postorden");
    pa2m_afirmar(abb_con_cada_elemento(arbol,ABB_RECORRER_POSTORDEN,funcion_iterador,&contador)==MAX_INSERTADO,"Se recorren la cantidad de elementos esperados.");
    pa2m_afirmar(contador==MAX_INSERTADO,"Se llama a la funcion la cantidad correcta")
    contador=0;
    pa2m_afirmar(abb_con_cada_elemento(arbol,ABB_RECORRER_POSTORDEN,funcion_iterador_cortar,&contador)==(MAX_INSERTADO/2),"Se recorren la cantidad de elementos esperados sin la funcion devuelve true.");
    pa2m_afirmar(contador==(MAX_INSERTADO/2),"Se llama a la funcion la cantidad correcta")
    contador=0;
    
    pa2m_nuevo_grupo("Iterador Recorrido Preorden");
    pa2m_afirmar(abb_con_cada_elemento(arbol,ABB_RECORRER_PREORDEN,funcion_iterador,&contador)==MAX_INSERTADO,"Se recorren la cantidad de elementos esperados.");
    pa2m_afirmar(contador==MAX_INSERTADO,"Se llama a la funcion la cantidad correcta")
    contador=0;
    pa2m_afirmar(abb_con_cada_elemento(arbol,ABB_RECORRER_PREORDEN,funcion_iterador_cortar,&contador)==(MAX_INSERTADO/2),"Se recorren la cantidad de elementos esperados sin la funcion devuelve true.");
    pa2m_afirmar(contador==(MAX_INSERTADO/2),"Se llama a la funcion la cantidad correcta")
    contador=0;

    arbol_destruir(arbol);
}

void pruebas_borrar(){
    id_persona_t* ids[MAX_INSERTADO];
    abb_t* arbol= crear_arbol_de_ids(ids);
    id_persona_t id_aux;
    /*                     5
     *                   /   \
     *                  3     8
     *                 / \   / \
     *                1  4   7  9
     *               / \    /
     *              0   2  6
    */
    pa2m_afirmar(arbol_borrar(arbol,NULL)==ERROR,"No se puede borrar un elemento que no esta en el arbol");
    pa2m_afirmar(arbol_borrar(arbol,ids[2])==EXITO,"Puedo borrar un nodo hoja");
    id_aux.id=2;
    pa2m_afirmar(!arbol_buscar(arbol,&id_aux),"El elemento ya no esta en el arbol");
    pa2m_afirmar(arbol_borrar(arbol,ids[1])==EXITO,"Puedo borrar un nodo con un hijo");
    id_aux.id=1;
    pa2m_afirmar(!arbol_buscar(arbol,&id_aux),"El elemento ya no esta en el arbol");
    pa2m_afirmar((id_persona_t*)arbol->nodo_raiz->izquierda->izquierda->elemento==ids[0],"Se remplazo con su hijo");
    /*                     5
     *                   /   \
     *                  3     8
     *                 / \   / \
     *                0   4 7   9
     *                     /
     *                    6
    */
    pa2m_afirmar(arbol_borrar(arbol,ids[8])==EXITO,"Puedo borrar un nodo con dos hijos");
    id_aux.id=8;
    pa2m_afirmar(!arbol_buscar(arbol,&id_aux),"El elemento ya no esta en el arbol");
    pa2m_afirmar((id_persona_t*)arbol->nodo_raiz->derecha->elemento==ids[7],"Se remplazo con el predecesor inorden");
    pa2m_afirmar((id_persona_t*)arbol->nodo_raiz->derecha->izquierda->elemento==ids[6],"Su hijo izquierdo es correcto");
    /*                     5
     *                   /   \
     *                  3     7
     *                 / \   / \
     *                0   4 6   9                 
    */
    pa2m_afirmar(arbol_borrar(arbol,ids[5])==EXITO,"Puedo borrar la raiz con dos hijos");
    id_aux.id=5;
    pa2m_afirmar(!arbol_buscar(arbol,&id_aux),"El elemento ya no esta en el arbol");
    pa2m_afirmar((id_persona_t*)arbol->nodo_raiz->elemento==ids[4],"Se remplazo con el predecesor inorden");

    pa2m_afirmar(arbol_borrar(arbol,arbol_raiz(arbol))==EXITO,"Puedo borrar otra vez la raiz con dos hijos");
    id_aux.id=4;
    pa2m_afirmar(!arbol_buscar(arbol,&id_aux),"El elemento ya no esta en el arbol");
    pa2m_afirmar((id_persona_t*)arbol->nodo_raiz->elemento==ids[3],"Se remplazo con el predecesor inorden");

    pa2m_afirmar(arbol_borrar(arbol,arbol_raiz(arbol))==EXITO,"Puedo borrar la raiz con dos hijos otra vez");
    id_aux.id=3;
    pa2m_afirmar(!arbol_buscar(arbol,&id_aux),"El elemento ya no esta en el arbol");
    pa2m_afirmar((id_persona_t*)arbol->nodo_raiz->elemento==ids[0],"Se remplazo con el predecesor inorden");
    /*           0
     *            \
     *             7
     *            / \
     *           6   9                 
    */
    pa2m_afirmar(arbol_borrar(arbol,arbol_raiz(arbol))==EXITO,"Puedo borrar la raiz con un hijo");
    pa2m_afirmar((id_persona_t*)arbol->nodo_raiz->elemento==ids[7],"Se remplazo su hijo");

    pa2m_afirmar(arbol_borrar(arbol,ids[9])==EXITO,"Puedo borrar otro nodo hoja");
    pa2m_afirmar(arbol_borrar(arbol,arbol_raiz(arbol))==EXITO,"Puedo borrar la raiz con un hijo otra vez");
    pa2m_afirmar((id_persona_t*)arbol->nodo_raiz->elemento==ids[6],"Se remplazo su hijo");
    pa2m_afirmar(arbol_borrar(arbol,arbol_raiz(arbol))==EXITO,"Puedo borrar la raiz(sin hijos)");
    pa2m_afirmar(arbol_vacio(arbol),"Arbol queda vacio");

    arbol_destruir(arbol);
}


int main(int argc, char *argv[] ){
    if(argc > 1){
        pruebas_catedra();
    }else{
        pa2m_nuevo_grupo("Pruebas con NULL");
        pruebas_null();
        pa2m_nuevo_grupo("Pruebas crear arbol");
        pruebas_crear();
        pa2m_nuevo_grupo("Pruebas de insertar");
        pruebas_insertar();
        pa2m_nuevo_grupo("Pruebas de busqueda");
        pruebas_buscar();
        pa2m_nuevo_grupo("Pruebas recorridos");
        pruebas_recorrido();
        pa2m_nuevo_grupo("Pruebas Iterador interno");
        pruebas_iterador_interno();
        pa2m_nuevo_grupo("Pruebas Borrar");
        pruebas_borrar();
        pa2m_mostrar_reporte();
    }

    return 0;
}