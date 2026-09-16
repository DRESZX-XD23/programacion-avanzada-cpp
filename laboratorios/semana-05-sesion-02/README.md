# Semana 5, Sesión 2: Punteros y memoria dinámica II

## Objetivo de la sesión

Diagnosticar y corregir fugas de memoria y punteros colgantes en código dado, distinguiendo un manejo correcto de uno incorrecto de memoria dinámica.

## Antes de empezar

**Lectura previa:** ["Memory Leaks and Dangling Pointers in C++", Debajyoti Chatterjee](https://debajyotichatterjee-88008.medium.com/memory-leaks-and-dangling-pointers-9b2ae80c2fe7)

**Referencia:** ["delete expression", cppreference](https://en.cppreference.com/w/cpp/language/delete.html)

Según el artículo, ¿en qué se diferencia un puntero colgante de una fuga de memoria? Las dos son formas de mal manejo de memoria dinámica, pero no son el mismo problema.

que el puntero colgane es un puntero sin memoria, y la fuga de memoria es una memoria sin puntero

La sesión pasada até la vida de la memoria reservada al ciclo de vida del objeto que la reserva, con RAII. ¿Qué pasaría si alguien más guardara un puntero a esa memoria, y siguiera usando ese puntero después de que el objeto dueño ya se destruyó?

Que el ciclo de vida de la memoria está atado al objeto dueño, ese objeto se encarga de liberar la memoria automáticamente en su destructor (por ejemplo al hacer delete sobre él).

## Ejercicio 1: reproducir un puntero colgante

Archivo: [`ejercicio1_puntero_colgante.cpp`](./ejercicio1_puntero_colgante.cpp). `obtenerLecturaInsegura` devuelve `&lectura`, la dirección de una variable local.

**Respuesta 1, antes de ver la solución:** `lectura` es una variable local de `obtenerLecturaInsegura`. ¿Qué pasa con ella cuando la función termina?

se elimina

**Respuesta 2:** antes de compilar, ¿qué advertencia esperas que dé el compilador sobre esta función?

 da una advertencia indicando que la función está devolviendo la dirección de una variable local, ya que esa variable deja de ser válida cuando la función termina.


**La formulación completa, tal como la resuelvo yo:**

laboratorios/semana-05-sesion-02/ejercicio1_puntero_colgante.cpp:25:12: warning: address of local variable 'lectura' returned [-Wreturn-local-addr]
   25 |     return &lectura;
      |            ^~~~~~~~
laboratorios/semana-05-sesion-02/ejercicio1_puntero_colgante.cpp:24:9: note: declared here
   24 |     int lectura = valorSensor * 2;
      |         ^~~~~~~

## Ejercicio 2: corregirlo

Archivo: [`ejercicio2_puntero_seguro.cpp`](./ejercicio2_puntero_seguro.cpp), mismo punto de partida que el Ejercicio 1.

**Respuesta 1, antes de ver la solución:** si esta función sí necesita devolver un puntero, ¿a qué debería apuntar ese puntero para que siga siendo válido después de que la función retorne?

Si la función necesita devolver un puntero que debe apuntar a memoria reservada dinámicamente con new, no a una variable local.

**Respuesta 2:** después de usar el puntero devuelto, ¿qué dos pasos evitan que alguien lo use por accidente después de liberado?

Liberar la memoria con delete para devolverla al sistema cuando ya no se necesita.
Asignarle nullptr al puntero después del delete.

**La formulación completa, tal como la resuelvo yo:**

int* obtenerLecturaSegura(int valorSensor) {
    int* nombre = new int(valorSensor * 2);
    return nombre;
}

int main() {
    int* resultado = obtenerLecturaSegura(10);
    std::cout << "Lectura: " << *resultado << std::endl;

    delete resultado;
    resultado = nullptr;

    return 0;
}
## Durante el ConcepTest

**Tu voto, antes de discutir en pareja** (A, B, C o D):

_(tu voto)_

**Tu razonamiento:**

_(tu respuesta)_

**Después de discutir en pareja, ¿cambiaste de voto? ¿Por qué?**

_(tu respuesta)_

## Ejercicio 3: diagnosticar un inventario

Archivo: [`ejercicio3_inventario.cpp`](./ejercicio3_inventario.cpp). Solo o en pareja. El archivo compila y corre, pero tiene dos bugs marcados con `TODO`.

**Bug 1, en `contarProductosAgotados`:** el arreglo `agotados` se reserva con `new[]` y solo se usa dentro de la función. Identifica qué falta antes de que la función termine, y corrígelo.

**Bug 2, en `obtenerReporteFinal`:** la función devuelve la dirección de `totalUnidades`, una variable local. Corrígelo, revisando primero si de verdad hace falta devolver un puntero para esto. Si cambias la función para que devuelva el entero por valor, actualiza también `main`: ya no necesitas `int* totalPtr`, ni el `delete` sobre él.

El archivo tiene, en su encabezado, la salida exacta que debe producir cuando esté completo.

## Compilar y ejecutar

```
g++ -std=c++20 -Wall -Wextra -g ejercicio1_puntero_colgante.cpp -o bin/ejercicio1
./bin/ejercicio1
```

Repite el mismo patrón con `ejercicio2_puntero_seguro.cpp` y `ejercicio3_inventario.cpp`.

## Qué construcciones nuevas usa este laboratorio

`nullptr`: valor especial que indica que un puntero no apunta a memoria válida, útil para dejar constancia explícita después de un `delete` y para comprobar un puntero antes de usarlo (`if (puntero != nullptr)`). El vocabulario de punteros, `new`, `delete` y RAII es el mismo de la Semana 5, Sesión 1. Nada de listas de inicialización de miembros, `smart pointers` ni excepciones: eso llega en sesiones posteriores.

## Antes de la próxima sesión

Cada vez que una función de este laboratorio necesitó devolver algo, copiar ese algo (un `int`, un `double`) fue barato. ¿Por qué copiar un objeto grande (por ejemplo, un arreglo de un millón de elementos) sería mucho más caro que copiar un `int`, y qué alternativa a copiar se te ocurre?

Copiar un int es barato porque son soloun objeto. Copiar un arreglo de un millón de elementos es caro porque hay que copiar cada elemento uno por uno, lo cual consume memoria extra.

en vez de copiar el objeto completo, se puede devolver un puntero a él