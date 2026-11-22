#include <iostream>
#include <vector>

class HistorialDePasos {
private:
    std::vector<int> pasos;
public:
    bool registrar(int cantidad) {
        if (cantidad < 0) {
            return false;
        }
        pasos.push_back(cantidad);
        return true;
    }
    int dias() {
        return pasos.size();
    }
    double promedio() {
        if (pasos.empty()) {
            return 0;
        }
        double suma = 0;
        for (int p : pasos) {
            suma += p;
        }
        return suma / pasos.size();
    }
    int diasSobreMeta(int meta) {
        int contador = 0;
        for (int p : pasos) {
            if (p >= meta) {
                contador++;
            }
        }
        return contador;
    }
    int mejorRacha(int meta) {
        int actual = 0;
        int mejor = 0;
        for (int p : pasos) {
            if (p >= meta) {
                actual++;
                if (actual > mejor) {
                    mejor = actual;
                }
            } else {
                actual = 0;
            }
        }
        return mejor;
    }
};

int main() {
    HistorialDePasos historial;
    historial.registrar(8000);
    historial.registrar(12000);
    historial.registrar(10500);
    std::cout << "Registrar -50: " << historial.registrar(-50) << std::endl;
    historial.registrar(4000);
    historial.registrar(11000);
    historial.registrar(13000);
    historial.registrar(9999);
    historial.registrar(10000);

    std::cout << "Dias registrados: " << historial.dias() << std::endl;
    std::cout << "Promedio: " << historial.promedio() << std::endl;
    std::cout << "Dias con meta: " << historial.diasSobreMeta(10000) << std::endl;
    std::cout << "Mejor racha: " << historial.mejorRacha(10000) << std::endl;
    return 0;
}