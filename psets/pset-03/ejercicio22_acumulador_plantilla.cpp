#include <iostream>

template <typename T>
class Acumulador {
private:
    T total;
    T maximo;
    int cantidad;
public:
    Acumulador() {
        total = T();
        maximo = T();
        cantidad = 0;
    }
    void agregar(T valor) {
        if (cantidad == 0 || valor > maximo) {
            maximo = valor;
        }
        total = total + valor;
        cantidad++;
    }
    T getTotal() {
        return total;
    }
    T getMaximo() {
        return maximo;
    }
    int getCantidad() {
        return cantidad;
    }
    double promedio() {
        if (cantidad == 0) {
            return 0;
        }
        return static_cast<double>(total) / cantidad;
    }
    void reiniciar() {
        total = T();
        maximo = T();
        cantidad = 0;
    }
};

int main() {
    Acumulador<int> goles;
    goles.agregar(2);
    goles.agregar(0);
    goles.agregar(5);
    goles.agregar(1);

    Acumulador<double> diferencias;
    diferencias.agregar(-3.5);
    diferencias.agregar(-1.25);
    diferencias.agregar(-2.0);

    std::cout << "Goles: " << goles.getTotal() << " en " << goles.getCantidad()
              << " partidos, maximo " << goles.getMaximo()
              << ", promedio " << goles.promedio() << std::endl;
    std::cout << "Diferencias: total " << diferencias.getTotal()
              << ", maximo " << diferencias.getMaximo() << std::endl;

    goles.reiniciar();
    std::cout << "Despues de reiniciar: " << goles.getCantidad()
              << " partidos, promedio " << goles.promedio() << std::endl;
    return 0;
}