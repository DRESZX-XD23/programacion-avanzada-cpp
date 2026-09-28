// Ejercicio 24: Documento, Propietario y Observador
// (desde cero, shared_ptr y weak_ptr)

#include <iostream>
#include <memory>
using namespace std;

class Documento{
private:
    int numeroVersion;
public:
    bool setNumeroVersion(int v){
        if(v>=1 and v<=999){
            numeroVersion=v;
            return true;
        }else{
            return false;
        }
    }
    int getNumeroVersion(){return numeroVersion;}
};

class Propietario{
private:
    shared_ptr<Documento> documento;
public:
    void adoptar(shared_ptr<Documento> doc){
        documento=doc;
    }
    void soltar(){
        documento.reset();
    }
    int contadorReferencias(){
        return documento.use_count();
    }
};

class Observador{
private:
    weak_ptr<Documento> documento;
public:
    void observar(shared_ptr<Documento> doc){
        documento=doc;
    }
    bool documentoTodaviaExiste(){
        return !documento.expired();
    }
};

int main(){
    shared_ptr<Documento> doc=make_shared<Documento>();
    doc->setNumeroVersion(3);

    Propietario dueno;
    dueno.adoptar(doc);
    cout<<"Referencias tras adoptar: "<<dueno.contadorReferencias()<<endl;

    Observador obs;
    obs.observar(doc);
    cout<<"Documento existe (observador): "<<boolalpha<<obs.documentoTodaviaExiste()<<endl;
    cout<<"Referencias despues de observar: "<<dueno.contadorReferencias()<<endl;

    doc.reset();
    cout<<"Referencias tras reset del original: "<<dueno.contadorReferencias()<<endl;
    cout<<"Documento existe (observador): "<<obs.documentoTodaviaExiste()<<endl;

    dueno.soltar();
    cout<<"Documento existe (observador): "<<obs.documentoTodaviaExiste()<<endl;

    return 0;
}