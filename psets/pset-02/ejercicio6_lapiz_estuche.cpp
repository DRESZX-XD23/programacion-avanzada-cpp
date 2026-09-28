// Ejercicio 6: Lapiz y Estuche (composicion con dos miembros)
//
// Completa los metodos marcados con TODO. No cambies las firmas ni el main().
//
// Compilar: g++ -std=c++20 -Wall -Wextra -g -o ejercicio6 ejercicio6_lapiz_estuche.cpp
// Ejecutar: ./ejercicio6
//
// Salida esperada:
// Lapiz 1 es el mas largo: false

#include <iostream>
using namespace std;
class Lapiz {
private:
    double longitudCm;
public:
    bool setLongitudCm(double l) {
        
        if(l>1 and l <=30){
            longitudCm=l;
            return true;
        }else{return false;}
        // TODO: valida que l sea mayor a 1 y menor o igual a 30.
    }
    double getLongitudCm() {
        // TODO: devuelve longitudCm.
        return longitudCm;
    }
};

class Estuche {
private:
    Lapiz lapiz1;
    Lapiz lapiz2;
public:
    bool configurarLapiz1(double l) {
        
        // TODO: delega en lapiz1.setLongitudCm(l) y devuelve su resultado.
        return lapiz1.setLongitudCm(l);
    }
    bool configurarLapiz2(double l) {
        // TODO: delega en lapiz2.setLongitudCm(l) y devuelve su resultado.
        return lapiz2.setLongitudCm(l);
    }
    bool lapizMasLargo() {
        if(lapiz2.getLongitudCm()<=lapiz1.getLongitudCm()){return true;}else{
            return false;
        }
        // TODO: devuelve true si la longitud de lapiz1 es mayor o igual a la de lapiz2.
    }
};

int main() {
    Estuche estuche1;
    estuche1.configurarLapiz1(12.5);
    estuche1.configurarLapiz2(18.0);
    std::cout << "Lapiz 1 es el mas largo: " << std::boolalpha << estuche1.lapizMasLargo() << std::endl;
    return 0;
}
