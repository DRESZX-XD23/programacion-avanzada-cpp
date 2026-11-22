#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

class Gimnasio {
private:
    std::vector<int> cuposPorHorario;
    std::map<int, double> precioPorPlan;
public:
    Gimnasio() {
        cuposPorHorario = {12, 0, 6, 20, 3};
        precioPorPlan[1] = 30;
        precioPorPlan[2] = 45;
        precioPorPlan[3] = 60;
    }
    int cuposEn(int horario) {
        return cuposPorHorario.at(horario);
    }
    double precioDe(int plan) {
        return precioPorPlan.at(plan);
    }
    double inscribir(int horario, int plan, int personas) {
        int cupos = cuposEn(horario);
        double precio = precioDe(plan);
        if (personas <= 0) {
            throw std::invalid_argument("personas no positivas");
        }
        if (personas > cupos) {
            throw std::runtime_error("sin cupos");
        }
        cuposPorHorario.at(horario) -= personas;
        return personas * precio;
    }
};

void atender(Gimnasio* gimnasio, int horario, int plan, int personas) {
    try {
        double total = gimnasio->inscribir(horario, plan, personas);
        std::cout << "Inscritas " << personas << " personas, total " << total << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Rechazada: horario o plan inexistente" << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Rechazada: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Rechazada: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Rechazada: error inesperado" << std::endl;
    }
}

int main() {
    Gimnasio gimnasio;
    atender(&gimnasio, 0, 2, 4);
    atender(&gimnasio, 1, 1, 1);
    atender(&gimnasio, 9, 1, 1);
    atender(&gimnasio, 3, 5, 2);
    atender(&gimnasio, 2, 3, -1);
    atender(&gimnasio, 2, 3, 6);
    atender(&gimnasio, 2, 3, 1);
    std::cout << "Cupos en el horario 0: " << gimnasio.cuposEn(0) << std::endl;
    std::cout << "Cupos en el horario 2: " << gimnasio.cuposEn(2) << std::endl;
    return 0;
}