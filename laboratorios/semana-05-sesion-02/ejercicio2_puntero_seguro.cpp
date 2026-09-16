#include <iostream>
using namespace std;


// TODO: cambia esta funcion para que no devuelva la direccion de una
// variable local. Usa memoria dinamica en su lugar, con new.


//lecturasensor* demostraralcanzememoriadinamica(){
//lecturasensor*sensor= new lecturasensor(80);
//cout<<"Valor "<<sensor->getvalor()<<endl;
//delete sensor;

//sensor= nullptr;

//return sensor;
//}


int* obtenerLecturaSegura(int valorSensor) {
    int* nombre = new int(valorSensor*2);
    return nombre;
}

int main() {
    int* resultado = obtenerLecturaSegura(10);
    std::cout << "Lectura: " << *resultado << std::endl;
    delete resultado;
    resultado = nullptr;

    // TODO: despues de terminar con "resultado", libera la memoria con
    // delete y asignale nullptr, para dejar constancia de que ya no
    // apunta a memoria valida.
    return 0;
}
