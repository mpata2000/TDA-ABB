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
  - [**Funcionamiento:**](#funcionamiento)
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

## **Funcionamiento:**

## **Teorico:**

**Explicar qué es un ABB y cómo se diferencia de un Árbol Binario.**



**Explicar cuál es el objetivo de tener una función de destrucción en el TDA y qué implicaría para el usuario no tenerla.**

**¿Cuál es la complejidad de las diferentes operaciones del ABB? Justifique.**

- Crear
- Destruir
- Vacio
- Insertar
- Eliminar
- Recorrer

## **Creditos:**
