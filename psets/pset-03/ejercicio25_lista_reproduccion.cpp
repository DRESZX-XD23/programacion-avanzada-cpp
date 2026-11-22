#include <iostream>
#include <list>
#include <set>

class ListaDeReproduccion {
private:
    std::list<int> pendientes;
    std::set<int> reproducidas;
public:
    void agregarAlFinal(int id) {
        pendientes.push_back(id);
    }
    void agregarSiguiente(int id) {
        pendientes.push_front(id);
    }
    int reproducir() {
        if (pendientes.empty()) {
            return -1;
        }
        int id = pendientes.front();
        pendientes.pop_front();
        reproducidas.insert(id);
        return id;
    }
    bool yaSono(int id) {
        return reproducidas.count(id) == 1;
    }
    int quitarTodas(int id) {
        int borradas = 0;
        auto it = pendientes.begin();
        while (it != pendientes.end()) {
            if (*it == id) {
                it = pendientes.erase(it);
                borradas++;
            } else {
                it++;
            }
        }
        return borradas;
    }
    int pendientesPorSonar() {
        return pendientes.size();
    }
};

int main() {
    ListaDeReproduccion lista;
    lista.agregarAlFinal(11);
    lista.agregarAlFinal(22);
    lista.agregarAlFinal(11);
    lista.agregarAlFinal(33);
    lista.agregarSiguiente(44);

    std::cout << "Suena: " << lista.reproducir() << std::endl;
    std::cout << "Suena: " << lista.reproducir() << std::endl;
    std::cout << "Quitadas: " << lista.quitarTodas(11) << std::endl;
    std::cout << "Pendientes: " << lista.pendientesPorSonar() << std::endl;
    std::cout << "La 44 ya sono: " << lista.yaSono(44) << std::endl;
    std::cout << "La 33 ya sono: " << lista.yaSono(33) << std::endl;
    std::cout << "Suena: " << lista.reproducir() << std::endl;
    std::cout << "Suena: " << lista.reproducir() << std::endl;
    return 0;
}