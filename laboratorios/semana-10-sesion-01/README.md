# Semana 10, Sesión 1: Plantillas y STL II: contenedores e iteradores

## Objetivo de la sesión

Elegir el contenedor de la STL adecuado según el patrón de acceso e inserción que exige un problema dado.

## Antes de empezar

**Lectura previa:** ["STL Containers: Vector, Set and Map", Megha B H](https://medium.com/@megha_bh/stl-containers-vector-set-and-map-7a90e0b1e19f)

**Referencia:** ["Containers library", cppreference](https://en.cppreference.com/w/cpp/container.html)

Según el artículo, ¿qué diferencia a un `set` de un `vector` cuando insertas un valor que ya estaba? ¿Y en qué orden quedan los elementos de un `map` al recorrerlo?

en el set los ordena de menor a mayor y solo puede haber un dato de cada uno, el vector los puedes poner tu como quieras y puede haber valores repetidos, el map se ordena igual de menor a mayor y el codigo no puede haber dos del mismo nombre

`Historial` tiene una capacidad fija y rechaza el valor que no cabe. ¿Qué tendría que hacer para crecer cuando se llena?

hay que moverlo a un array nuevo con move, tiene que ser mas grande y despues eliminar el antiguo array

## Ejercicio 1: Historial sobre un vector

Archivo: [`ejercicio1_historial_vector.cpp`](./ejercicio1_historial_vector.cpp). El `Historial<T>` de la sesión pasada, con capacidad 3, recibe 6 valores.

**Respuesta 1, antes de ver la solución:** con un `std::vector<int>` y `reserve(3)`, ¿qué capacidad esperas ver después de agregar el cuarto valor? ¿Qué tuvo que pasar con los tres valores que ya estaban guardados?

que de error el codigo 

**Respuesta 2:** en el paso 4, `semana.end()` no apunta al último elemento. ¿A qué apunta, y por qué el loop se detiene con `it != semana.end()` en vez de `it <= semana.end()`?

apunta a la posición que viene justo después del último elemento, donde no hay ningún valor. Se detiene por que o sino estaria leyendo una posicion que no existe.

**La formulación completa, tal como la resuelvo yo:**

template <typename T>
class Historial {
    private:
        std::vector<T> valores;
    public:
        Historial(int capacidadInicial) {
            valores.reserve(capacidadInicial);
        }

        bool agregar(T valor) {
            valores.push_back(valor);
            return true;
        }

        T obtener(int indice) {
            return valores[indice];
        }

        T ultimo() {
            return valores.back();
        }

        int getUsadas() {
            return valores.size();
        }

        int getCapacidad() {
            return valores.capacity();
        }
};
Agregar 4200: aceptado (usadas 1, capacidad 3)
Agregar 1800: aceptado (usadas 2, capacidad 3)
Agregar 3300: aceptado (usadas 3, capacidad 3)
Agregar 5100: aceptado (usadas 4, capacidad 6)
Agregar 2700: aceptado (usadas 5, capacidad 6)
Agregar 3900: aceptado (usadas 6, capacidad 6)
Ultimo dia: 3900
Primer dia: 4200
Semana: 4200 1800 3300 5100 2700 3900 4600
Total de la semana: 25600

## Durante el caso comparativo

Una fila de impresión recibe trabajos urgentes al frente y cancela trabajos en cualquier posición. Un registro de lecturas solo agrega al final y se consulta por posición. ¿Qué contenedor usarías para cada uno, y qué operación decide la elección?

Las operaciones que deciden son agregar al frente (push_front) y cancelar en cualquier posición (erase). En una lista, las dos solo reconectan punteros entre nodos, sin mover los demás elementos. En un vector, insertar al inicio o borrar en medio obliga a correr todos los elementos de atrás una posición. Además, vector ni siquiera tiene push_front.

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

## Ejercicio 2: la fila de la impresora

Archivo: [`ejercicio2_cola_impresion.cpp`](./ejercicio2_cola_impresion.cpp). Solo o en pareja.

Completa los métodos de `ColaDeImpresion`, que guarda los trabajos en una `std::list<int>`. `main` ya está completo y la salida esperada exacta está en el encabezado del archivo.

Antes de dar el ejercicio por terminado, responde: en `cancelar`, ¿qué pasaría si después de `trabajos.erase(it)` siguieras el loop con `++it`? ¿Qué operación de esta clase sería más barata con un `std::vector`, y por qué igual conviene la lista para este problema?

erase destruye el nodo donde estaba parado it, así que it queda inválido: apunta a memoria que ya no es parte de la lista. Hacer ++it sobre él es comportamiento indefinido: el programa puede saltarse elementos, imprimir basura o fallar. lo correcto sería it = trabajos.erase(it);, porque erase devuelve un iterador válido al siguiente elemento.

Recorrer la fila (imprimir, y la búsqueda dentro de cancelar) y agregar al final (agregar).

Porque las operaciones que definen el problema son agregar urgentes al frente (push_front), atender al primero (pop_front) y cancelar en cualquier posición (erase)

## Ejercicio 3: la bodega de componentes

Archivo: [`ejercicio3_bodega.cpp`](./ejercicio3_bodega.cpp). Solo o en pareja.

Escribe la clase `Bodega` a partir de la especificación del archivo. La especificación no dice qué contenedor usa cada atributo: lo eliges tú. `main` ya está completo y la salida esperada exacta está en el encabezado.

Antes de dar el ejercicio por terminado, responde por cada atributo: ¿qué contenedor elegiste, qué operación de la especificación decidió esa elección, y qué se rompería o se volvería más caro con otro contenedor?

Stock → std::map<int, int>.
La operación que decide es buscar la cantidad por código (ingresar, retirar, stockDe), y además imprimirStock pide los códigos de menor a mayor.
Historial de retiros → std::vector<int>.
Las operaciones que deciden son agregar al final en el orden en que ocurren (push_back), permitir repetidos (el 120 aparece tres veces) y consultar por posición (retiroNumero(2) usa []).

La especificación pide sin repetir y ordenados de menor a mayor, y el set hace las dos cosas automáticamente con insert.

Responde también: ¿por qué `stockDe(999)` no puede escribirse como `return stock[999];` si `stock` es un `map`? ¿Qué línea de la salida esperada lo delataría?

Porque en un map, el operador [] crea la clave si no existe, con valor 0. Leer stock[999] agregaría el código 999 al stock aunque nunca se ingresó, y la especificación dice que stockDe no debe registrar el código.

## Compilar y ejecutar

```
g++ -std=c++20 -Wall -Wextra -g ejercicio1_historial_vector.cpp -o bin/ejercicio1
./bin/ejercicio1
```

Repite el mismo patrón con `ejercicio2_cola_impresion.cpp` y `ejercicio3_bodega.cpp`.

## Qué construcciones nuevas usa este laboratorio

Los contenedores `std::vector<T>` (`push_back`, `size`, `[]`, `back`, `reserve`, `capacity`, inicialización con llaves), `std::list<T>` (`push_front`, `push_back`, `front`, `pop_front`, `erase`), `std::set<T>` (`insert`, `count`) y `std::map<K, V>` (`[]`, `count`, `size`, recorrido con `.first` y `.second`); iteradores (`begin()`, `end()`, `*it`, `++it`); `auto` para el tipo de un iterador; y el `for` de rango (`for (int valor : semana)`).

## Antes de la próxima sesión

**Lectura:** ["C++ STL: Overview of <algorithm>", Michael Spagna](https://mjspagna.medium.com/c-stl-overview-of-algorithm-a0d94342253e)

Hoy recorriste un `vector` y una `list` con el mismo patrón de iterador. Si mañana necesitas sumar, buscar el máximo y contar valores en los dos contenedores, ¿cuántas funciones escribirías con lo que sabes hoy? ¿Qué tendría que recibir una sola función para servir a los dos?

sumar, buscar el máximo y contar, cada una dos veces, una para std::vector y otra para std::list. El código de cada pareja sería casi idéntico, porque los dos se recorren con el mismo patrón de iterador (begin(), end(), *it, ++it). Solo cambiaría el tipo del parámetro.

En vez de recibir el contenedor, tendría que recibir dos iteradores: uno al inicio y otro al final del rango (begin() y end()).