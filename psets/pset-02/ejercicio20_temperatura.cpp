// Ejercicio 20: Temperatura (desde cero, operator+ y operator<<)
//
// Este archivo no tiene codigo de partida. Escribe tu de tu propia clase,
// tus propios includes y tu propio main().
//
#include <iostream>
using namespace std;
class Temperatura{
private:
double grados;
public:
Temperatura(double gradosIniciales){
    grados= gradosIniciales;}
double getGrados(){ return grados;}

Temperatura operator+(Temperatura otro){
double Nuevatemperatura= grados + otro.grados;
return Temperatura(Nuevatemperatura);
}

};


// Disena la clase Temperatura: atributo privado grados (double).
// Constructor Temperatura(double gradosIniciales) que asigna grados por
// asignacion directa (sin validar, sin setter). Getter double getGrados().
// operator+ como metodo miembro, que recibe otro Temperatura por valor y
// devuelve un Temperatura nuevo con la suma de los grados de ambos.


std::ostream& operator<<(std::ostream& os, Temperatura d){
os << d.getGrados() << " grados";
    return os;
}

// operator<< como funcion libre (fuera de la clase), que recibe
// std::ostream& y un Temperatura por valor, e imprime el valor de grados
// seguido de " grados". Debe devolver el std::ostream& recibido.
int main(void){
Temperatura v1(20.5);
Temperatura v2(5.5);
Temperatura v3(v1+v2);

cout << v1 << endl;
cout << v2 << endl;
cout << v3 << endl;
    return 0;
}
//
// En main(): crea dos objetos Temperatura, uno con 20.5 grados y otro con
// 5.5 grados. Crea un tercero sumando los dos primeros con operator+.
// Imprime los tres objetos, cada uno en su propia linea, usando cout con
// tu operator<<.
//
// Compilar: g++ -std=c++20 -Wall -Wextra -g -o ejercicio20 ejercicio20_temperatura.cpp
// Ejecutar: ./ejercicio20
//
// Salida esperada:
// 20.5 grados
// 5.5 grados
// 26 grados
