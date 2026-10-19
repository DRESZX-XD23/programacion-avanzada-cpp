# Semana 8, Sesión 2: Polimorfismo I, funciones virtuales

## Objetivo de la sesión

Explicar el mecanismo de despacho dinámico mediante funciones virtuales, y predecir el comportamiento de un programa que invoca una función virtual a través de un puntero a la clase base.

## Antes de empezar

**Lectura previa:** ["Demystifying Dynamic Dispatch: A Deep Dive into Virtual Functions, vptr, and vtable", Satya Dirisala](https://medium.com/@satyadirisala/demystifying-dynamic-dispatch-a-deep-dive-into-virtual-functions-vptr-and-vtable-9574c1ad9bed)

**Referencia:** ["virtual function specifier", cppreference](https://en.cppreference.com/w/cpp/language/virtual.html)

Según el artículo, ¿por qué el compilador no puede decidir, al compilar, qué versión de una función virtual se va a ejecutar? ¿Qué guarda el vptr de cada objeto?

no habia lectura, pero supongo que es porque sin virtual o override, siempre se usa la funcion aplicada al padre, sin importarque este en una clase de sus hijas

En el examen, `Camion` hereda de `Vehiculo`. Si escribes `Vehiculo* vehiculo = &camion;` y ambas clases tienen su propio método `describir()`, ¿cuál se ejecuta con `vehiculo->describir()`? ¿De qué depende tu respuesta?

Depende de si describir() está declarado como virtual en Vehiculo. Si no es virtual, se ejecuta Vehiculo::describir(), porque se usa el tipo del puntero. Si es virtual, se ejecuta Camion::describir()

## Ejercicio 1: figuras sin virtual y con virtual

Archivo: [`ejercicio1_figuras_sin_virtual.cpp`](./ejercicio1_figuras_sin_virtual.cpp). `Circulo` y `Rectangulo` heredan de `Figura` y cada una tiene su propio `area()`.

**Respuesta 1, antes de ver la solución:** llamado directamente, `circulo.area()` da 3.14159 y `rectangulo.area()` da 6. Si guardas ambos en `Figura* figuras[2]` y llamas `figuras[i]->describir()`, ¿qué área imprime cada uno?
 
 imprime 0 ,0 por que no tiene el virtual y usa la del padre

**Respuesta 2:** después de anteponer `virtual` a `area()` en `Figura`, sin tocar las derivadas, ¿qué cambia en la salida? `describir()` no es virtual: ¿afecta eso a la llamada a `area()` que hace adentro?


1. cambia que ahora las funciones hijas van a poder usarse dentro del arreglo, con sus propios datos y no los del padre

2. no, ya que solo imprime, no hace nada mas


**La formulación completa, tal como la resuelvo yo:**

class Figura {
    public:
        // TODO (paso 2): antepone "virtual" a este metodo y vuelve a
        // compilar y ejecutar. Compara la salida con la del paso 1.
        virtual double area() {
            return 0.0;
        }

        void describir() {
            std::cout << "Figura de area " << area() << std::endl;
        }
};

class Circulo : public Figura {
    private:
        double radio;
    public:
        Circulo(double nuevoRadio) {
            radio = nuevoRadio;
        }

        double area() {
            return 3.14159 * radio * radio;
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

        double area() {
            return base * altura;
        }
};

int main() {
    Circulo circulo(1.0);
    Rectangulo rectangulo(2.0, 3.0);

    std::cout << "Llamada directa:" << std::endl;
    std::cout << "Circulo: " << circulo.area() << std::endl;
    std::cout << "Rectangulo: " << rectangulo.area() << std::endl;

// hacerla puntero, osea guardar direcciones de mem
// Lo que hace el puntero es que se ejecute la funcion de padre en cada hija y no arriba
// desde el padree
    Figura* figuras[2];
    figuras[0]= &circulo;
    figuras[1]= &rectangulo;
    std::cout<< "Lista de figuraras"<<std::endl;
    
    for(int i=0;i < 2 ; i++){
        figuras[i]->describir(); // como es puntero, usar flecha y ya no punto
    }
    
    // TODO (paso 1): declara un arreglo "Figura* figuras[2];", guarda en
    // figuras[0] la direccion de circulo y en figuras[1] la direccion de
    // rectangulo. Imprime "A traves de Figura*:" y, con un for, llama a
    // figuras[i]->describir() para cada posicion. Compila y ejecuta
    // antes de tocar la clase Figura.

    return 0;
}
// 1 hacer virtual
// 2 hacer puntero al arreglo
## Ejercicio 2: nómina con override

Archivo: [`ejercicio2_nomina_override.cpp`](./ejercicio2_nomina_override.cpp). `Docente` y `Contratista` heredan de `Empleado`, que declara `salarioMensual()` e `imprimirRol()` como virtuales.

**Respuesta 1, antes de ver la solución:** el docente gana 1800 y el contratista trabaja 40 horas a 25 por hora. Corre el programa sin cambiar nada: ¿cuánto imprime para el contratista, y por qué, si `salarioMensual` sí es virtual en la base?

0, porque falta quitar los parametros adentro de lafuncion y poner override como precaucion

**Respuesta 2:** al agregar `override` a los métodos de `Contratista`, ¿qué línea rechaza el compilador y qué dice el mensaje?

la del int adentro de la funcion.

**La formulación completa, tal como la resuelvo yo:**

#include <iostream>

class Empleado {
    private:
        int codigo;
    public:
        void setCodigo(int nuevoCodigo) {
            codigo = nuevoCodigo;
        }

        int getCodigo() {
            return codigo;
        }

        virtual double salarioMensual() {
            return 0.0;
        }

        virtual void imprimirRol() {
            std::cout << "Empleado sin rol";
        }
};

class Docente : public Empleado {
    private:
        double sueldoFijo;
    public:
        Docente(int nuevoCodigo, double nuevoSueldo) {
            setCodigo(nuevoCodigo);
            sueldoFijo = nuevoSueldo;
        }

        // TODO (paso 2): agrega "override" despues de "()" en los dos
        // metodos de esta clase.
        double salarioMensual() override {
            return sueldoFijo;
        }

        void imprimirRol() override{
            std::cout << "Docente";
        }
};

class Contratista : public Empleado {
    private:
        double tarifaPorHora;
        int horasDelMes;
    public:
        Contratista(int nuevoCodigo, double nuevaTarifa, int nuevasHoras) {
            setCodigo(nuevoCodigo);
            tarifaPorHora = nuevaTarifa;
            horasDelMes = nuevasHoras;
        }

        // TODO (paso 2): agrega "override" despues de la lista de
        // parametros en los dos metodos de esta clase y compila. Lee el
        // mensaje de error del compilador antes de corregir nada.
        //
        // TODO (paso 3): corrige el metodo que el compilador rechaza para
        // que de verdad redefina al de Empleado. Las horas ya estan
        // guardadas en el atributo horasDelMes.
        double salarioMensual() override{
            return tarifaPorHora * horasDelMes;
        }

        void imprimirRol() override{
            std::cout << "Contratista";
        }
};

int main() {
    Docente ana(101, 1800.0);
    Contratista luis(202, 25.0, 40);

    Empleado* nomina[2];
    nomina[0] = &ana;
    nomina[1] = &luis;

    double total = 0.0;
    for (int i = 0; i < 2; i++) {
        std::cout << "Codigo " << nomina[i]->getCodigo() << " (";
        nomina[i]->imprimirRol();
        std::cout << "): " << nomina[i]->salarioMensual() << std::endl;
        total = total + nomina[i]->salarioMensual();
    }
    std::cout << "Total de la nomina: " << total << std::endl;

    return 0;
}
// poner virtual
// hacer puntero al arreglo 
//override es un seguro
// quitar 

## Ejercicio 3: cola de notificaciones

Archivo: [`ejercicio3_notificaciones.cpp`](./ejercicio3_notificaciones.cpp). Solo o en pareja.

`main` guarda tres notificaciones distintas en `std::unique_ptr<Notificacion> cola[3]` y llama `cola[i]->enviar()` en cada una. Completa:

- `Notificacion`: decide qué le falta a `enviar()` y a `~Notificacion()` para que el envío y la destrucción se resuelvan según el tipo real de cada objeto.
- `NotificacionCorreo`, `NotificacionSMS` y `NotificacionPush`: herencia pública de `Notificacion`, constructor, `enviar()` y destructor, ambos marcados con `override`. `NotificacionSMS` reserva su arreglo de intentos con `std::make_unique<int[]>`.

La salida esperada exacta está en el encabezado del archivo.

Antes de dar el ejercicio por terminado, responde: si quitas `virtual` del destructor de `Notificacion` y vuelves a compilar con `-fsanitize=address`, ¿qué destructores se imprimen al final, y qué reporta AddressSanitizer?

Nunca aparecen ~NotificacionPush, ~NotificacionSMS ni ~NotificacionCorreo. 
 new-delete-type-mismatch 
## Compilar y ejecutar

```
g++ -std=c++20 -Wall -Wextra -g ejercicio1_figuras_sin_virtual.cpp -o bin/ejercicio1
./bin/ejercicio1
```

Repite el mismo patrón con `ejercicio2_nomina_override.cpp` y `ejercicio3_notificaciones.cpp`. Para el Ejercicio 3, compila también con AddressSanitizer:

```
g++ -std=c++20 -Wall -Wextra -g -fsanitize=address ejercicio3_notificaciones.cpp -o bin/ejercicio3_asan
./bin/ejercicio3_asan
```

En Mac, el comando `g++` es en realidad Clang: con el Ejercicio 2 sin corregir, Clang muestra una advertencia `-Woverloaded-virtual` que el GCC del Dev Container no muestra. Una advertencia no detiene la compilación; `override` la convierte en un error.

## Qué construcciones nuevas usa este laboratorio

Un puntero a la clase base que apunta a un objeto derivado (`Figura* figura = &circulo;`) y `->` sobre ese puntero; `virtual` antepuesto a un método de la base; `override` después de la lista de parámetros de un método de la derivada; y el destructor `virtual` en una base que se usa a través de punteros o smart pointers.

## Antes de la próxima sesión

**Lectura:** ["SOLID Design Principles with Example Code (C++)", Suresh Jangale](https://medium.com/@sureshjangale137/solid-design-principles-with-examples-e6e8baf5f85f)

`Figura::area()` devuelve 0 solo porque algo tenía que devolver. ¿Tiene sentido crear un objeto que sea solo una `Figura`, sin ser círculo ni rectángulo? ¿Qué debería hacer el compilador si alguien lo intenta?

prohibirlo para que no de error
