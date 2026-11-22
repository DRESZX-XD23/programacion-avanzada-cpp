#include <iostream>
#include <stdexcept>

class Ascensor {
private:
    int pisoActual;
    double cargaKg;
public:
    Ascensor() {
        pisoActual = 0;
        cargaKg = 0;
    }
    void subirPersona(double kg) {
        if (kg <= 0) {
            throw std::invalid_argument("peso no positivo");
        }
        if (cargaKg + kg > 450) {
            throw std::runtime_error("sobrecarga");
        }
        cargaKg += kg;
    }
    void bajarPersona(double kg) {
        if (kg <= 0) {
            throw std::invalid_argument("peso no positivo");
        }
        if (kg > cargaKg) {
            throw std::runtime_error("no hay tanto peso a bordo");
        }
        cargaKg -= kg;
    }
    void irA(int piso) {
        if (piso < 0 || piso > 10) {
            throw std::out_of_range("piso inexistente");
        }
        pisoActual = piso;
    }
    int getPiso() {
        return pisoActual;
    }
    double getCarga() {
        return cargaKg;
    }
};

int main() {
    Ascensor ascensor;

    try {
        ascensor.subirPersona(80);
        ascensor.subirPersona(95);
        ascensor.subirPersona(120);
        std::cout << "Carga: " << ascensor.getCarga() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    try {
        ascensor.subirPersona(200);
        ascensor.irA(7);
    } catch (const std::runtime_error& e) {
        std::cout << "No se pudo: " << e.what() << std::endl;
    }
    std::cout << "Piso actual: " << ascensor.getPiso() << std::endl;

    try {
        ascensor.irA(12);
    } catch (const std::out_of_range& e) {
        std::cout << "Fuera de rango: " << e.what() << std::endl;
    }

    try {
        ascensor.bajarPersona(-60);
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    ascensor.irA(4);
    std::cout << "Piso " << ascensor.getPiso() << ", carga " << ascensor.getCarga() << std::endl;
    return 0;
}