#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>
#include <thread>
#include <vector>

#include "pedidos.h"
#include "productos.h"
#include "reporte.h"

void agregarMil(ColaSegura<int>* cola) {
    for (int i = 0; i < 1000; i++) {
        cola->agregar(i);
    }
}

void venderMil(Inventario* inventario, int* logradas) {
    for (int i = 0; i < 1000; i++) {
        if (inventario->descontar(1, 1)) {
            (*logradas)++;
        }
    }
}

Venta crearVenta(int id, int producto, int cantidad, double total) {
    Venta venta;
    venta.id = id;
    venta.producto = producto;
    venta.cantidad = cantidad;
    venta.total = total;
    return venta;
}

TEST(ColaSegura, EntregaEnElOrdenEnQueLlegaron) {
    ColaSegura<int> cola;
    cola.agregar(7);
    cola.agregar(9);
    EXPECT_EQ(cola.tomar().value(), 7);
    EXPECT_EQ(cola.tomar().value(), 9);
}

TEST(Inventario, DescuentaCuandoAlcanza) {
    Inventario inventario;
    inventario.registrar(1, 10);
    EXPECT_TRUE(inventario.descontar(1, 4));
    EXPECT_EQ(inventario.unidades(1), 6);
}

TEST(Bebida, GrandeCuestaUnaVezYMedia) {
    Bebida chica;
    chica.setDatos(1, 2.0, false);
    Bebida grande;
    grande.setDatos(2, 2.0, true);
    EXPECT_DOUBLE_EQ(chica.precio(), 2.0);
    EXPECT_DOUBLE_EQ(grande.precio(), 3.0);
}

TEST(Combo, DescuentaDiezPorCientoATravesDeLaBase) {
    Bebida bebida;
    bebida.setDatos(0, 2.0, true);
    Plato plato;
    plato.setDatos(0, 4.5);
    std::unique_ptr<Producto> combo = std::make_unique<Combo>(4, bebida, plato);
    EXPECT_NEAR(combo->precio(), 6.75, 1e-9);
}

TEST(Catalogo, CodigoRepetidoLanzaSinAgregar) {
    Catalogo catalogo;
    std::unique_ptr<Plato> primero = std::make_unique<Plato>();
    primero->setDatos(3, 4.5);
    std::unique_ptr<Plato> segundo = std::make_unique<Plato>();
    segundo->setDatos(3, 5.0);
    catalogo.agregar(std::move(primero));
    EXPECT_THROW(catalogo.agregar(std::move(segundo)), std::invalid_argument);
    EXPECT_EQ(catalogo.cantidad(), 1);
    EXPECT_DOUBLE_EQ(catalogo.precioDe(3).value(), 4.5);
}

TEST(Catalogo, PrecioNoPositivoLanza) {
    Catalogo catalogo;
    std::unique_ptr<Plato> gratis = std::make_unique<Plato>();
    gratis->setDatos(6, 0);
    EXPECT_THROW(catalogo.agregar(std::move(gratis)), std::invalid_argument);
    EXPECT_EQ(catalogo.cantidad(), 0);
}

TEST(Catalogo, ProductoDesconocidoNoTienePrecio) {
    Catalogo catalogo;
    EXPECT_FALSE(catalogo.precioDe(99).has_value());
}

TEST(ColaSegura, VaciaDevuelveNullopt) {
    ColaSegura<double> cola;
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
    inventario.registrar(1, 10);
    EXPECT_THROW(inventario.descontar(1, 0), std::invalid_argument);
    EXPECT_THROW(inventario.descontar(1, -2), std::invalid_argument);
    EXPECT_EQ(inventario.unidades(1), 10);
}

TEST(Reporte, TotalMayorYVentasSobre) {
    std::vector<Venta> ventas;
    ventas.push_back(crearVenta(1, 3, 3, 13.5));
    ventas.push_back(crearVenta(2, 1, 2, 3.0));
    ventas.push_back(crearVenta(3, 4, 3, 20.25));
    EXPECT_DOUBLE_EQ(totalVendido(ventas), 36.75);
    EXPECT_EQ(ventaMayor(ventas).value().id, 3);
    EXPECT_EQ(ventasSobre(ventas, 10), 2);
    EXPECT_EQ(unidadesVendidas(ventas, 3), 3);
}

TEST(Reporte, SinVentasNoHayMayor) {
    std::vector<Venta> ventas;
    EXPECT_FALSE(ventaMayor(ventas).has_value());
}

TEST(ColaSegura, DosHilosNoPierdenElementos) {
    ColaSegura<int> cola;
    std::thread h1(agregarMil, &cola);
    std::thread h2(agregarMil, &cola);
    h1.join();
    h2.join();
    EXPECT_EQ(cola.pendientes(), 2000);
}

TEST(Inventario, DosHilosNoVendenDeMas) {
    Inventario inventario;
    inventario.registrar(1, 1000);
    int logradas1 = 0;
    int logradas2 = 0;
    std::thread h1(venderMil, &inventario, &logradas1);
    std::thread h2(venderMil, &inventario, &logradas2);
    h1.join();
    h2.join();
    EXPECT_EQ(inventario.unidades(1), 0);
    EXPECT_EQ(logradas1 + logradas2, 1000);
}