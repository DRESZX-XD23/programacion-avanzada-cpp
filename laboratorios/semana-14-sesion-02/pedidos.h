#pragma once

#include <atomic>
#include <map>
#include <mutex>
#include <optional>
#include <stdexcept>
#include <vector>



struct Pedido {
    int id;
    int producto;
    int cantidad;
};

class ColaDePedidos {
public:
    ColaDePedidos() {
        siguiente = 0;
    }

    // Deja un pedido al final de la cola.
    void agregar(Pedido pedido) {
        // TODO 1: el candado protege el push_back de las tres cajas.
        std::lock_guard<std::mutex> guardia(candado);
        pedidos.push_back(pedido);
    }

    std::optional<Pedido> tomar() {
        std::lock_guard<std::mutex> guardia(candado);
        int total = pedidos.size();
        if (siguiente >= total) {
            return std::nullopt;
        }
        Pedido pedido = pedidos[siguiente];
        siguiente++;
        return pedido;
    }

    // Cuantos pedidos quedan sin tomar.
    int pendientes() {
        std::lock_guard<std::mutex> guardia(candado);
        int total = pedidos.size();
        return total - siguiente;
    }

private:
    std::vector<Pedido> pedidos;
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

    bool descontar(int producto, int cantidad) {
        // TODO 3: todo el metodo es una sola seccion critica. Si se lanza
        // una excepcion, el destructor de guardia suelta el candado (RAII).
        std::lock_guard<std::mutex> guardia(candado);

        if (cantidad <= 0) {
            throw std::invalid_argument("la cantidad debe ser positiva");
        }

        auto it = stock.find(producto);
        if (it == stock.end()) {
            throw std::invalid_argument("producto desconocido");
        }

        if (it->second < cantidad) {
            return false;   // no alcanza: no se toca nada
        }

        it->second -= cantidad;
        return true;
    }

    
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