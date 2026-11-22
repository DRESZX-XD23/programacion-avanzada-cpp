#include <iostream>

class Encendible {
public:
    virtual ~Encendible() {
    }
    virtual void encender() = 0;
    virtual void apagar() = 0;
    virtual bool estaEncendido() = 0;
};

class Regulable {
public:
    virtual ~Regulable() {
    }
    virtual int nivel() = 0;
    virtual void subir() = 0;
    virtual void bajar() = 0;
};

class LamparaInteligente : public Encendible, public Regulable {
private:
    bool encendida;
    int brillo;
public:
    LamparaInteligente() {
        encendida = false;
        brillo = 0;
    }
    void encender() override {
        encendida = true;
        if (brillo == 0) {
            brillo = 5;
        }
    }
    void apagar() override {
        encendida = false;
        brillo = 0;
    }
    bool estaEncendido() override {
        return encendida;
    }
    int nivel() override {
        return brillo;
    }
    void subir() override {
        if (encendida && brillo < 10) {
            brillo++;
        }
    }
    void bajar() override {
        if (encendida && brillo > 1) {
            brillo--;
        }
    }
};

void subirAlMaximo(Regulable* r) {
    while (r->nivel() < 10) {
        r->subir();
    }
}

void apagarSiEstaEncendido(Encendible* e) {
    if (e->estaEncendido()) {
        e->apagar();
    }
}

int main() {
    LamparaInteligente lampara;
    Encendible* encendible = &lampara;
    Regulable* regulable = &lampara;

    std::cout << std::boolalpha;
    std::cout << "Encendida al inicio: " << encendible->estaEncendido() << std::endl;

    regulable->subir();
    std::cout << "Nivel tras subir apagada: " << regulable->nivel() << std::endl;

    encendible->encender();
    std::cout << "Nivel al encender: " << regulable->nivel() << std::endl;

    subirAlMaximo(regulable);
    std::cout << "Nivel al maximo: " << regulable->nivel() << std::endl;

    regulable->bajar();
    std::cout << "Nivel tras bajar: " << regulable->nivel() << std::endl;

    apagarSiEstaEncendido(encendible);
    std::cout << "Encendida al final: " << encendible->estaEncendido() << std::endl;
    std::cout << "Nivel al final: " << regulable->nivel() << std::endl;
    return 0;
}