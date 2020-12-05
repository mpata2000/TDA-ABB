# **TDA ABB**

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
    - [**Puntero NULL**](#puntero-null)
    - [**Crear :**](#crear-)
    - [**Comparador:**](#comparador)
    - [**Destructor:**](#destructor)
    - [**ABB vacio :**](#abb-vacio-)
    - [**Insertar :**](#insertar-)
    - [**Buscar:**](#buscar)
    - [**Borrar :**](#borrar-)
    - [**Recorridos :**](#recorridos-)
    - [**Iterador Interno**](#iterador-interno)
    - [**Recursividad :**](#recursividad-)
  - [**Teorico:**](#teorico)
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

Si no existe el zip lo crea, sino actualiza el zip. Se zipean todos los .c y .h y las carpetas/archivos que se hayan puesto en la variable FILES en el makefile. El zip se va a llamar abb.zip (el nombre del ejecutable + .zip)

### **Clean**

>`make clean`

Borra el ejecutable y los obejtos creados en la compilacion.

## **Funcionamiento y Implementacion :**

### **pruebas.c (el main):**

Si el main recive mas de un argumento ela pruebas que se van a correr son las prueba de `abb_minipruebas.c` dada por la catedra. Si no se recive nada las pruebas que se van a correr son las del pruebas.c.

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

### **Iterador Interno**

El iterador interno para funcionar tiene que recivir uno de los recorridos validos definidos en el abb.h y una funcion no nula.

### **Recursividad :**

Para todas las funciones que se requiere mas de iteracion se utilizo funciones recursivas auxiliares.

- Insertar
- Borrar
- Buscar
- Los recorridos
- El iterador interno

## **Teorico:**

**Explicar qué es un ABB y cómo se diferencia de un Árbol Binario.**

**Explicar cuál es el objetivo de tener una función de destrucción en el TDA y qué implicaría para el usuario no tenerla.**

El objetivo de tener una funcion de destruccion de elementose es permitirle al usuario meter elementos almacenados en el heap. Si no se brinda la opcion de utilizar un el destructor el usuario no podria hacer esto ya que al borrar un elemento o destruir el arbol el TDA de el no sabe que tipo de elemento se inserto y no lo podria usar. Ademas brindar la opcion permite que los elementos del ABB sean mas facil de modificar.

**¿Cuál es la complejidad de las diferentes operaciones del ABB? Justifique.**

- Crear
- Destruir
- Vacio
- Insertar
- Eliminar
- Recorrer

## **Creditos:**
