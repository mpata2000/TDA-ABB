# **TDA ABB**

Este TDA ABB es el segundo TDA que se tiene que entregar para la aprobacion de la cursada de `Algoritmos y Programacion 2(75.41)-Catedra Mendez`.

Se realizaron 110 pruebas propias para chequear el funcionamieno correcto del ABB.

## **Tabla de Contenidos**

- [**TDA ABB**](#tda-abb)
  - [**Tabla de Contenidos**](#tabla-de-contenidos)
  - [**Compilacion y Ejecucion :**](#compilacion-y-ejecucion-)
    - [**La linea principal de compilacion :**](#la-linea-principal-de-compilacion-)
    - [**La linea principal de ejecucion :**](#la-linea-principal-de-ejecucion-)
    - [**La linea principal de ejecucion con valgrind :**](#la-linea-principal-de-ejecucion-con-valgrind-)
  - [**Comandos extra del makefile:**](#comandos-extra-del-makefile)
    - [**Debugging :**](#debugging-)
    - [**Zip :**](#zip-)
    - [**Clean**](#clean)
  - [**Funcionamiento y Implementacion :**](#funcionamiento-y-implementacion-)
    - [**pruebas.c (el main):**](#pruebasc-el-main)
    - [**pa2mm .h :**](#pa2mm-h-)
    - [**Puntero NULL**](#puntero-null)
    - [**Crear :**](#crear-)
    - [**Comparador:**](#comparador)
    - [**Destructor:**](#destructor)
    - [**ABB vacio :**](#abb-vacio-)
    - [**Insertar :**](#insertar-)
    - [**Buscar:**](#buscar)
    - [**Borrar :**](#borrar-)
    - [**Recorridos :**](#recorridos-)
    - [**Iterador Interno :**](#iterador-interno-)
    - [**Recursividad :**](#recursividad-)
  - [**Teorico:**](#teorico)
    - [**Explicar qué es un ABB y cómo se diferencia de un Árbol Binario.**](#explicar-qué-es-un-abb-y-cómo-se-diferencia-de-un-árbol-binario)
    - [**Explicar cuál es el objetivo de tener una función de destrucción en el TDA y qué implicaría para el usuario no tenerla.**](#explicar-cuál-es-el-objetivo-de-tener-una-función-de-destrucción-en-el-tda-y-qué-implicaría-para-el-usuario-no-tenerla)
    - [**¿Cuál es la complejidad de las diferentes operaciones del ABB? Justifique.**](#cuál-es-la-complejidad-de-las-diferentes-operaciones-del-abb-justifique)
  - [**Creditos:**](#creditos)

## **Compilacion y Ejecucion :**

Para compilar y usar este TDA se utiliza un makefile. Si quiere saber mas lea MAKEFILE.md

### **La linea principal de compilacion :**

> `make` o `make abb`

Se crea objetos de las librerias utilizadas y el ejecutable abb.

### **La linea principal de ejecucion :**

>`make run` o `make run arg_1=...`

Se llama al comando chequea si el ejecutable esta actualizado, si no lo esta se compila devuelta, y se ejecuta el programa

- Si no se inicializa arg_1 se corren las pruebas de pruebas.c .
- si se inicializa arg_1 a cualquier valor se correran las pruebas otorgada por la catedra (abb_minipruebas.c).

### **La linea principal de ejecucion con valgrind :**

>`make test` o `make test arg_1=...`

Se chequea si el ejecutable esta actualizado, si no lo esta se compila devuelta, y se ejecuta el programa con valgrind para chequear la perdida de memoria.

- Aplica lo mismo que en `make run`, si se inicializa arg_1 corre la pruebas de la catedra si no corre con las de pruebas.c .

## **Comandos extra del makefile:**

### **Debugging :**

>`make debug`

Chequea si el ejecutable esta actualizado, si no lo esta se compila devuelta. Despues se llama a gdb con el ejecutabe en el modo tui

### **Zip :**

>`make zip`

Crea un zip. Se comprimen todos los .c y .h y las carpetas/archivos que se hayan puesto en la variable FILES en el makefile. El zip se va a llamar abb.zip (el nombre del ejecutable + .zip)

### **Clean**

>`make clean`

Borra el ejecutable y los obejtos creados en la compilacion.

## **Funcionamiento y Implementacion :**

### **pruebas.c (el main):**

Si el main recive mas de un argumento ela pruebas que se van a correr son las prueba de `abb_minipruebas.c` dada por la catedra. Si no se recive nada las pruebas que se van a correr son las del pruebas.c.

### **pa2mm .h :**

Para las pruebas hechas se utilizo la libreria proporcionada por la catedra creada por Lucas Pandolfo. Si tiene alguna queja sobre su implementacion vaya hablar con el, aca se utiliza como una libreria externa.

### **Puntero NULL**

Si alguna funcion del TDA recive un arbol nulo va a fallar.

### **Crear :**

Se puede crear un ABB sin destructor pero no se puede crear un ABB sin comparador. **Siempre se tiene que almacenar el retorno de la funcion en un abb_t\* y tiene que ser destruido con arbol_destruir() para no perder memoria.**

### **Comparador:**

- Si no sigue los retornos indicados en el abb.h se va a romper el ABB.
- Si se insertan elementos NULL el comparador tiene que ser capaz de manejarlo

### **Destructor:**

- Si usted desea almacenar elementos almacenados en heap asegurese que el destructor libere bien sus elementos para no perder memoria.
- Si se insertan elementos NULL su destructor tiene que ser capaz de manejarlo

### **ABB vacio :**

Una ABB esta vacio cuando su raiz es nula.

- A un ABB vacio se le puede insertar un elemento y va a dejar de estar vacia.
- Con un ABB vacio no se puede borrar,buscar ni recorrer ningun elemento.
- Si se borra el ultimo elemento restante del ABB queda vacio.
- Un arbol NULL se considera vacio.

### **Insertar :**

Se puede insertar cualquier tipo de elemento solo se tiene que asegurarse de que las funciones usadas al crear el arbol sea capaz de usarlo.

- Siempre chequee si la insercion falla.
- Se puede insertar elementos con la misma clave de comparacion.
- Si se encuentra un elemento con la misma clave de comparacion se va insertar como su predecesor inorden.
- **Aclaracion:** Si inserta dos veces el mismo elemento del heap lo mas probable es que se rompa el ABB

### **Buscar:**

- Si inserta elementos NULL no va a saber si se encontro el elemento deseado o si la funcion fallo.
- Si tiene dos elementos con la misma clave de comparacion se va a devolver el primero encontrado.

### **Borrar :**

El borrado del elemento solo puede fallar si no se encontro ese elemento.

- Si tiene dos elementos con la misma clave de comparacion se va a borrar el primero encontrado.
- Cuando se borra un elemento con dos hijos se busca como remplazo su predecesor inorden.

### **Recorridos :**

Para hacer cualquiera de los recorridos se tiene que mandar un size_t valido de los elementos a recorrer y un array no nulo que pueda almacenar los elementos almacenados en el arbol.

### **Iterador Interno :**

El iterador interno para funcionar tiene que recivir uno de los recorridos validos definidos en el abb.h y una funcion no nula.

### **Recursividad :**

Para todas las funciones que se requiere mas de iteracion se utilizo funciones recursivas auxiliares.

- Insertar
- Borrar
- Buscar
- Los recorridos
- El iterador interno

## **Teorico:**

### **Explicar qué es un ABB y cómo se diferencia de un Árbol Binario.**

Un arbol binario de busqueda es un arbol de comparacion y un arbol binario donde cada nodo debe contener un valor clave de comparacion que satisfaga las siguientes condiciones:

- La clave del hijo izquierdo(si exite) es menor que la clave del padre.
- La clave del hijo derecha(si exite) es mayor que la clave del padre.
- Cada sub-arbol es un ABB.

A diferecia del un arbol binario que es una estructura de datos donde cada nodo tiene dos hijos pero los elementos de estos nodos no se encuentran ordenados.

### **Explicar cuál es el objetivo de tener una función de destrucción en el TDA y qué implicaría para el usuario no tenerla.**

El objetivo de tener una funcion de destruccion de elementose es permitirle al usuario meter elementos almacenados en el heap. Si no se brinda la opcion de utilizar un el destructor el usuario no podria hacer esto ya que al borrar un elemento o destruir el arbol el TDA de el no sabe que tipo de elemento se inserto y no lo podria usar. Ademas brindar la opcion permite que los elementos del ABB sean mas facil de modificar.

### **¿Cuál es la complejidad de las diferentes operaciones del ABB? Justifique.**

- `Crear:` `O(1)` Ya que no depende del tamaño del arbol y su complejidad es constante.
- `Destruir: O(n)` Ya que solo recorre una vez todos los nodos del arbol.
- `Vacio: O(1)` Ya que no depende del tamaño del arbol y su complejidad es constante.
- `Buscar:`
  - Si el arbol esta balanceado `O(log(n))` ya que cada vez se reduce el problema a la mitad.
  - Si el arbol no esta balanceado empieza a tender a ser una lista, entonces en el peor de los casos se recorre todos los nodos, entonces su complejidad es `O(n)`.
- `Insertar:`  
  - Si el arbol esta balanceado `O(log(n))` ya que cada vez se reduce el problema a la mitad.
  - Si el arbol no esta balanceado empieza a tender a ser una lista, entonces en el peor de los casos se recorre todos los nodos, entonces su complejidad es `O(n)`.
- `Eliminar:`
  - Si el arbol esta balanceado `O(log(n))` ya que cada vez se reduce el problema a la mitad.
  - Si el arbol no esta balanceado empieza a tender a ser una lista, entonces en el peor de los casos se recorre todos los nodos, entonces su complejidad es `O(n)`.
- `Recorrer:` Todos los recorridos son `O(n)` ya que en el pero de los casos se recorre todos los nodos del arbol.

## **Creditos:**

Este trabajo no se podria haber completado sin la ayuda de mi corrector Grabiel Pucci.
