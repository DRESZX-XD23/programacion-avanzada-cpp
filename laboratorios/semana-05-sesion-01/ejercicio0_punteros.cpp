#include <iostream>
using namespace std;
#include<string>



int main(){
    int numero =10;
// vas a ir a apuntar a un entero el valor de la derecha tiene que ser una direccion de memoria la direccion: &
    int *puntero_anumero = &numero;



    cout<<"Direccion en memoria: "<< puntero_anumero << endl;
    cout<<"Valor en memoria desde la variable: " << numero << endl;

    //entrar y ver que hay dentro con* busca lo que hay en esa direccion
    cout<<"valor memoria desde puntero "<< *puntero_anumero << endl;
    cout<<endl;



  int notas[5]={80,90,60,50,71};
 // int *punteraso = notas;
  //punteraso=punteraso+4;
 // cout<<*punteraso<<endl<<endl;

  for(int contador=0;contador <= 4;contador++){
    int *punteraso = notas;
    punteraso=punteraso+contador;
    cout<<*punteraso<<endl;
  }
    return 0;
}