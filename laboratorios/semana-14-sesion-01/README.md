# Semana 14, Sesión 1: C++ en la industria: casos reales

## Objetivo de la sesión

Argumentar, con casos reales de la industria, por qué C++ sigue siendo la opción dominante en sistemas, trading de alta frecuencia, videojuegos y sistemas embebidos.

## Antes de empezar

**Lectura previa:** ["Why C++ Still Dominates High-Frequency Trading (And It's Not Just Speed)", Rishi Jain](https://medium.com/@beingrishijain/why-cpp-still-dominates-high-frequency-trading-and-its-not-just-speed-ad15d6a1a256)

**Referencia:** [C++ Applications (Bjarne Stroustrup)](https://www.stroustrup.com/applications.html)

Según el artículo, si no es solo la velocidad, ¿qué hace que las firmas de trading de alta frecuencia sigan eligiendo C++?
Su comportamiento es predecible. En HFT importa el peor caso, no el promedio: un pico o una pausa inesperada se considera una pérdida. C++ no tiene recolector de basura que detenga la ejecución de forma repentina ni un runtime oculto que actúe por detrás del programador.

En la sesión pasada te pregunté qué características de C++ que vimos en el semestre importan en un sistema que compra y vende acciones, además de la velocidad. ¿Cuáles anotaste?

creo que RAII y destructores Smart pointers Control de dónde vive la memoria std::mutex y std::lock_guard.

Entra a esta carpeta y crea la carpeta de los ejecutables:

```
cd laboratorios/semana-14-sesion-01
mkdir -p bin
```

Hoy los programas se compilan con optimización (`-O2`), como se compila lo que llega a producción, y se miden con `time`, igual que en la Semana 13. Cada archivo trae su comando en el encabezado.

## Ejercicio 1: el libro de órdenes de una bolsa

Archivos: [`ejercicio1_libro_mapa.cpp`](./ejercicio1_libro_mapa.cpp) (no lo modifiques) y [`ejercicio1_libro_arreglo.cpp`](./ejercicio1_libro_arreglo.cpp). Un libro de órdenes guarda cuántas acciones hay ofrecidas a cada precio. Llegan 20 millones de eventos (órdenes nuevas y cancelaciones), y después de cada uno el programa de trading consulta cuánto hay en ese precio. La versión del mapa ya funciona. La del arreglo guarda cada precio en una casilla fija de un `std::vector`. Compila y mide la del mapa antes de tocar nada.

**Respuesta 1 (antes de los TODO):** ¿cuánto tardó la versión del mapa? Antes de escribir la del arreglo: ¿cuántas veces más rápida crees que va a ser? ¿Por qué?

la versión del mapa tardó unos 3.07 s. El std::map es un árbol: cada consulta baja unos 10 niveles por punteros a nodos que pueden estar en cualquier parte de la memoria, y count y luego [] repiten la búsqueda.

**Respuesta 2 (después de los TODO):** ¿imprimen lo mismo las dos versiones? ¿Cuánto tardó cada una? Si el libro procesara 20 millones de eventos por hora, ¿cuánto tiempo de procesador por evento gasta cada versión?
sí, las dos imprimen lo mismo (335979057 y 3363069806340). El mapa tardó 3.07 s y el arreglo 0.075 s, unas 40 veces más rápido. Por evento son 3.07 s / 20 000 000 ≈ 154 ns con el mapa y 0.075 s / 20 000 000 ≈ 3.8 ns con el arreglo

**Respuesta 3:** la versión del arreglo funciona porque los precios son 1000 y se conocen de antemano. ¿Qué pasaría si los precios pudieran ser cualquier número? ¿Qué te dice eso sobre de dónde sale la ventaja?

si los precios pudieran ser cualquier número, no se podría reservar una casilla para cada uno: el vector tendría que ser gigante y quedaría casi vacío. Habría que volver a un map o a un unordered_map


## Ejercicio 2: el presupuesto de un cuadro

Archivos: [`ejercicio2_particulas_punteros.cpp`](./ejercicio2_particulas_punteros.cpp) (no lo modifiques) y [`ejercicio2_particulas_contiguas.cpp`](./ejercicio2_particulas_contiguas.cpp). En casa, solo o en pareja; vence el domingo de la Semana 14.

Un juego a 60 cuadros por segundo tiene 16.7 milisegundos por cuadro para todo. La versión de punteros simula 600 cuadros de una explosión de 300000 partículas, cada una creada con `std::make_unique`. La tuya guarda las mismas partículas, con la misma clase, dentro de un `std::vector<Particula>`.

1. Compila y mide la versión de punteros. Divide el tiempo por 600: ¿qué parte del presupuesto de un cuadro se lleva la física de las partículas?


Punteros: 0.78 s / 600 o 1.3 ms por cuadro.
2. Resuelve los tres `TODO` de la versión contigua. Tiene que imprimir la misma altura promedio.
3. Mídela, y calcula lo mismo que en el paso 1.

Contigua: 0.19 s / 600 o 0.32 ms por cuadro.

4. Responde: las dos versiones hacen exactamente las mismas cuentas. ¿De dónde sale la diferencia?
De dónde vive cada partícula en memoria. En la versión de punteros, cada partícula es una reserva separada, mezclada con los bloques de relleno, y recorrerlas obliga al procesador a saltar por toda la memoria.
5. Responde: un motor de juegos escrito en un lenguaje con recolector de basura podría pausar el juego unos milisegundos en cualquier cuadro. ¿Por qué eso es un problema, aunque el promedio de tiempo por cuadro sea bueno?

Porque el presupuesto es por cuadro, no por promedio. Si en un cuadro el recolector pausa 5 ms y la física ya usa 12 ms, ese cuadro se pasa de 16.7 ms y el jugador ve un tirón (stutter), aunque el promedio sea bueno.
## Ejercicio 3: el sensor del motor de un dron

Archivo: [`ejercicio3_buffer_sensor.cpp`](./ejercicio3_buffer_sensor.cpp). En casa, solo o en pareja; vence el domingo de la Semana 14.

El microcontrolador del motor de un dron lee la temperatura 1000 veces por segundo y recuerda las últimas 64 lecturas. En ese tipo de sistema hay una regla: una vez que el programa arranca, no se pide memoria dinámica nunca más. El encabezado describe la clase `BufferCircular`; esta vez no hay código de partida para la clase. [`contador_reservas.h`](./contador_reservas.h) cuenta cada vez que el programa pide memoria dinámica (no lo modifiques). El `main` ya está escrito. Mientras no escribas la clase, el archivo no compila.

1. Escribe `BufferCircular` y corre el programa: las cinco líneas tienen que salir iguales a las del encabezado, incluida la última, `0`.



2. Compila y corre [`ejercicio3_buffer_lista.cpp`](./ejercicio3_buffer_lista.cpp), que hace lo mismo con una `std::list`. ¿Cuántas reservas de memoria hizo? ¿De dónde salen?
La versión con std::list hizo 1000000 reservas, una por lectura. Cada push_back crea un nodo nuevo en el heap, y pop_front libera el más antiguo.
3. Responde: ¿por qué un sistema embebido prohíbe pedir memoria después de arrancar, si la versión con `std::list` también da los números correctos?

Porque en un sistema embebido no basta con que el resultado sea correcto: también tiene que llegar a tiempo, siempre. Pedir memoria tarda un tiempo que no se puede acotar. Con el tiempo la memoria se fragmenta y una reserva puede fallar, lo que en el aire significa bad_alloc o un crash sin poder reiniciar.

4. Responde: corre tu programa con `-fsanitize=address,undefined` y sin. ¿Lo usarías en el dron? ¿Dónde sí?

con sanitizers tardó 0.012 s y sin ellos 0.003 s, unas 4 veces más. La salida es la misma. No lo usaría en el dron: agrega tiempo, ocupa mucha memoria extra y su reacción ante un error es abortar el programa

## Qué construcciones nuevas usa este laboratorio

Ninguna en el código que escribes: `std::vector`, `std::map`, `std::unique_ptr`, clases y arreglos ya los conoces. Lo nuevo es compilar con `-O2` y medir. `contador_reservas.h` reemplaza el `operator new` de todo el programa, algo que el curso no vio: se usa solo para medir.

## Antes de la próxima sesión

La próxima sesión no tiene clase. Hasta el domingo de la Semana 14 tienes los Ejercicios 2 y 3 de hoy y el Laboratorio Integrador II ([`laboratorios/semana-14-sesion-02/`](../semana-14-sesion-02/)), que junta en un solo proyecto los temas de la Semana 8 a la Semana 13. Hoy también se asigna el Proyecto Final (PSet 4), en [`psets/pset-04/`](../../psets/pset-04/).

Hoy cada ventaja de C++ salió de controlar algo: dónde vive la memoria, cuándo se pide, qué hace el procesador en cada paso. Ese control también es la fuente de los errores que viste en el semestre (un puntero colgante, un data race). En el sistema de tu Proyecto Final, ¿qué tendrías que controlar tú, y cómo vas a comprobar que no rompiste nada?

Tendría que controlar quién es dueño de cada objeto (con unique_ptr o shared_ptr en vez de new y delete sueltos, para no dejar punteros colgantes) cómo se comparte la información entre hilos (con mutex y lock_guard alrededor de cada dato compartido, para evitar data races)