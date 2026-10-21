# Semana 9, Sesión 1: Polimorfismo II: interfaces y clases abstractas

## Objetivo de la sesión

Diseñar una interfaz común mediante clases abstractas y funciones virtuales puras para un conjunto de clases heterogéneas.

## Antes de empezar

**Lectura previa:** ["SOLID Design Principles with Example Code (C++)", Suresh Jangale](https://medium.com/@sureshjangale137/solid-design-principles-with-examples-e6e8baf5f85f)

**Referencia:** ["Abstract class", cppreference](https://en.cppreference.com/w/cpp/language/abstract_class.html)

Según el artículo, ¿qué dice el principio de inversión de dependencias sobre de quién debe depender una clase de alto nivel? ¿Qué problema describe el principio de segregación de interfaces?

DIP: una clase de alto nivel debe depender de abstracciones no de clases concretas. 

ISP: describe el problema de las interfaces grandes que obligan a las clases a implementar métodos que no usan

La sesión pasada, `Figura::area()` devolvía 0 solo porque algo tenía que devolver. ¿Tiene sentido crear un objeto que sea solo una `Figura`? Si no, ¿qué debería hacer el compilador cuando alguien lo intenta?

dar error, al hacerla funcion pura con el cirtual y el =0

## Ejercicio 1: Figura abstracta

Archivo: [`ejercicio1_figura_abstracta.cpp`](./ejercicio1_figura_abstracta.cpp). La misma jerarquía de la sesión pasada, ahora con `imprimirNombre()` y un `Triangulo`. Compila y córrelo antes de cambiar nada: el triángulo imprime área 0.

**Respuesta 1, antes de ver la solución:** después de convertir `area()` e `imprimirNombre()` en virtuales puras, ¿qué pasa con la línea `Figura generica;` si le quitas el comentario?

Da error

**Respuesta 2:** `Triangulo` no implementa `area()`. ¿En qué línea aparece el error, y qué le falta a `Triangulo` para que se pueda crear?

a triangulo de lalta la funcion area de la padre figura
en la linea de main, en figuras[2] = std::make_unique<Triangulo>(4.0, 3.0)
**La formulación completa, tal como la resuelvo yo:**

#include <iostream>
#include <memory>

// clase abstracta, no se pueden crar objetos de eso
// es una tiene almenos una funcion virtual pura =0
// clase padre, sus clases hijas obligadas a poner todas sus funciones
// siempre poner la padre con PUNTEROS
// Interfaz una clase abstracta que solo tuene FuncinesVirtualesPuras y el destructor   
// clase abstracta ambas puras y otras
class Figura {
    public:
        // TODO (paso 1): ninguna Figura "generica" tiene un area ni un
        // nombre que tenga sentido. Convierte estos dos metodos en
        // funciones virtuales puras.
        virtual double area() =0;
        virtual void imprimirNombre()=0;
        void describir() { // interfaz
            imprimirNombre();
            std::cout << " de area " << area() << std::endl;
        }

        virtual ~Figura() {
        }
};

class Circulo : public Figura {
    private:
        double radio;
    public:
        Circulo(double nuevoRadio) {
            radio = nuevoRadio;
        }

        double area() override {
            return 3.14159 * radio * radio;
        }

        void imprimirNombre() override {
            std::cout << "Circulo";
        }
};

class Rectangulo : public Figura {
    private:
        double base;
        double altura;
    public:
        Rectangulo(double nuevaBase, double nuevaAltura) {
            base = nuevaBase;
            altura = nuevaAltura;
        }

        double area() override {
            return base * altura;
        }

        void imprimirNombre() override {
            std::cout << "Rectangulo";
        }
};

class Triangulo : public Figura {
    private:
        double base;
        double altura;
    public:
        Triangulo(double nuevaBase, double nuevaAltura) {
            base = nuevaBase;
            altura = nuevaAltura;
        }

        void imprimirNombre() override {
            std::cout << "Triangulo";
        }
        double area() override{
            return (base * altura)/2;
        }
        // TODO (paso 3): despues del paso 1, compila y lee el error que
        // aparece en main. Agrega lo que le falta a Triangulo.
};

int main() {
    // TODO (paso 2): despues del paso 1, quita el comentario de la
    // siguiente linea, compila, lee el error y vuelve a comentarla.
    // Figura generica;

    std::unique_ptr<Figura> figuras[3];
    figuras[0] = std::make_unique<Circulo>(1.0);
    figuras[1] = std::make_unique<Rectangulo>(2.0, 3.0);
    figuras[2] = std::make_unique<Triangulo>(4.0, 3.0);

    for (int i = 0; i < 3; i++) {
        figuras[i]->describir();
    }

    return 0;
}


## Durante el ConcepTest

**Tu voto, antes de discutir en pareja** (A, B, C o D):

_(tu voto)_

**Tu razonamiento:**

_(tu respuesta)_

**Después de discutir en pareja, ¿cambiaste de voto? ¿Por qué?**

_(tu respuesta)_

## Ejercicio 2: estación meteorológica

Archivo: [`ejercicio2_estacion_meteorologica.cpp`](./ejercicio2_estacion_meteorologica.cpp). Solo o en pareja.

`EstacionMeteorologica` guarda hasta 3 medidores en `std::unique_ptr<IMedidor> medidores[3]` y arma un reporte con todos. Diseña la interfaz `IMedidor`, implementa `Termometro`, `Barometro` y `Anemometro`, y completa `agregar()` y `reportar()`. `EstacionMeteorologica` no puede mencionar ninguna clase concreta. La salida esperada exacta está en el encabezado del archivo.

Antes de dar el ejercicio por terminado, responde: si mañana agregas un `Higrometro` (humedad en %), ¿qué líneas de `EstacionMeteorologica` tienes que cambiar?

Solo se crea la clase Higrometro : public IMedidor con sus tres métodos. EstacionMeteorologica no cambia.

## Ejercicio 3: dispositivos de oficina

Archivo: [`ejercicio3_dispositivos_oficina.cpp`](./ejercicio3_dispositivos_oficina.cpp). Solo o en pareja.

El archivo compila y corre tal como está, con una sola interfaz `IDispositivoOficina` que obliga a `ImpresoraBasica` a responder a `escanear()` y a `enviarFax()`. Divídela en `IImpresora`, `IEscaner` e `IFax`, haz que cada clase implemente solo las que soporta, y ajusta `imprimirLote`, `escanearLote` y `main`. Las dos salidas, la de antes y la esperada después del cambio, están en el encabezado del archivo.

Antes de escribir código, responde: `Multifuncional` va a heredar de tres clases a la vez. En la Semana 4, una herencia así terminó en el problema del diamante. ¿Por qué aquí no aparece?

 El diamante aparece cuando dos padres heredan de un mismo abuelo y la hija termina con dos copias de él. y aqui no aparece porque no heredan una clase basica en comun
Al terminar, prueba guardar `&basica` en el arreglo de escáneres. ¿Qué dice el compilador?

No compila. El compilador dice que no puede convertir ImpresoraBasica* a IDispositivoQueescanea*, porque ImpresoraBasica no hereda de esa interfaz.

## Compilar y ejecutar

```
g++ -std=c++20 -Wall -Wextra -g ejercicio1_figura_abstracta.cpp -o bin/ejercicio1
./bin/ejercicio1
```

Repite el mismo patrón con `ejercicio2_estacion_meteorologica.cpp` y `ejercicio3_dispositivos_oficina.cpp`.

## Qué construcciones nuevas usa este laboratorio

Función virtual pura (`virtual tipo nombre(parámetros) = 0;`) y clase abstracta; la convención de interfaz del curso (solo virtuales puras públicas y un destructor virtual con cuerpo vacío, sin atributos); e implementar varias interfaces a la vez con la herencia múltiple de la Semana 4, Sesión 1.

## Antes de la próxima sesión

**Lectura:** ["Function and Class Templates in C++: A Practical Guide to Generic Programming", Murat Toğunçhan Düzgün](https://medium.com/@togunchan/function-and-class-templates-in-c-enhancing-flexibility-and-reusability-894bd3d0c84e)

Necesitas una función `mayor` que devuelva el mayor de dos valores para `int`, para `double` y para `char`. Con lo que sabes hoy, ¿cuántas funciones escribes, y qué cambia entre ellas además del tipo?

serian tres, no cambiararia nada, solo el tipo int, double, char