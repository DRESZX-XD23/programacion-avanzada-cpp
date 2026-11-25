#pragma once

#include <map>
#include <memory>
#include <optional>
#include <stdexcept>

// Laboratorio Integrador II: el catalogo de la cafeteria del campus.
//
// Cada producto sabe calcular su precio. El catalogo los guarda a traves de
// la base, y los dos cocineros lo consultan al mismo tiempo.

class Producto {
public:
    virtual ~Producto() {}

    void setCodigo(int nuevoCodigo) {
        codigo = nuevoCodigo;
    }

    int getCodigo() {
        return codigo;
    }

    virtual double precio() = 0;

private:
    int codigo;
};

// Una bebida grande cuesta una vez y media su precio base.
class Bebida : public Producto {
public:
    Bebida() {
        setCodigo(0);
        precioBase = 0;
        grande = false;
    }

    void setDatos(int codigo, double base, bool esGrande) {
        setCodigo(codigo);
        precioBase = base;
        grande = esGrande;
    }

    double precio() override {
        if (grande) {
            return precioBase * 1.5;
        }
        return precioBase;
    }

private:
    double precioBase;
    bool grande;
};

class Plato : public Producto {
public:
    Plato() {
        setCodigo(0);
        precioFijo = 0;
    }

    void setDatos(int codigo, double nuevoPrecio) {
        setCodigo(codigo);
        precioFijo = nuevoPrecio;
    }

    double precio() override {
        return precioFijo;
    }

private:
    double precioFijo;
};

// Un combo tiene una bebida y un plato, y cuesta la suma de los dos con un
// 10% de descuento.
class Combo : public Producto {
public:
    Combo(int codigo, Bebida nuevaBebida, Plato nuevoPlato)
        : bebida(nuevaBebida), plato(nuevoPlato) {
        setCodigo(codigo);
    }

    double precio() override {
        return (bebida.precio() + plato.precio()) * 0.9;
    }

private:
    Bebida bebida;
    Plato plato;
};

class Catalogo {
public:
    // Agrega el producto. Lanza std::invalid_argument("precio no positivo")
    // si su precio es menor o igual a 0, y std::invalid_argument("codigo
    // repetido") si ya hay uno con el mismo codigo. Si lanza, no agrega nada.
    void agregar(std::unique_ptr<Producto> producto) {
        if (producto->precio() <= 0) {
            throw std::invalid_argument("precio no positivo");
        }
        int codigo = producto->getCodigo();
        if (productos.count(codigo) > 0) {
            throw std::invalid_argument("codigo repetido");
        }
        productos[codigo] = std::move(producto);
    }

    // El precio del producto con ese codigo, o vacio si no esta.
    std::optional<double> precioDe(int codigo) {
        auto it = productos.find(codigo);
        if (it == productos.end()) {
            return std::nullopt;
        }
        return it->second->precio();
    }

    int cantidad() {
        return productos.size();
    }

private:
    std::map<int, std::unique_ptr<Producto>> productos;
};