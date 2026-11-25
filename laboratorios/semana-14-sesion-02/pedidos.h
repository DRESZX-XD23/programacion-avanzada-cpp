#pragma once

#include <atomic>
#include <map>
#include <mutex>
#include <optional>
#include <stdexcept>
#include <vector>

// Laboratorio Integrador II: los pedidos de la cafeteria del campus.
//
// Tres cajas dejan pedidos en una cola al mismo tiempo. Despues, dos
// cocineros sacan pedidos de la cola al mismo tiempo, descuentan el
// inventario, registran cada venta y anotan el resultado. Cada clase de este
// archivo la usan varios hilos a la vez.

struct Pedido {
    int id;
    int producto;
    int cantidad;
};

struct Venta {
    int id;
    int producto;
    int cantidad;
    double total;
};

// Una cola que pueden usar varios hilos a la vez.
template <typename T>
class ColaSegura {
public:
    ColaSegura() {
        siguiente = 0;
    }

    // Deja un elemento al final de la cola.
    void agregar(T elemento) {
        std::lock_guard<std::mutex> guardia(candado);
        elementos.push_back(elemento);
    }

    // Saca el elemento mas antiguo que no se haya sacado todavia, o
    // std::nullopt si ya no quedan.
    std::optional<T> tomar() {
        std::lock_guard<std::mutex> guardia(candado);
        int total = elementos.size();
        if (siguiente >= total) {
            return std::nullopt;
        }
        T elemento = elementos[siguiente];
        siguiente++;
        return elemento;
    }

    // Cuantos elementos quedan sin tomar.
    int pendientes() {
        std::lock_guard<std::mutex> guardia(candado);
        int total = elementos.size();
        return total - siguiente;
    }

private:
    std::vector<T> elementos;
    int siguiente;
    std::mutex candado;
};

class Inventario {
public:
    // Registra un producto con sus unidades iniciales.
    void registrar(int producto, int unidades) {
        std::lock_guard<std::mutex> guardia(candado);
        stock[producto] = unidades;
    }

    // Descuenta la cantidad del producto si alcanza, y devuelve true. Si no
    // alcanza, no descuenta nada y devuelve false. Lanza
    // std::invalid_argument si el producto no existe o si la cantidad no es
    // positiva.
    bool descontar(int producto, int cantidad) {
        std::lock_guard<std::mutex> guardia(candado);

        if (cantidad <= 0) {
            throw std::invalid_argument("la cantidad debe ser positiva");
        }

        auto it = stock.find(producto);
        if (it == stock.end()) {
            throw std::invalid_argument("producto desconocido");
        }

        if (it->second < cantidad) {
            return false;
        }

        it->second -= cantidad;
        return true;
    }

    // Unidades que quedan del producto (0 si no existe).
    int unidades(int producto) {
        std::lock_guard<std::mutex> guardia(candado);
        if (stock.count(producto) == 0) {
            return 0;
        }
        return stock[producto];
    }

private:
    std::map<int, int> stock;
    std::mutex candado;
};

class Estadisticas {
public:
    Estadisticas() {
        despachados = 0;
        sinStock = 0;
        invalidos = 0;
    }

    void anotarDespachado() {
        despachados++;
    }

    void anotarSinStock() {
        sinStock++;
    }

    void anotarInvalido() {
        invalidos++;
    }

    int getDespachados() {
        return despachados;
    }

    int getSinStock() {
        return sinStock;
    }

    int getInvalidos() {
        return invalidos;
    }

private:
    std::atomic<int> despachados;
    std::atomic<int> sinStock;
    std::atomic<int> invalidos;
};

class RegistroDeVentas {
public:
    void anotar(Venta venta) {
        std::lock_guard<std::mutex> guardia(candado);
        ventas.push_back(venta);
    }

    // Una copia de todas las ventas anotadas hasta ahora.
    std::vector<Venta> todas() {
        std::lock_guard<std::mutex> guardia(candado);
        return ventas;
    }

private:
    std::vector<Venta> ventas;
    std::mutex candado;
};