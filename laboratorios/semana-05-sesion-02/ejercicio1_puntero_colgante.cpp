#include <iostream>
using namespace std;

class lecturasensor{
private:
int valor;
public:
lecturasensor(int v){
 valor=v;
 cout<<"se llamo al Constructor"<<endl;

}

~lecturasensor(){
    cout<<"lamando al destructos";
}

int getvalor(){return valor;}

};
// TODO: predice antes de compilar. ¿que advertencia esperas que de
// el compilador sobre esta funcion?
int* obtenerLecturaInsegura(int valorSensor) {
    int lectura = valorSensor * 2;
    return &lectura;
}

void demostraralcanze(){
    lecturasensor sensor(50);
    cout<< "valor "<<sensor.getvalor()<<endl;
}

lecturasensor* demostraralcanzememoriadinamica(){
lecturasensor*sensor= new lecturasensor(80);
cout<<"Valor "<<sensor->getvalor()<<endl;
delete sensor;

sensor= nullptr;

return sensor;
}



//al acabar la funcion el retunr se libera y entonces no tendria direccion, puntero colgante
int main() {
    int* resultado = obtenerLecturaInsegura(10);
    std::cout << "Lectura (puntero colgante): " << *resultado << std::endl;
    cout<<endl;
    demostraralcanze();
lecturasensor* sensor_ptr= demostraralcanzememoriadinamica();    
cout<<sensor_ptr->getvalor()<<endl;    
return 0;
}
