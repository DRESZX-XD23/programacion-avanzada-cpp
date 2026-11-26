#include <iostream>

#include "contador_reservas.h"

const int CAPACIDAD = 64;
const int LECTURAS = 1000000;

class BufferCircular {
public:
    BufferCircular() {
        inicio = 0;
        cantidad = 0;
    }

    void agregar(double valor) {
        if (cantidad < CAPACIDAD) {
            lecturas[(inicio + cantidad) % CAPACIDAD] = valor;
            cantidad++;
        } else {
            lecturas[inicio] = valor;
            inicio = (inicio + 1) % CAPACIDAD;
        }
    }

    int getCantidad() {
        return cantidad;
    }

    double masAntigua() {
        if (cantidad == 0) {
            return 0;
        }
        return lecturas[inicio];
    }

    double promedio() {
        if (cantidad == 0) {
            return 0;
        }
        double suma = 0;
        for (int i = 0; i < cantidad; i++) {
            suma += lecturas[(inicio + i) % CAPACIDAD];
        }
        return suma / cantidad;
    }

    double minimo() {
        if (cantidad == 0) {
            return 0;
        }
        double menor = lecturas[inicio];
        for (int i = 1; i < cantidad; i++) {
            double valor = lecturas[(inicio + i) % CAPACIDAD];
            if (valor < menor) {
                menor = valor;
            }
        }
        return menor;
    }

private:
    double lecturas[CAPACIDAD];
    int inicio;
    int cantidad;
};

int main() {
    BufferCircular buffer;
    long long reservasAntes = reservasHechas;

    unsigned int semilla = 2026;
    for (int i = 0; i < LECTURAS; i++) {
        semilla = semilla * 1103515245 + 12345;
        double lectura = 60.0 + ((semilla >> 8) % 2400) / 100.0;
        buffer.agregar(lectura);
    }

    long long reservasDurante = reservasHechas - reservasAntes;
    std::cout << "Lecturas guardadas: " << buffer.getCantidad() << std::endl;
    std::cout << "Mas antigua: " << buffer.masAntigua() << std::endl;
    std::cout << "Promedio de las ultimas 64: " << buffer.promedio() << std::endl;
    std::cout << "Minimo de las ultimas 64: " << buffer.minimo() << std::endl;
    std::cout << "Reservas de memoria mientras corria el sensor: " << reservasDurante << std::endl;
    return 0;
}