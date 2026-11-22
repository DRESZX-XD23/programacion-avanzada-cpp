#include <iostream>

class Envio {
public:
    virtual ~Envio() {
    }
    virtual double costo() = 0;
};

class EnvioNacional : public Envio {
private:
    double pesoKg;
public:
    EnvioNacional(double peso) {
        if (peso < 0) {
            pesoKg = 0;
        } else {
            pesoKg = peso;
        }
    }
    double costo() override {
        return 2 + 1.5 * pesoKg;
    }
};

class EnvioInternacional : public Envio {
private:
    double pesoKg;
public:
    EnvioInternacional(double peso) {
        if (peso < 0) {
            pesoKg = 0;
        } else {
            pesoKg = peso;
        }
    }
    double costo() override {
        return 10 + 4 * pesoKg;
    }
};

void imprimirCosto(Envio* envio) {
    std::cout << "Costo: " << envio->costo() << std::endl;
}

Envio* masBarato(Envio* a, Envio* b) {
    if (b->costo() < a->costo()) {
        return b;
    }
    return a;
}

int main() {
    EnvioNacional nacional(3);
    EnvioInternacional internacional(0.5);
    EnvioNacional negativo(-4);

    imprimirCosto(&nacional);
    imprimirCosto(&internacional);
    imprimirCosto(&negativo);

    Envio* barato = masBarato(&nacional, &internacional);
    std::cout << "El mas barato cuesta " << barato->costo() << std::endl;
    return 0;
}
