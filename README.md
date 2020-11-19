# **TDA ABB**

## **Tabla de Contenidos**

- [**TDA ABB**](#tda-abb)
  - [**Tabla de Contenidos**](#tabla-de-contenidos)
  - [**Compilacion:**](#compilacion)
  - [**Makefile:**](#makefile)
    - [**Comandos:**](#comandos)
      - [**make o make $(EXEC):**](#make-o-make-exec)
      - [**make debug:**](#make-debug)
      - [**make test:**](#make-test)
      - [**make run:**](#make-run)
      - [**make zip:**](#make-zip)
      - [**make clean:**](#make-clean)
      - [**make %.o:**](#make-o)
  - [**Funcionamiento:**](#funcionamiento)
  - [**Teorico:**](#teorico)
  - [**Creditos:**](#creditos)

## **Compilacion:**

----
Para compilar y usar este TDA se utiliza un makefile.

**La linea principal de compilacion es:**
> `make` o `make lista_se`

**La linea principal de para ejecutar con mis pruebas:**
>`make run`

**La linea principal de para ejecutar con las pruebas de la catedra:**
>`make run arg_1=...`

- Se puede poner algo atras del arg_1.

**La linea principal de para ejecutar con valgrind:**
>`make test`

- Aplica lo mismo que en `make run`, si se inicializa arg_1 corre la pruebas de la catedra si no corre mis pruebas.

## **Makefile:**

----

```makefile
CC = gcc
CFILES = *.c
HFILES = *.h
OBJETOS = lista.o lista_minipruebas.o
FILES = Enunciado README.md
EXEC = lista_se
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

$(EXEC): pruebas.c $(OBJETOS)
    $(CC) $^ $(CFLAGS) -o $(EXEC)

debug: $(EXEC)
    gdb $(EXEC)

test: $(EXEC)
   valgrind $(VFLAGS) ./$(EXEC)

run: $(EXEC)
   ./$(EXEC) $(arg_1) $(arg_2) $(arg_3)

%.o: %.c %.h
   $(CC) $(CFLAGS) -c $< -o $@

zip:
   zip -r $(EXEC).zip $(CFILES) $(HFILES) $(FILES)

.PHONY: clean
clean:
   rm -f *.o $(EXEC)
```

### **Comandos:**

#### **make o make $(EXEC):**

```makefile
$(EXEC): pruebas.c $(OBJETOS)
    $(CC) $^ $(CFLAGS) -o $(EXEC)
```

 Este comando compila el programa si y solo si el archivo de jecucion (EXEC) esta desactulizado.

- `EXEC = lista_se`
  - El nombre del ejecutable que se quiere crear
- `OBJETOS = lista.o lista_minipruebas.o -O0`
  - Los objetos que se quieren compilar para compilar el ejecutable(solo se vuelven a compilar lo objetos si estan des acutializados)
- `CC = gcc`
  - El nombre del compilador que se va usar-
- `CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0`
  - Los flags de gcc que se van a usar al compilar el ejecutable.
- `$^`
  - Es una instruccion de make que agarra todo lo que esta depues del `:` y lo copia donde esta
  
#### **make debug:**

```makefile
debug: $(EXEC)
    gdb $(EXEC)
```

 Este comando primero chequea que `$(EXEC)` este compilado y actualizado(si no lo esta lo actualiza) y corre `gdb $(EXEC)` para debuggear el programa.

#### **make test:**

```makefile
test: $(EXEC)
   valgrind $(VFLAGS) ./$(EXEC) $(arg_1) $(arg_2) $(arg_3)
```

  Este comando primero chequea que evento `$(EXEC)` este compilado y actualizado; y corre valgrind para testear perdidas de memoria.

- `arg_n`
  - Estas variables se pueden utilizar cuando se quiere dar argumentos al main. Se inicializa escribiendo despues del comando `make test arg_1=i` y asi con cada arg_n que se quiera inicilazar.

#### **make run:**

```makefile
run: $(EXEC)
   ./$(EXEC) $(arg_1) $(arg_2) $(arg_3)
```

 Se usa para ejecutar el programa. El comando primero chequea que `$(EXEC)` este compilado y actualizado(si no lo esta lo actualiza).

- `arg_n`
  - Estas variables se pueden utilizar cuando se quiere dar argumentos al main. Se inicializa escribiendo despues del comando `make run arg_1=i` y asi con cada arg_n que se quiera inicilazar.

#### **make zip:**

```makefile
zip:
   zip -r $(EXEC).zip $(CFILES) $(HFILES) $(FILES)
```

Este comando crea un zip con los archivos `$(CFILES)`,`$(HFILES)` y `$(FILES)` con el nombre `$(EXEC).zip` (osea el nombre del ejecutable con .zip al final).

#### **make clean:**

```makefile
.PHONY: clean
clean:
   rm -f *.o $(EXEC)
```

make clean borra todos los objetos (*.o se remplaza por todos los ojetos en la carpeta) y el ejecutable (`$(EXEC)`)

- `.PHONY : clean.`
  - Esto hace un clean mas robusto. Si existiera un archivo que se llamara clean, y no la pusieramos, vamos a tener un comportamiento indefinido.

#### **make %.o:**

```makefile
%.o: %.c %.h
   $(CC) $(CFLAGS) -c $< -o $@
```

Esta es una funcion interna del make la cual es llamada por `make $(EXEC)`. Solo se llama cuando los `$(OBJETOS)` estan desactualizados.

- `$@`
  - Indica que ahi se escribir a el nombre de lo que queremos generar, el target de la regla que es %.o
- `%.o`
  - Indica que es la regla para cualquier cosa terminada en .o .
- `$<`
  - Es una instruccion de make que agarra la primer instruccion prerequisito despues del `:` que es %.c.
- `%.c`
  - Chequea para cada .o este compilado con el ultimo .c mas actualizado.

## **Funcionamiento:**

## **Teorico:**

## **Creditos:**
