# Semana 14, Sesión 2: Laboratorio Integrador II

## Objetivo de la sesión

Aplicar de forma integrada los temas de concurrencia, testing y build systems del curso al desarrollo del proyecto final (PSet 5).

## Antes de empezar

Sin lectura nueva. Repasa las lecturas y referencias de las Semanas 12 y 13 si algo no está fresco:

- [GoogleTest Primer](https://google.github.io/googletest/primer.html) y [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html) (Semana 12)
- [std::mutex (cppreference)](https://en.cppreference.com/w/cpp/thread/mutex.html) y [std::atomic (cppreference)](https://en.cppreference.com/w/cpp/atomic/atomic.html) (Semana 13)

La sesión tiene dos partes. La primera es este laboratorio, un solo problema que combina los tres temas. La segunda es tiempo para tu Proyecto Final (PSet 5): trae tus dudas.

## El problema: los pedidos de la cafetería del campus

Tres cajas toman pedidos al mismo tiempo y los dejan en una cola. Después, dos cocineros sacan pedidos de la cola al mismo tiempo, descuentan los productos del inventario y anotan el resultado. Un pedido puede despacharse, quedar sin stock (el producto 5 tiene pocas unidades) o ser inválido (uno de cada 50 pide un producto que no existe). Al final del día, todo tiene que cuadrar: ningún pedido perdido ni repetido, y ningún producto con unidades negativas.

No hay ejercicio resuelto antes del tuyo: el proyecto completo es tu único ejercicio de hoy.

## De dónde viene cada pieza

| Tema | De qué semana | Dónde aparece hoy |
|---|---|---|
| Clases, `std::vector`, `std::map`, `std::optional` | Semanas 2, 10 y 11 | `ColaDePedidos`, `Inventario` |
| Excepciones | Semana 11, Sesión 1 | `Inventario::descontar` lanza `std::invalid_argument`; el cocinero la atrapa |
| Pruebas con GoogleTest | Semana 12, Sesión 1 | `test_pedidos.cpp` |
| CMake y sanitizers | Semana 12, Sesión 2 | `CMakeLists.txt`, con `CON_SANITIZERS` y la opción nueva `CON_TSAN` |
| Hilos, mutex, `lock_guard` | Semana 13, Sesión 1 | `ColaDePedidos` e `Inventario` |
| `std::atomic` | Semana 13, Sesión 2 | `Estadisticas` |

## Archivos

- [`pedidos.h`](./pedidos.h): las tres clases. `Pedido` y los métodos de consulta ya están. Te tocan los `TODO 1` a `4`.
- [`main.cpp`](./main.cpp): un día de la cafetería. No lo cambies: al final imprime `Cuadra: si` o `Cuadra: no`.
- [`test_pedidos.cpp`](./test_pedidos.cpp): dos pruebas ya escritas. Te toca el `TODO 5`: cinco pruebas más, descritas en el archivo, incluida una con dos hilos.
- [`CMakeLists.txt`](./CMakeLists.txt): el programa y las pruebas, con la opción `CON_SANITIZERS` de la Semana 12. Te toca el `TODO 6`: una opción `CON_TSAN` para ThreadSanitizer.

## Compilar y ejecutar

Desde esta carpeta:

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/cafeteria
ctest --test-dir build --output-on-failure
```

Antes de cambiar nada, corre el programa tres veces. Lo más probable es que termine con un error de memoria (`Segmentation fault` o `malloc(): ...`), o que no cuadre. ¿Por qué un programa que nunca usa `new` ni `delete` puede romper la memoria?

Porque std::vector sí usa memoria dinámica por dentro. Cuando push_back llena la capacidad, el vector pide un bloque más grande, copia los elementos y libera el bloque viejo. Si dos cajas hacen push_back a la vez sin candado, una puede escribir en el bloque que la otra acaba de liberar, o las dos pueden liberar el mismo bloque.

Cuando tengas el `TODO 6`, compila en otra carpeta con ThreadSanitizer:

```
cmake -S . -B build-tsan -DCON_TSAN=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-tsan
./build-tsan/cafeteria
./build-tsan/pruebas
```

## Salida esperada

```
Pedidos en la cola: 60000
Pedidos atendidos: 60000
Pedidos invalidos: 1197
Pedidos sin stock: (cambia un poco de una corrida a otra)
Cuadra: si
```

Y `ctest`: las 7 pruebas pasan, también en `build-tsan`, sin ningún reporte de ThreadSanitizer.

## Rúbrica

- **Concurrencia, la cola:** `agregar` y `tomar` toman el candado de la clase; en `tomar`, mirar si quedan pedidos y avanzar `siguiente` pasan dentro de la misma sección crítica. Ningún pedido se pierde ni se entrega dos veces.
- **Concurrencia, el inventario:** en `descontar`, preguntar si alcanza y restar pasan con el candado tomado; las excepciones se lanzan con el candado tomado, y el `lock_guard` lo suelta al salir (RAII).
- **Atomics:** los tres contadores de `Estadisticas` son `std::atomic<int>`, empiezan en 0 en el constructor, y no usan mutex.
- **Excepciones:** `descontar` lanza `std::invalid_argument` para un producto que no existe o una cantidad no positiva, y no descuenta nada en esos casos.
- **Pruebas:** las cinco pruebas del `TODO 5`, cada una con un nombre que dice lo que verifica, y la de dos hilos, compilada con `CON_TSAN`, hace que ThreadSanitizer reporte un data race si se quita el candado de `descontar`.
- **Build:** `CON_TSAN` apagada por defecto; con ella encendida, el programa y las pruebas corren sin reportes de ThreadSanitizer.

## Para pensar mientras completas `Estadisticas`

Estadisticas usa atomics y no un mutex. Inventario usa un mutex y no atomics. ¿Por qué no al revés? ¿Qué tendría que pasar con descontar para que un std::atomic<int> por producto alcanzara?

Estadisticas usa atomics porque cada anotación es una sola operación sobre un
número (++), y un atomic la hace indivisible sin necesidad de mutex.
Inventario necesita un mutex porque descontar tiene dos pasos que deben ir
juntos: revisar si alcanza y restar. 

Para que bastara un std::atomic<int> por producto, revisar y restar tendrían
que ser una sola operación atómica


## Después: tu Proyecto Final

Con el tiempo que quede, trabaja en tu PSet 5. Antes de irte, anota:

**¿Qué parte de tu proyecto corre en más de un hilo, y qué la protege?**

Las tres cajas
agregan pedidos a la vez y los dos cocineros toman pedidos y descuentan del
inventario a la vez. La cola y el inventario los protege un `std::mutex` con
`lock_guard`

**¿Qué prueba de tu proyecto mostraría el problema si quitaras esa protección? ¿Fallaría siempre, o necesitas ThreadSanitizer para verlo?**

dos hilos descuentan 1 unidad 1000 veces cada uno de
un producto con 1000, y al final deben quedar 0 y haberse vendido 1000. Sin el
candado no falla siempre: la carrera depende de cómo se intercalen los hilos y
muchas veces la prueba pasa por suerte. 
Lo comprobé: sin el candado la prueba pasó, pero ThreadSanitizer reportó el
data race.
## Antes de la próxima sesión

La próxima sesión es de Tópicos Avanzados: un repaso de todo el curso guiado por tus preguntas, sin lectura nueva. Trae por escrito dos preguntas: una sobre un tema del curso que todavía no te cierra, y una sobre algo de C++ que el curso no vio y te gustaría entender.

sobre el uso de los punteros, como se diferencian en contraste con un int o un double.
reforzar mas el uso de arrays 