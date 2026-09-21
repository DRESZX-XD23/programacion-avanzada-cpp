#include <iostream>
using namespace std;

class motor{
private:
double potenciaHP;
int* historialRPM;

public:

motor(double nuevapotencia,int n){


    if(nuevapotencia<=0){
        cout<<"potencia invalida, se asigna 100 por defecto";
        potenciaHP=100;
    }else{
        potenciaHP=nuevapotencia;
        cout<<"potencia asignada: "<<potenciaHP<<" HP"<<endl;
    }
    historialRPM = new int[n];
    cout<<"espacio reservado para "<<n<<" RPM"<<endl;
}
  
~motor() {
    delete[] historialRPM;
    cout<<"Se ha borrado su historial de rpm"<<endl;}
};


int main() {
  motor m(75.0, 5);
  cout << "Fin de main" << endl;
}
//lvalue una variable
//rvalue a+b muere al terminar
//&& temporal
//pasar cosas de una a otra, dejas a la original con nulptr: noexcept(nunca falla )
/////pasos && constructor de movimiento el move y forward
// move dice que eso es temporal
//solo se usa return
//regla de 5 destructor constructor de copia, asignacion de copia, constructor de movimiento, asignasion de movimiento
///dos punteroa al mismo lugar
//copia superficial 
//cambia uno lo detecta el otro.
//hay un problema con el delete.

//solo se roba a algo temporal