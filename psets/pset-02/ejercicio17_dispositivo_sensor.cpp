// Ejercicio 17: Dispositivo, DispositivoConectado y SensorTemperatura
// (desde cero, herencia de tres niveles)
//
// Este archivo no tiene codigo de partida. Escribe tu de tu propia clase,
// tus propios includes y tu propio main().
//
// Disena tres clases en cadena:
//
#include <iostream> 
using namespace std;
class Dispositivo{
private:
double consumoWatts;
public:

bool setConsumoWatts(double c){
   if(c>0 and c <=100){ consumoWatts=c;
return true;}else{
    return false;
} }
double getconsumoWatts(){return consumoWatts;}
};
// Dispositivo: atributo privado consumoWatts (double). Setter bool
// setConsumoWatts(double c) valido si c es mayor a 0 y menor o igual a 100.
// Getter double getConsumoWatts().
//
class DispositivoConectado: public Dispositivo{
private:
int canalRed;
public:
bool setCanalRed(int c){
if(c<=11 and c>=1 ){canalRed=c;
return true; }else{
    return false;
}
}

int getCanalRed(){return canalRed;}
}; 
// DispositivoConectado: hereda publicamente de Dispositivo. Agrega atributo
// privado canalRed (int). Setter bool setCanalRed(int c) valido si c esta
// entre 1 y 11 (ambos incluidos). Getter int getCanalRed().
//


class SensorTemperatura: public DispositivoConectado{
private:
double lecturaActual;
public:
bool setlecturaActual(double l){
if(l<=125 and l>=-40 ){lecturaActual=l;
return true; }else{
    return false;
}
}

double getlecturaActual(){return lecturaActual;}

bool alertaCritica(){if(lecturaActual>100){return true;}else{
    return false;
}}
};


// SensorTemperatura: hereda publicamente de DispositivoConectado. Agrega
// atributo privado lecturaActual (double). Setter bool
// setLecturaActual(double l) valido si l esta entre -40 y 125 (ambos
// incluidos). Getter double getLecturaActual(). 
//Metodo bool alertaCritica()
// que devuelve true si lecturaActual es mayor a 100, false en cualquier
// otro caso.
//
int main(){
SensorTemperatura v1;
v1.setConsumoWatts(5.5);
v1.setCanalRed(6);
v1.setlecturaActual(45);
cout<<"Alerta con 45: "<<boolalpha<<v1.alertaCritica()<<endl;


v1.setlecturaActual(110);

cout<<"Alerta con 110: "<<boolalpha<<v1.alertaCritica()<<endl;;


cout<<"Consumo: "<<v1.getconsumoWatts()<<endl;
cout<<"Canal: "<<v1.getCanalRed()<<endl;



    return 0;
}
// En main(): crea un SensorTemperatura. Asignale consumoWatts = 5.5 (setter
// heredado de Dispositivo), canalRed = 6 (setter heredado de
// DispositivoConectado), y lecturaActual = 45.0 (setter propio). 

//Imprime el
// resultado de alertaCritica() con esa lectura, precedido por "Alerta con
// 45.0: ". Despues cambia lecturaActual a 110.0 e imprime alertaCritica()
// otra vez, precedido por "Alerta con 110.0: ". Imprime consumoWatts
// precedido por "Consumo: " y canalRed precedido por "Canal: ". Los valores
// booleanos se imprimen como "true" o "false" (usa std::boolalpha antes de
// imprimirlos).
//
// Compilar: g++ -std=c++20 -Wall -Wextra -g -o ejercicio17 ejercicio17_dispositivo_sensor.cpp
// Ejecutar: ./ejercicio17
//
// Salida esperada:
// Alerta con 45.0: false
// Alerta con 110.0: true
// Consumo: 5.5
// Canal: 6
