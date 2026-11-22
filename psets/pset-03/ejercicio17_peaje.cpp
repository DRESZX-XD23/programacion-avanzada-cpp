// Ejercicio 17: Vehiculo, Camion y Bus en el peaje (arreglo de punteros a la base)

#include <iostream>

class Vehiculo {
private:
    double tarifaBase;
public:
    Vehiculo() {
        tarifaBase = 0;
    }
    virtual ~Vehiculo() {
    }
    void setTarifaBase(double t) {
        tarifaBase = t;
    }
    double getTarifaBase() {
        return tarifaBase;
    }
    virtual double peaje() {
        return tarifaBase;
    }
};

class Camion : public Vehiculo {
private:
    int ejes;
public:
    Camion(double tarifa, int e) {
        setTarifaBase(tarifa);           // tarifaBase es privada de Vehiculo
        ejes = e;
    }
    double peaje() override {
        return getTarifaBase() + 1.5 * ejes;
    }
};

class Bus : public Vehiculo {
private:
    int pasajeros;
public:
    Bus(double tarifa, int p) {
        setTarifaBase(tarifa);
        pasajeros = p;
    }
    double peaje() override {
        if (pasajeros > 30) {
            return 2 * getTarifaBase();
        }
        return getTarifaBase();
    }
};

double recaudacion(Vehiculo* fila[], int cantidad) {
    double suma = 0;
    for (int i = 0; i < cantidad; i++) {
        suma += fila[i]->peaje();        // virtual: cada uno usa su version
    }
    return suma;
}

int main() {
    Vehiculo comun;
    comun.setTarifaBase(1);
    Camion camion(2, 4);
    Bus busLleno(2, 45);
    Bus busVacio(2, 12);

    Vehiculo* fila[4] = {&comun, &camion, &busLleno, &busVacio};

    for (int i = 0; i < 4; i++) {
        std::cout << "Vehiculo " << i << " paga: " << fila[i]->peaje() << std::endl;
    }
    std::cout << "Recaudacion: " << recaudacion(fila, 4) << std::endl;
    return 0;
}