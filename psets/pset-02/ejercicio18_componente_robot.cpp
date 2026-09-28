// Ejercicio 18: Componente, ComponenteMecanico, ComponenteDigital y Robot
// (desde cero, herencia multiple con el problema del diamante)

#include <iostream>
using namespace std;

class Componente{
private:
int codigoSerie;
public:    
bool setCodigoSerie(int c){
    if(c>=1000 and c<=9999){
        codigoSerie=c;
        return true;}else{
            return false;
        }
    }
    int getCodigoSerie(){return codigoSerie;}
};

class ComponenteMecanico: public virtual Componente{
private:
    double pesoKg;
public:
    bool setPesoKg(double p){
        if(p>0 and p<=50){pesoKg=p;
            return true;
        }else{
            return false;
        }
    }
    double getPesoKg(){return pesoKg;}
};

class ComponenteDigital: public virtual Componente{
private:
    int version;
public:
    bool setVersion(int v){
        if(v>=1 and v<=99){version=v;
            return true;
        }else{
            return false;
        }
    }
    int getVersion(){return version;}
};

class Robot: public ComponenteMecanico, public ComponenteDigital{
private:
    bool autonomo;
public:
    void setAutonomo(bool a){
        autonomo=a;
    }
    bool getAutonomo(){return autonomo;}
};

int main(){
    Robot r1;
    r1.setCodigoSerie(4821);
    r1.setPesoKg(12.5);
    r1.setVersion(3);
    r1.setAutonomo(true);

    cout<<"Codigo serie: "<<r1.getCodigoSerie()<<endl;
    cout<<"Peso: "<<r1.getPesoKg()<<endl;
    cout<<"Version: "<<r1.getVersion()<<endl;
    cout<<"Autonomo: "<<boolalpha<<r1.getAutonomo()<<endl;

    return 0;
}