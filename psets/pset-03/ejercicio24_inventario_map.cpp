#include <iostream>
#include <map>

class Inventario {
private:
    std::map<int, int> stockPorCodigo;
public:
    void ingresar(int codigo, int unidades) {
        if (unidades <= 0) {
            return;
        }
        stockPorCodigo[codigo] += unidades;
    }
    bool retirar(int codigo, int unidades) {
        auto it = stockPorCodigo.find(codigo);
        if (it == stockPorCodigo.end() || it->second < unidades) {
            return false;
        }
        it->second -= unidades;
        return true;
    }
    int stockDe(int codigo) {
        auto it = stockPorCodigo.find(codigo);
        if (it == stockPorCodigo.end()) {
            return 0;
        }
        return it->second;
    }
    int agotados() {
        int contador = 0;
        for (auto it = stockPorCodigo.begin(); it != stockPorCodigo.end(); it++) {
            if (it->second == 0) {
                contador++;
            }
        }
        return contador;
    }
    int codigos() {
        return stockPorCodigo.size();
    }
    void imprimir() {
        for (auto it = stockPorCodigo.begin(); it != stockPorCodigo.end(); it++) {
            std::cout << it->first << ": " << it->second << std::endl;
        }
    }
};

int main() {
    Inventario inventario;
    inventario.ingresar(300, 40);
    inventario.ingresar(120, 15);
    inventario.ingresar(450, 5);
    inventario.ingresar(999, -3);

    std::cout << "Retirar 15 del 120: " << inventario.retirar(120, 15) << std::endl;
    std::cout << "Retirar 10 del 450: " << inventario.retirar(450, 10) << std::endl;
    std::cout << "Retirar 1 del 777: " << inventario.retirar(777, 1) << std::endl;

    std::cout << "Stock del 999: " << inventario.stockDe(999) << std::endl;
    std::cout << "Codigos registrados: " << inventario.codigos() << std::endl;
    std::cout << "Agotados: " << inventario.agotados() << std::endl;
    inventario.imprimir();
    return 0;
}