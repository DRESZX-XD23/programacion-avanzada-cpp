#include <iostream>
#include <list>
#include <set>

class TurnosDeLaboratorio {
private:
    std::list<int> cola;
    std::set<int> enCola;
public:
    bool pedirTurno(int carnet) {
        if (enCola.count(carnet) == 1) {
            return false;
        } else {
            cola.push_back(carnet);
            enCola.insert(carnet);
            return true;
        }
    }
    bool pedirTurnoUrgente(int carnet) {
        if (enCola.count(carnet) == 1) {
            return false;
        } else {
            cola.push_front(carnet);
            enCola.insert(carnet);
            return true;
        }
    }
    int atender() {
        if (cola.empty()) {
            return -1;
        }
        int carnet = cola.front();
        cola.pop_front();
        enCola.erase(carnet);
        return carnet;
    }
    bool retirar(int carnet) {
        for (auto it = cola.begin(); it != cola.end(); it++) {
            if (*it == carnet) {
                cola.erase(it);
                enCola.erase(carnet);
                return true;
            }
        }
        return false;
    }
    int enEspera() {
        return cola.size();
    }
};

int main() {
    TurnosDeLaboratorio turnos;
    turnos.pedirTurno(3021);
    turnos.pedirTurno(5100);
    std::cout << "Pedir 3021 otra vez: " << turnos.pedirTurno(3021) << std::endl;
    turnos.pedirTurno(1888);
    turnos.pedirTurnoUrgente(4410);
    std::cout << "En cola: " << turnos.enEspera() << std::endl;

    std::cout << "Atendido: " << turnos.atender() << std::endl;
    std::cout << "Atendido: " << turnos.atender() << std::endl;
    std::cout << "Retirar 5100: " << turnos.retirar(5100) << std::endl;
    std::cout << "Retirar 7777: " << turnos.retirar(7777) << std::endl;
    std::cout << "En cola: " << turnos.enEspera() << std::endl;
    std::cout << "Atendido: " << turnos.atender() << std::endl;
    std::cout << "Atendido: " << turnos.atender() << std::endl;
    return 0;
}