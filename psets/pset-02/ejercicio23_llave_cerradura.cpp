// Ejercicio 23: Llave y Cerradura (desde cero, unique_ptr y std::move)

#include <iostream>
#include <memory>
using namespace std;

class Llave{
private:
    int numeroSerie;
public:
    Llave(){
        numeroSerie=0;
    }
    void setNumeroSerie(int n){
        numeroSerie=n;
    }
    int getNumeroSerie(){return numeroSerie;}
};

class Cerradura{
private:
    unique_ptr<Llave> llaveAsignada;
public:
    bool asignarLlave(unique_ptr<Llave> nuevaLlave){
        if(llaveAsignada!=nullptr){
            return false;
        }else{
            llaveAsignada=move(nuevaLlave);
            return true;
        }
    }
    bool tieneLlave(){
        if(llaveAsignada!=nullptr){
            return true;
        }else{
            return false;
        }
    }
};

int main(){
    unique_ptr<Llave> llave1=make_unique<Llave>();
    unique_ptr<Llave> llave2=make_unique<Llave>();
    llave1->setNumeroSerie(101);
    llave2->setNumeroSerie(202);

    Cerradura c1;

    cout<<"Tiene llave antes: "<<boolalpha<<c1.tieneLlave()<<endl;
    cout<<"Asignar llave1: "<<c1.asignarLlave(move(llave1))<<endl;
    cout<<"Asignar llave2: "<<c1.asignarLlave(move(llave2))<<endl;
    cout<<"Tiene llave despues: "<<c1.tieneLlave()<<endl;

    return 0;
}