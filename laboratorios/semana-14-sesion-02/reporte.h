#pragma once

#include <algorithm>
#include <numeric>
#include <optional>
#include <set>
#include <vector>

#include "pedidos.h"

// Laboratorio Integrador II: el reporte de cierre del dia. Se calcula al
// final, con un solo hilo, sobre la copia de las ventas.

// La suma del total de todas las ventas.
inline double totalVendido(std::vector<Venta> ventas) {
    return std::accumulate(ventas.begin(), ventas.end(), 0.0,
                           [](double suma, const Venta& v) {
                               return suma + v.total;
                           });
}

// La venta de mayor total, o vacio si no hay ventas.
inline std::optional<Venta> ventaMayor(std::vector<Venta> ventas) {
    if (ventas.empty()) {
        return std::nullopt;
    }
    auto it = std::max_element(ventas.begin(), ventas.end(),
                               [](const Venta& a, const Venta& b) {
                                   return a.total < b.total;
                               });
    return *it;
}

// Cuantas ventas tienen un total mayor que limite.
inline int ventasSobre(std::vector<Venta> ventas, double limite) {
    return static_cast<int>(std::count_if(ventas.begin(), ventas.end(),
                                          [limite](const Venta& v) {
                                              return v.total > limite;
                                          }));
}

// Cuantas unidades de ese producto se vendieron en total.
inline int unidadesVendidas(std::vector<Venta> ventas, int producto) {
    return std::accumulate(ventas.begin(), ventas.end(), 0,
                           [producto](int suma, const Venta& v) {
                               if (v.producto == producto) {
                                   return suma + v.cantidad;
                               }
                               return suma;
                           });
}

// true si ningun id de pedido aparece en dos ventas.
inline bool idsSinRepetir(std::vector<Venta> ventas) {
    std::set<int> ids;
    int total = ventas.size();
    for (int i = 0; i < total; i++) {
        ids.insert(ventas[i].id);
    }
    int distintos = ids.size();
    return distintos == total;
}