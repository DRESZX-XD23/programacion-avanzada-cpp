// Ejercicio 13: AlmacenNotas (RAII con new[] y delete[])
//
// Completa el constructor, el destructor y los metodos marcados con TODO.
// No cambies las firmas ni el main().
//
// Compilar: g++ -std=c++20 -Wall -Wextra -g -o ejercicio13 ejercicio13_almacen_notas.cpp
// Ejecutar: ./ejercicio13
//
// Salida esperada:
// Nota 0: 18.5
// Nota 1: 15
// Nota 2: 20
// Almacen de notas liberado

#include <iostream>
using namespace std;
class AlmacenNotas {
private:
    double* notas;
    int cantidad;
public:
    AlmacenNotas(int n) {
        cantidad=n;
        notas = new double[n]; 
        for(int k=0;k<n;k++){
            notas[k]=0;
        }
        // TODO: asigna cantidad = n.
        // TODO: reserva con new[] un arreglo de cantidad doubles y guardalo en notas.
        // TODO: en un bucle, inicializa cada posicion de notas en 0.0.
    }
    ~AlmacenNotas() {
    delete[] notas;
    cout<<"Almacen de notas liberado"<<endl;
        // TODO: libera notas con delete[].
        // TODO: imprime "Almacen de notas liberado" seguido de un salto de linea.
    }
    bool setNota(int indice, double valor) {
        if(indice >=0 and indice <cantidad and valor <=20 and valor>=0 ){
            notas[indice]=valor;
            return true; 
        }else{return false;}
        // TODO: valida que indice este entre 0 (incluido) y cantidad (excluido),
        // y que valor este entre 0 y 20 (ambos incluidos).
    }
    double getNota(int indice) {
        // TODO: devuelve notas[indice].
        return notas[indice];
    }
};

int main() {
    AlmacenNotas almacen1(3);
    almacen1.setNota(0, 18.5);
    almacen1.setNota(1, 15.0);
    almacen1.setNota(2, 20.0);
    std::cout << "Nota 0: " << almacen1.getNota(0) << std::endl;
    std::cout << "Nota 1: " << almacen1.getNota(1) << std::endl;
    std::cout << "Nota 2: " << almacen1.getNota(2) << std::endl;
    return 0;
}
