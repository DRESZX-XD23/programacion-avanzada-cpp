// Ejercicio 21: Cola (desde cero, RAII con new[] y delete[])

#include <iostream>
using namespace std;

class Cola{
private:
    int* datos;
    int capacidad;
public:
    Cola(int c){
        capacidad=c;
        datos = new int[capacidad];
        for(int k=0;k<capacidad;k++){
            datos[k]=0;
        }
    }
    ~Cola(){
        delete[] datos;
        datos=nullptr;
        cout<<"Cola liberada"<<endl;
    }
    bool agregar(int indice, int valor){
        if(indice>=0 and indice<capacidad){
            datos[indice]=valor;
            return true;
        }else{
            return false;
        }
    }
    int getValor(int indice){return datos[indice];}
};

int main(){
    Cola c1(4);

    cout<<"Agregar en 1: "<<boolalpha<<c1.agregar(1, 55)<<endl;
    cout<<"Agregar en 9: "<<c1.agregar(9, 99)<<endl;

    for(int i=0;i<4;i++){
        cout<<"Posicion "<<i<<": "<<c1.getValor(i)<<endl;
    }

    return 0;
}
