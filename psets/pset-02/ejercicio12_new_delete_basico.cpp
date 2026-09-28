    // Ejercicio 12: new[] y delete[] basico
    //
    // Completa las lineas marcadas con TODO dentro de main(). No agregues includes
    // ni cambies el resto del archivo.
    //
    // Compilar: g++ -std=c++20 -Wall -Wextra -g -o ejercicio12 ejercicio12_new_delete_basico.cpp
    // Ejecutar: ./ejercicio12
    //
    // Salida esperada:
    // Suma: 150

    #include <iostream>

    int main() {
        int n=5;
        int h=10;
        int* valores = new int[n];
        // TODO: reserva dinamicamente un arreglo de 5 int con new[] y guarda el
        // puntero en una variable llamada valores.
    for(int m=0;m<n;m++){
        valores[m]=h;
        h=h+10;
    }
        // TODO: asigna a valores los numeros 10, 20, 30, 40 y 50 (en ese orden,
        // por indice).

        int suma = 0;
        for (int i = 0; i < 5; i++) {
            suma= suma+ valores[i];
            // TODO: suma valores[i] a suma.
        }
        std::cout << "Suma: " << suma << std::endl;
        delete[] valores;
        // TODO: libera la memoria reservada con delete[].

        return 0;
    }
