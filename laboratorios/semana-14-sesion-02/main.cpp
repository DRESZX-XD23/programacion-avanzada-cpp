#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <thread>
#include <vector>

#include "pedidos.h"
#include "productos.h"
#include "reporte.h"

// Laboratorio Integrador II: un dia de la cafeteria. No cambies este main:
// al final verifica que no se perdio ni se repitio ningun pedido, y que el
// inventario y las ventas cuadran.

const int CAJAS = 3;
const int PEDIDOS_POR_CAJA = 20000;
const int PRODUCTOS = 5;
const int UNIDADES_INICIALES[PRODUCTOS] = {30000, 30000, 30000, 30000, 900};

void armarCatalogo(Catalogo* catalogo) {
    std::unique_ptr<Bebida> cafe = std::make_unique<Bebida>();
    cafe->setDatos(1, 1.5, false);
    std::unique_ptr<Bebida> jugo = std::make_unique<Bebida>();
    jugo->setDatos(2, 2.0, true);
    std::unique_ptr<Plato> almuerzo = std::make_unique<Plato>();
    almuerzo->setDatos(3, 4.5);
    std::unique_ptr<Plato> galleta = std::make_unique<Plato>();
    galleta->setDatos(5, 1.0);

    Bebida jugoDelCombo;
    jugoDelCombo.setDatos(0, 2.0, true);
    Plato almuerzoDelCombo;
    almuerzoDelCombo.setDatos(0, 4.5);

    catalogo->agregar(std::move(cafe));
    catalogo->agregar(std::move(jugo));
    catalogo->agregar(std::move(almuerzo));
    catalogo->agregar(std::make_unique<Combo>(4,