// Ejercicio 25: Motor, TituloPropiedad, Vehiculo y Concesionario
// (integrador final: composicion + operator<< + unique_ptr + shared_ptr)

#include <iostream>
#include <memory>
using namespace std;

class Motor{
private:
    double potenciaHP;
public:
    bool setPotenciaHP(double p){
        if(p>0 and p<=1000){
            potenciaHP=p;
            return true;
        }else{
            return false;
        }
    }
    double getPotenciaHP(){return potenciaHP;}
};

std::ostream& operator<<(std::ostream& os, Motor m){
    os<<"Motor de "<<m.getPotenciaHP()<<" HP";
    return os;
}

class TituloPropiedad{
private:
    int numeroRegistro;
public:
    bool setNumeroRegistro(int n){
        if(n>=1000 and n<=999999){
            numeroRegistro=n;
            return true;
        }else{
            return false;
        }
    }
    int getNumeroRegistro(){return numeroRegistro;}
};

class Vehiculo{
private:
    unique_ptr<Motor> motorPropio;
    shared_ptr<TituloPropiedad> tituloPropio;
public:
    Vehiculo(){
        // motorPropio ya empieza en nullptr
    }
    Vehiculo(unique_ptr<Motor> motorInicial){
        motorPropio=move(motorInicial);
    }
    void registrarTitulo(shared_ptr<TituloPropiedad> t){
        tituloPropio=t;
    }
    bool tieneMotor(){
        if(motorPropio!=nullptr){
            return true;
        }else{
            return false;
        }
    }
    void mostrarMotor(){
        if(tieneMotor()){
            cout<<*motorPropio<<endl;
        }else{
            cout<<"Vehiculo sin motor"<<endl;
        }
    }
    unique_ptr<Motor> extraerMotor(){
        return move(motorPropio);
    }
    void recibirMotor(unique_ptr<Motor> nuevoMotor){
        motorPropio=move(nuevoMotor);
    }
};

class Concesionario{
private:
    shared_ptr<TituloPropiedad> tituloEnRegistro;
public:
    void archivarTitulo(shared_ptr<TituloPropiedad> t){
        tituloEnRegistro=t;
    }
    int referenciasTitulo(){
        return tituloEnRegistro.use_count();
    }
};

int main(){
    // 1
    shared_ptr<TituloPropiedad> titulo=make_shared<TituloPropiedad>();
    titulo->setNumeroRegistro(4521);

    // 2
    unique_ptr<Motor> motor1=make_unique<Motor>();
    motor1->setPotenciaHP(180);

    // 3
    Vehiculo vehiculo1(move(motor1));

    // 4
    vehiculo1.registrarTitulo(titulo);

    // 5
    Concesionario concesionario1;
    concesionario1.archivarTitulo(titulo);

    // 6
    cout<<"Referencias al titulo: "<<concesionario1.referenciasTitulo()<<endl;

    // 7
    cout<<"Motor del vehiculo 1: ";
    vehiculo1.mostrarMotor();

    // 8
    Vehiculo vehiculo2;
    cout<<"Motor del vehiculo 2 antes: ";
    vehiculo2.mostrarMotor();

    // 9
    vehiculo2.recibirMotor(vehiculo1.extraerMotor());

    // 10
    cout<<"Motor del vehiculo 1 despues: ";
    vehiculo1.mostrarMotor();
    cout<<"Motor del vehiculo 2 despues: ";
    vehiculo2.mostrarMotor();

    return 0;
}