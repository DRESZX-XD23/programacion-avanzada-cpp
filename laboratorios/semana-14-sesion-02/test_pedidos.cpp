#include <gtest/gtest.h>

#include <atomic>
#include <stdexcept>
#include <thread>

#include "pedidos.h"

// Pruebas de las tres clases. Las dos primeras ya estan escritas; las
// demas te tocan (ver el README).

TEST(ColaDePedidos, EntregaEnElOrdenEnQueLlegaron) {
    ColaDePedidos cola;
    Pedido primero;
    primero.id = 1;
    primero.producto = 2;
    primero.cantidad = 1;
    Pedido segundo;
    segundo.id = 2;
    segundo.producto = 3;
    segundo.cantidad = 2;
    cola.agregar(primero);
    cola.agregar(segundo);
    EXPECT_EQ(cola.tomar()->id, 1);
    EXPECT_EQ(cola.tomar()->id, 2);
}

TEST(Inventario, DescuentaCuandoAlcanza) {
    Inventario inventario;
    inventario.registrar(1, 10);
    EXPECT_TRUE(inventario.descontar(1, 4));
    EXPECT_EQ(inventario.unidades(1), 6);
}

// TODO 5

TEST(ColaDePedidos, VaciaDevuelveNullopt) {
    ColaDePedidos cola;
    EXPECT_FALSE(cola.tomar().has_value());
    EXPECT_EQ(cola.pendientes(), 0);
}

TEST(Inventario, NoDescuentaSiNoAlcanza) {
    Inventario inventario;
    inventario.registrar(1, 3);
    EXPECT_FALSE(inventario.descontar(1, 5));
    EXPECT_EQ(inventario.unidades(1), 3);
}

TEST(Inventario, ProductoDesconocidoLanza) {
    Inventario inventario;
    inventario.registrar(1, 10);
    EXPECT_THROW(inventario.descontar(99, 1), std::invalid_argument);
}

TEST(Inventario, CantidadNoPositivaLanza) {
    Inventario inventario;
    inventario.registrar(1, 10);   // el producto existe: debe lanzar por la cantidad
    EXPECT_THROW(inventario.descontar(1, 0), std::invalid_argument);
    EXPECT_THROW(inventario.descontar(1, -2), std::invalid_argument);
    EXPECT_EQ(inventario.unidades(1), 10);
}

TEST(Inventario, DosHilosNoVendenDeMas) {
    Inventario inventario;
    inventario.registrar(1, 1000);
    std::atomic<int> logrados = 0;   // lo suben los dos hilos a la vez

    auto vendedor = [&]() {
        for (int i = 0; i < 1000; i++) {
            if (inventario.descontar(1, 1)) {
                logrados++;
            }
        }
    };

    std::thread h1(vendedor);
    std::thread h2(vendedor);
    h1.join();
    h2.join();

    EXPECT_EQ(inventario.unidades(1), 0);
    EXPECT_EQ(logrados, 1000);
}