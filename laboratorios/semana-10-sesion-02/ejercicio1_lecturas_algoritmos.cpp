#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <numeric>

// Temperaturas de una semana en el laboratorio. Cada calculo esta escrito
// con un loop a mano. Corre el archivo antes de cambiar nada.

int main() {
    std::vector<double> temperaturas = {21.5, 23.0, 19.5, 23.0, 25.5, 22.0, 18.5};

    // TODO (paso 1): reemplaza este loop por std::accumulate, de
    // <numeric>, con 0.0 como valor inicial.
// el 00 del final es de cuanto quiero que comience    
double sumaTotal= std::accumulate(temperaturas.begin(), temperaturas.end(), 0.0);
std::cout<<"Suma acumulada: "<<sumaTotal<<std::endl;


    // TODO (paso 2): reemplaza este loop por std::max_element, de
    // <algorithm>. Ojo: devuelve un iterador, no un valor. para entrar lo que hay dentor de it uasr *
auto itMaximo = std::max_element(temperaturas.begin(), temperaturas.end());
std::cout<<"Valor maximo: "<< *itMaximo<<std::endl;



    // TODO (paso 3): reemplaza este loop por std:: el 23 el valor que quiero contar
int vecesen23=std::count(temperaturas.begin(), temperaturas.end(),23.0);
    std::cout<<"Veces que dio 23: "<<vecesen23<<std::endl;                      ;


    // TODO (paso 4): reemplaza este loop por std::find. Si encuentra
    // 25.5, la posicion es la distancia entre el iterador encontrado y
    // temperaturas.begin().
auto itposicion = std::find(temperaturas.begin(), temperaturas.end(), 25.5);

if(itposicion== temperaturas.end()){
    std::cout<<"Nose encontro el valor 25.5"<<std::endl; 
}else{
    //itposicion con respecto al inicio
    std::cout<<"Se encontro el 25.5 en la posicion: " << (itposicion - temperaturas.begin())<<std::endl;
}
    // TODO (paso 5): crea una std::list<double> llamada lista con los
    // mismos valores, copiandolos del vector:
    // std::list<double> lista(temperaturas.begin(), temperaturas.end());
    // y repite los pasos 1, 2 y 3 sobre lista, con las mismas llamadas.
    // Imprime "Suma (lista): ", "Maxima (lista): " y "Dias en 23.0 (lista): ".

   std::list<double> lista(temperaturas.begin(), temperaturas.end());

    double suma= std::accumulate(lista.begin(), lista.end(), 0.0);
    std::cout<<"Suma (lista): "<<suma<<std::endl;

    auto itMax = std::max_element(lista.begin(), lista.end());
    std::cout<<"Maxima (lista): "<< *itMax<<std::endl;

    int veces23=std::count(lista.begin(), lista.end(),23.0);
    std::cout<<"Dias en 23.0 (lista): "<<veces23<<std::endl;                      ;

    // TODO (paso 6): imprime "Suma con 0 como valor inicial: " con
    int maxima = std::accumulate(temperaturas.begin(), temperaturas.end(), 0);
    std::cout<<"Suma con 0 como valor inicial: "<<maxima<<std::endl;
    return 0;
}
