#include <iostream>
#include <map>
#include <optional>
#include <string>

class AgendaDelConsultorio {
private:
    std::map<int, int> pacientePorHora;
public:
    std::optional<int> pacienteEn(int hora) {
        auto it = pacientePorHora.find(hora);
        if (it == pacientePorHora.end()) {
            return std::nullopt;
        }
        return it->second;
    }
    std::optional<int> primeraLibreDesde(int hora) {
        if (hora < 8) {
            hora = 8;
        }
        for (int h = hora; h <= 17; h++) {
            if (pacientePorHora.count(h) == 0) {
                return h;
            }
        }
        return std::nullopt;
    }
    std::optional<int> agendar(int paciente, int desde) {
        std::optional<int> hora = primeraLibreDesde(desde);
        if (hora.has_value()) {
            pacientePorHora[*hora] = paciente;
        }
        return hora;
    }
    bool cancelar(int hora) {
        if (pacientePorHora.count(hora) == 0) {
            return false;
        }
        pacientePorHora.erase(hora);
        return true;
    }
};

void imprimirHora(std::string texto, std::optional<int> hora) {
    std::cout << texto;
    if (hora.has_value()) {
        std::cout << *hora << std::endl;
    } else {
        std::cout << "sin hora" << std::endl;
    }
}

int main() {
    AgendaDelConsultorio agenda;
    imprimirHora("Paciente 501: ", agenda.agendar(501, 8));
    imprimirHora("Paciente 502: ", agenda.agendar(502, 8));
    imprimirHora("Paciente 503: ", agenda.agendar(503, 16));
    imprimirHora("Paciente 504: ", agenda.agendar(504, 16));
    imprimirHora("Paciente 504 otra vez: ", agenda.agendar(504, 16));

    std::cout << "A las 9: " << *agenda.pacienteEn(9) << std::endl;
    std::cout << "A las 12: " << agenda.pacienteEn(12).value_or(0) << std::endl;

    try {
        std::cout << agenda.pacienteEn(13).value() << std::endl;
    } catch (const std::bad_optional_access& e) {
        std::cout << "Nadie a las 13" << std::endl;
    }

    agenda.cancelar(8);
    imprimirHora("Paciente 505: ", agenda.agendar(505, 7));
    return 0;
}