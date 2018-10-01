# Estructuras de Datos

Conjunto de estructuras de datos hechas en c++


## Pilas
Las pilas son estructuras de datos de tipo LIFO (Last In First Out, último en entrar primero en salir).
**- PilaArregloFijo.cpp**
Pila básica de enteros que almacena los datos en un arreglo que **no cambia de tamaño**.

**- PilaArregloDinamico.cpp**
Pila básica hecha con plantillas que almacena los datos en un arreglo dinámico.

**- PilaJoseGurrola.cpp**
Pila completa que guarda los valores utilizando una estructura "elemento",  el cual contiene el valor y un puntero al siguiente elemento de la pila.

## Colas
Las colas son estructuras de datos de tipo FIFO (First In First Out, Primero en entrar, ultimo en salir)

**- Cola plantilla.cpp**
Cola completa en plantilla que guarda los valores utilizando una estructura "elemento". 

**- Cola circular.cpp**
Cola completa en plantilla, es circular porque el ultimo elemento apunta al primero.

## Listas
 La lista enlazada es un estructura que nos permite almacenar datos de una forma organizada, al igual que los vectores pero, a diferencia de estos, esta estructura es dinámica.
 
**- Lista Simple Ordenada.cpp**
Lista enlazada en plantilla que ordena de menor a mayor los datos.

**- ListaDoble.cpp**
Lista enlazada en plantilla cuyos elementos se enlazan apuntando tanto al siguiente elemento como al anterior.

**- ListaCircular.cpp**
Lista enlazada en plantilla cuyo ultimo elemento de la lista apunta al primero.

**- Lista Racionales.cpp**
Lista enlazada de números Racionales, la lista utiliza a la clase Racional para formar la estructura.

**- Lista Polinomios.cpp**
Lista enlazada de Polinomios, contiene una clase polinomio, la cual usa a la clase monomio para construirse.

## Tabla Hash
Una tabla hash es una estructura de datos que asocia llaves o claves con valores. La operación principal que soporta de manera eficiente es la búsqueda.
La carpeta contiene una clase Lista y una clase Excepción que ayudan al correcto funcionamiento de la Tabla Hash.

**- Tabla Hash.cpp**
Tabla Hash completa en plantilla, se le puede insertar, eliminar y buscar un elemento, vaciar la table e imprimirla. La tabla al llenarse se re-dimensiona automáticamente. El cpp incluye un programa cliente para mostrar su funcionamiento.

## Árboles
 Los árboles son estructura de datos en la cual cada nodo puede tener un hijo izquierdo y un hijo derecho.
 
**- Arbol.cpp**
Árbol binario completo que tiene los siguientes metodos: Instertar, Eliminar, Saber si está vacío, Obtener el nodo raiz, saber si un nodo es hoja o no, buscar un elemento en el arbol, vaciar el arbol e imprimir en inorden, postorden y preorden.

**- ArbolAVL.cpp**
Un árbol AVL es un tipo especial de árbol binario. Fue el primer árbol de búsqueda binario auto-balanceable que se ideó. El programa tiene los sisguientes metodos: Instertar, Eliminar, Saber si está vacío, Obtener el nodo raiz, saber si un nodo es hoja o no, buscar un elemento en el arbol, vaciar el arbol e imprimir en forma ascendente.

**- Monton.cpp**
Es una estructura de datos del tipo árbol con información perteneciente a un conjunto ordenado. Los montículos máximos tienen la característica de que cada nodo padre tiene un valor mayor que el de cualquiera de sus nodos hijos, mientras que en los montículos mínimos, el valor del nodo padre es siempre menor al de sus nodos hijos.
