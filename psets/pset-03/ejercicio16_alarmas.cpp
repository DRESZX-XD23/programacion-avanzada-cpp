// Ejercicio 16: Alarma, AlarmaDeIncendio y AlarmaDeIntrusion (funciones virtuales)

#include <iostream>

class Alarma {
public:
    virtual ~Alarma() {
    }
    virtual int segundosDeAviso() {
        return 10;
    }
    int prioridad() {                  
        return 1;
    }
};

class AlarmaDeIncendio : public Alarma {
private:
    int pisos;
public:
    AlarmaDeIncendio(int p) {
        pisos = p;
    }
    int segundosDeAviso() override {
        return pisos * 15;
    }
    int prioridad() {                  
        return 3;
    }
};

class AlarmaDeIntrusion : public Alarma {
private:
    int sensores;
public:
    AlarmaDeIntrusion(int s) {
        sensores = s;
    }
    int segundosDeAviso() override {
        return sensores * 4;
    }
};

int main() {
    AlarmaDeIncendio incendio(4);
    AlarmaDeIntrusion intrusion(9);

    Alarma* puntero = &incendio;
    std::cout << "Incendio por puntero, aviso: " << puntero->segundosDeAviso() << std::endl;
    std::cout << "Incendio por puntero, prioridad: " << puntero->prioridad() << std::endl;
    std::cout << "Incendio directa, prioridad: " << incendio.prioridad() << std::endl;

    puntero = &intrusion;
    std::cout << "Intrusion por puntero, aviso: " << puntero->segundosDeAviso() << std::endl;

    Alarma comun;
    Alarma* punteroComun = &comun;
    std::cout << "Alarma comun por puntero, aviso: " << punteroComun->segundosDeAviso() << std::endl;
    return 0;
}