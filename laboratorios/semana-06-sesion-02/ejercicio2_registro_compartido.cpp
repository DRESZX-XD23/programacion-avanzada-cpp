#include <iostream>
#include <memory>
#include <utility>

class RegistroDeVuelo {
    private:
        // TODO: cambia "double* alturas" por std::unique_ptr<double[]>.
        std::unique_ptr<double[]> alturas;
        int capacidad;
    public:


        RegistroDeVuelo(int nuevaCapacidad) {
            capacidad = nuevaCapacidad;
            // TODO: crea "alturas" con std::make_unique<double[]>(capacidad)
            // en vez de "new double[capacidad]".
            alturas = std::make_unique<double[]>(capacidad) ;
            std::cout << "Registro de vuelo creado para " << capacidad << " lecturas" << std::endl;
        }

        void guardarAltura(int indice, double valor) {
            alturas[indice] = valor;
        }

        double getAltura(int indice) {
            return alturas[indice];
        }

        // TODO: con unique_ptr como atributo, ya no hace falta nada de
        // esto. Borra el destructor completo (unique_ptr libera solo).
        ~RegistroDeVuelo() {
            std::cout << "Destruyendo registro (capacidad " << capacidad << ")" << std::endl;
        }
};

class MonitorDeVuelo {
    private:
        // TODO: declara "registro" como std::shared_ptr<RegistroDeVuelo>.
        std::shared_ptr<RegistroDeVuelo> registro; 
        int idMonitor;
    public:
        // TODO: el constructor recibe std::shared_ptr<RegistroDeVuelo>
        // unRegistro por valor, y lo guarda con
        // registro = std::move(unRegistro); (mover el shared_ptr local
        // hacia el atributo evita una copia de mas, aunque la clase ya
        // permite copiar shared_ptr sin ningun riesgo).
        MonitorDeVuelo(std::shared_ptr<RegistroDeVuelo>nuevoregistro, int unId) {         
            idMonitor = unId;
            registro = std::move(nuevoregistro);
            std::cout<< "Monitor: "<< idMonitor <<" conectado. Cuenta "<<registro.use_count()<<std::endl;    ;
        }

        void reportar(int indice) {
            std::cout << "Monitor " << idMonitor << " ve altura " << 0.0 << std::endl;
            (void)indice;
        }

        ~MonitorDeVuelo() {
            std::cout << "Monitor " << idMonitor << " desconectado" << std::endl;
        }
};

int main() {
    RegistroDeVuelo registroSolo(3);
    registroSolo.guardarAltura(0, 100.0);
    std::cout << "registroSolo.getAltura(0) = " << registroSolo.getAltura(0) << std::endl;

    std::cout << "---" << std::endl;

   std::shared_ptr<RegistroDeVuelo>registrocompartido = std::make_shared<RegistroDeVuelo>(5);
    registrocompartido->guardarAltura(0,200);
    std::cout<<"Cuenta antes de monitoriar: "<<registrocompartido.use_count()<<std::endl;

    {
    MonitorDeVuelo torre_quito(registrocompartido, 1);        
    MonitorDeVuelo torre_ambato(registrocompartido,2);
    MonitorDeVuelo torre_cuenca(registrocompartido,3);
    std::cout <<"Cuenta despues de monitores: "<<registrocompartido.use_count()<<std::endl;
    torre_quito.reportar(0);
    torre_ambato.reportar(0);
    torre_cuenca.reportar(0);
    }

// ver cuantos punteros quedaron

std::cout <<"Cuenta despues de cerrar monitores: "<<registrocompartido.use_count()<<std::endl;
    // TODO: crea "compartido" con
    // std::make_shared<RegistroDeVuelo>(5) en vez de un objeto local.
    // Guarda una lectura en el indice 0 y muestra compartido.use_count().
    //
    // Despues, dentro de un bloque { }, crea dos MonitorDeVuelo pasandoles
    // "compartido" (torre con id 1, cabina con id 2), muestra
    // compartido.use_count() con los dos monitores activos, y llama a
    // reportar(0) en cada uno. Al cerrar el bloque, los monitores se
    // destruyen; muestra compartido.use_count() una vez mas para
    // confirmar que volvio a bajar.

    return 0;
}
