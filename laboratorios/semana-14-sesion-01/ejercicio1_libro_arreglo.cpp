#include <iostream>
#include <vector>

const int PRECIO_MINIMO = 10000;
const int NIVELES = 1000;
const int EVENTOS = 20000000;

class LibroArreglo {
public:
    LibroArreglo() {
        cantidades.reserve(NIVELES);
        for (int i = 0; i < NIVELES; i++) {
            cantidades.push_back(0);
        }
    }

    void agregar(int precio, int cantidad) {
        cantidades[precio - PRECIO_MINIMO] += cantidad;
    }

    void cancelar(int precio, int cantidad) {
        int& casilla = cantidades[precio - PRECIO_MINIMO];
        if (casilla <= cantidad) {
            casilla = 0;
        } else {
            casilla -= cantidad;
        }
    }

    int cantidadEn(int precio) {
        return cantidades[precio - PRECIO_MINIMO];
    }

private:
    std::vector<int> cantidades;
};

int main() {
    LibroArreglo libro;
    unsigned int semilla = 12345;
    long long sumaConsultas = 0;
    for (int i = 0; i < EVENTOS; i++) {
        semilla = semilla * 1103515245 + 12345;
        int precio = PRECIO_MINIMO + (semilla >> 8) % NIVELES;
        int cantidad = 1 + (semilla >> 20) % 100;
        if ((semilla >> 4) % 3 == 0) {
            libro.cancelar(precio, cantidad);
        } else {
            libro.agregar(precio, cantidad);
        }
        sumaConsultas += libro.cantidadEn(precio);
    }
    long long total = 0;
    for (int precio = PRECIO_MINIMO; precio < PRECIO_MINIMO + NIVELES; precio++) {
        total += libro.cantidadEn(precio);
    }
    std::cout << "Acciones en el libro: " << total << std::endl;
    std::cout << "Suma de las consultas: " << sumaConsultas << std::endl;
    return 0;
}