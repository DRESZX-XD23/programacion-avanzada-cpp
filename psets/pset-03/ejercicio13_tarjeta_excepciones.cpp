// Ejercicio 13: TarjetaDeTransporte (lanzar excepciones)

#include <iostream>
#include <stdexcept>

class TarjetaDeTransporte {
private:
    double saldo;
public:
    TarjetaDeTransporte() {
        saldo = 0;
    }
    void recargar(double monto) {
        if (monto <= 0) {
            throw std::invalid_argument("monto no positivo");
        }
        saldo += monto;
    }
    void pagar(double tarifa) {
        if (tarifa <= 0) {
            throw std::invalid_argument("tarifa no positiva");
        }
        if (tarifa > saldo) {
            throw std::runtime_error("saldo insuficiente");
        }
        saldo -= tarifa;          
    }
    double getSaldo() {
        return saldo;
    }
};

int main() {
    TarjetaDeTransporte tarjeta;
    tarjeta.recargar(5);
    std::cout << "Saldo: " << tarjeta.getSaldo() << std::endl;

    try {
        tarjeta.pagar(0.45);
        std::cout << "Pago aceptado, saldo: " << tarjeta.getSaldo() << std::endl;
        tarjeta.recargar(-2);
        std::cout << "Esta linea no debe imprimirse" << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Error de dato: " << e.what() << std::endl;
    }

    try {
        tarjeta.pagar(20);
    } catch (const std::invalid_argument& e) {
        std::cout << "Error de dato: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Error de operacion: " << e.what() << std::endl;
    }
    std::cout << "Saldo sin cambios: " << tarjeta.getSaldo() << std::endl;

    try {
        tarjeta.pagar(-1);
    } catch (const std::exception& e) {
        std::cout << "Error de dato: " << e.what() << std::endl;
    }
    std::cout << "Fin" << std::endl;
    return 0;
}