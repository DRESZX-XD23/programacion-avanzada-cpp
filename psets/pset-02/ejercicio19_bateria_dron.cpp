// Ejercicio 19: Bateria y Dron (desde cero, composicion)
//
// Este archivo no tiene codigo de partida. Escribe tu de tu propia clase,
// tus propios includes y tu propio main().
//
#include <iostream>
using namespace std;
// Disena dos clases:
//

class Bateria{
private:
int cargaPorcentaje;
public:

bool setcargaPorcentaje(int c){
    if(c >=0 and c <=100){
        
        cargaPorcentaje=c;
        return true;
    }else return false;
}

int getCargaporcentaje(){return cargaPorcentaje;}

};
// Bateria: atributo privado cargaPorcentaje (int). Setter bool
// setCargaPorcentaje(int c) valido si c esta entre 0 y 100 (ambos
// incluidos). Getter int getCargaPorcentaje().

class Dron{
private:
Bateria bateria;
double altitudMetros;
public:
bool configurarBateria(int c){
return bateria.setcargaPorcentaje(c);

}

// Dron: tiene como atributo privado un objeto Bateria (composicion, no
// herencia) y un atributo privado altitudMetros (double). Metodo bool
// configurarBateria(int c) que delega en el setter de la bateria interna y
// devuelve su resultado.



bool setAltitudMetros(double a){
    if(a <=500 and a >=0){altitudMetros=a;
    return true;}else{
        return false;
    }
}

bool puedeDespegar(){if(bateria.getCargaporcentaje()>=20){
    return true;
}else{return false;}}

};

//Setter bool setAltitudMetros(double a) valido si a
// esta entre 0 y 500 (ambos incluidos). Metodo bool puedeDespegar() que
// devuelve true si la carga de la bateria interna es mayor o igual a 20,
// false en cualquier otro caso (usa el getter publico de Bateria, no
// accedas a su atributo privado).

int main(){
    Dron v1;
    v1.setAltitudMetros(0);
    v1.configurarBateria(10);
    cout<<"Puede despegar con el 10%: ";
    cout<<boolalpha<<v1.puedeDespegar();
    cout<<endl;
    v1.configurarBateria(45);
    cout<<"Puede despegar con el 45%: ";
    cout<<boolalpha<<v1.puedeDespegar();
    cout<<endl;
    return 0;
}
// En main(): crea un Dron. Asignale altitudMetros = 0. Configura su
// bateria con 10% de carga y muestra el resultado de puedeDespegar(),
// precedido por "Puede despegar con 10%: ". Despues reconfigura la bateria
// a 45% y muestra puedeDespegar() otra vez, precedido por "Puede despegar
// con 45%: ". Usa std::boolalpha antes de imprimir cada resultado booleano.
//
// Compilar: g++ -std=c++20 -Wall -Wextra -g -o ejercicio19 ejercicio19_bateria_dron.cpp
// Ejecutar: ./ejercicio19
//
// Salida esperada:
// Puede despegar con 10%: false
// Puede despegar con 45%: true
