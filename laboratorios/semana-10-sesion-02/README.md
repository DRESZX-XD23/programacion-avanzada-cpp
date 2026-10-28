# Semana 10, Sesión 2: Plantillas y STL III: algoritmos STL

## Objetivo de la sesión

Resolver problemas usando algoritmos de la biblioteca STL en lugar de loops manuales, y explicar por qué funcionan con cualquier contenedor compatible.

## Antes de empezar

**Lectura previa:** ["C++ STL: Overview of <algorithm>", Michael Spagna](https://mjspagna.medium.com/c-stl-overview-of-algorithm-a0d94342253e)

**Referencia:** ["Algorithms library", cppreference](https://en.cppreference.com/w/cpp/algorithm.html)

Según el artículo, ¿qué reciben como argumento los algoritmos de `<algorithm>`: el contenedor, o otra cosa? ¿Qué devuelve `std::find` cuando no encuentra el valor?

reciben en un rango de inico hasta el final.
 Cuando `std::find` no encuentra el valor, devuelve el iterador final del
rango (`v.end()`), que no apunta a ningún elemento.


Si necesitas sumar, buscar el máximo y contar valores en un `vector` y en una `list`, ¿cuántas funciones escribirías con lo que sabías la sesión pasada? ¿Qué tendría que recibir una sola función para servir a los dos?


Escribiría 6 funciones (sumar, máximo y contar, una para `vector` y otra
para `list`).

 Para que una sola sirva a los dos, debería ser una plantilla
que reciba dos iteradores (inicio y fin)

## Ejercicio 1: de loops a algoritmos

Archivo: [`ejercicio1_lecturas_algoritmos.cpp`](./ejercicio1_lecturas_algoritmos.cpp). Las temperaturas de una semana, con cuatro loops escritos a mano.

**Respuesta 1, antes de ver la solución:** `std::max_element` no devuelve un `double`. ¿Qué devuelve, y por qué esa es la decisión correcta si el vector pudiera estar vacío?

Devuelve un iterador que apunta al elemento máximo. si el vector está vacío, no existe ningún máximo
que devolver como `double`

**Respuesta 2:** en el paso 5, las mismas llamadas pasan a recibir `lista.begin()` y `lista.end()`. ¿Compilan sin cambios? ¿Qué tiene que saber hacer el iterador de una lista para que `std::count` funcione?

Sí, compilan sin cambios. Para que `std::count` funcione, el iterador de la
lista solo tiene que saber avanzar al siguiente elemento

**Respuesta 3:** en el paso 6, `std::accumulate` recibe `0` en vez de `0.0`. ¿Qué número esperas que imprima?

un entero, y cada vez se va perdiendo exactitud

**La formulación completa, tal como la resuelvo yo:**


double sumaTotal = std::accumulate(temperaturas.begin(), temperaturas.end(), 0.0);


auto itMaximo = std::max_element(temperaturas.begin(), temperaturas.end());


int vecesEn23 = std::count(temperaturas.begin(), temperaturas.end(), 23.0);


auto itPosicion = std::find(temperaturas.begin(), temperaturas.end(), 25.5);

std::list<double> lista(temperaturas.begin(), temperaturas.end());
double sumaLista = std::accumulate(lista.begin(), lista.end(), 0.0);
auto itMaxLista = std::max_element(lista.begin(), lista.end());
int veces23Lista = std::count(lista.begin(), lista.end(), 23.0);


int sumaConCero = std::accumulate(temperaturas.begin(), temperaturas.end(), 0);

Salida:

suma acumulada: 153
Valor maximo: 25.5
Veces que dio 23: 2
Se encontro el 25.5 en la posicion: 4
Suma (lista): 153
Maxima (lista): 25.5
Dias en 23.0 (lista): 2
Suma con 0 como valor inicial: 151











    ## Durante los ConcepTests

**ConcepTest 1. Tu voto, antes de discutir en pareja** (A, B, C o D):

_(tu voto)_

**Tu razonamiento:**

_(tu respuesta)_

**Después de discutir en pareja, ¿cambiaste de voto? ¿Por qué?**

_(tu respuesta)_

**ConcepTest 2. Tu voto, antes de discutir en pareja** (A, B, C o D):

_(tu voto)_

**Tu razonamiento:**

_(tu respuesta)_

## Ejercicio 2: predicados sobre los pasos de una semana

Archivo: [`ejercicio2_pasos_predicados.cpp`](./ejercicio2_pasos_predicados.cpp). Solo o en pareja.

Escribe la función `esDiaSedentario` y resuelve cada `TODO` del `main` con `std::count_if`, `std::find_if` y `std::sort`, usando la función con nombre en el primero y lambdas en los demás. La salida esperada exacta está en el encabezado del archivo.

Antes de dar el ejercicio por terminado, responde: ¿qué error da el compilador si la lambda de la meta no escribe `[meta]`? ¿Por qué el ejercicio ordena una copia y no el vector `pasos`?

 el error meta is not captured: la lambda está dentro del main pero no puede usar una variable local de afuera si no la captura entre corchetes.
da error por que esa lamda esta afuera del main y no sabe que variable coger.
e ordena una copia porque sort modifica el vector que recibe. Si
ordenara pasos, se perdería el orden original

## Ejercicio 3: las ventas de la tienda

Archivo: [`ejercicio3_ventas_algoritmos.cpp`](./ejercicio3_ventas_algoritmos.cpp). Solo o en pareja.

Responde las cuatro preguntas del `main` sobre un `std::vector<Venta>` con algoritmos de la STL, sin escribir ningún loop propio. Tú eliges qué algoritmo resuelve cada una. La salida esperada exacta está en el encabezado.

Antes de dar el ejercicio por terminado, responde: si `ventas` fuera una `std::list<Venta>`, ¿cuál de tus llamadas deja de compilar? ¿Con qué la reemplazarías?

Deja de compilar std::sort, porque necesita iteradores de acceso
aleatorio 

reemplazo ventas.sort([](Venta a, Venta b) { return a.getTotal() > b.getTotal(); });
Responde también: ¿qué imprime "Total recaudado" si el valor inicial de tu suma es `0` en vez de `0.0`? Pruébalo.

imprime 146, la primera venta (2.5) se guarda como 2 y se pierde el 0.5
## Compilar y ejecutar

```
g++ -std=c++20 -Wall -Wextra -g ejercicio1_lecturas_algoritmos.cpp -o bin/ejercicio1
./bin/ejercicio1
```

Repite el mismo patrón con `ejercicio2_pasos_predicados.cpp` y `ejercicio3_ventas_algoritmos.cpp`.

## Qué construcciones nuevas usa este laboratorio

Los algoritmos `std::accumulate` (de `<numeric>`, con y sin operación propia), `std::max_element`, `std::count`, `std::count_if`, `std::find`, `std::find_if` y `std::sort` (de `<algorithm>`), siempre sobre un rango `[begin, end)`; la resta de dos iteradores de un vector para obtener una posición; pasar una función por su nombre como argumento; lambdas sin captura (`[](int p) { ... }`) y con captura por valor (`[meta](int p) { ... }`); y construir una `std::list` a partir del rango de un vector.

## Antes de la próxima sesión

**Lectura:** ["Why I've soured on exceptions in C++", Jordan Edmunds Chetty](https://medium.com/@jordan.l.edmunds/why-ive-soured-on-exceptions-in-c-ea10b8ad10e8)

La `Bodega` de la sesión pasada devuelve `false` cuando no puede retirar, y `*std::max_element(v.begin(), v.end())` con un vector vacío lee una posición que no existe. ¿Cómo se entera hoy quien llama a esas funciones de que algo salió mal? ¿Qué pasa si no revisa el valor devuelto?

Solo se entera si revisa el valor devuelto false o v.end(). Si no lo
revisa, el error no salta