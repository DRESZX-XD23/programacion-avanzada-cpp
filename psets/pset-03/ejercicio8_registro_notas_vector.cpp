#include <iostream>
#include <vector>

class RegistroDeNotas {
private:
    std::vector<double> notas;
public:
    bool agregar(double nota) {
        if (nota >= 0 && nota <= 20) {
            notas.push_back(nota);
            return true;
        }
        return false;
    }
    int cantidad() {
        return notas.size();
    }
    double promedio() {
        if (notas.empty()) { return 0; }
        double suma = 0;
        for (double nota : notas) {
            suma = suma + nota;
        }
        return suma / notas.size();
    }
    double mejor() {
        if (notas.empty()) { return 0; }
        double alta = notas[0];
        for (double nota : notas) {
            if (nota > alta) { alta = nota; }
        }
        return alta;
    }
    int cuantasDesde(double minimo) {
        int contador = 0;
        for (double nota : notas) {
            if (nota >= minimo) { contador++; }
        }
        return contador;
    }
    double ultima() {
        if (notas.empty()) { return 0; }
        return notas.back();
    }
};

int main() {
    RegistroDeNotas registro;
    registro.agregar(15.0);
    registro.agregar(19.5);
    registro.agregar(12.5);
    registro.agregar(18.5);
    std::cout << "Agregar 25: " << registro.agregar(25) << std::endl;
    registro.agregar(13.0);

    std::cout << "Notas registradas: " << registro.cantidad() << std::endl;
    std::cout << "Promedio: " << registro.promedio() << std::endl;
    std::cout << "Mejor nota: " << registro.mejor() << std::endl;
    std::cout << "Notas desde 16: " << registro.cuantasDesde(16) << std::endl;
    std::cout << "Ultima nota: " << registro.ultima() << std::endl;
    return 0;
}