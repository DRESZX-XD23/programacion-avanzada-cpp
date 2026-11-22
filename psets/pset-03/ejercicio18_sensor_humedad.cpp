// Ejercicio 18: Sensor y SensorDeHumedad (destructor virtual y unique_ptr)

#include <iostream>
#include <memory>

class Sensor {
public:
    virtual ~Sensor() {
        std::cout << "Sensor apagado" << std::endl;
    }
    virtual double promedio() {
        return 0;
    }
};

class SensorDeHumedad : public Sensor {
private:
    double* lecturas;
public:
    SensorDeHumedad(double a, double b, double c) {
        lecturas = new double[3];        
        lecturas[0] = a;
        lecturas[1] = b;
        lecturas[2] = c;
    }
    ~SensorDeHumedad() {
        delete[] lecturas;               
        std::cout << "Lecturas liberadas" << std::endl;
    }
    double promedio() override {
        return (lecturas[0] + lecturas[1] + lecturas[2]) / 3;
    }
};

int main() {
    {
        std::unique_ptr<Sensor> sensor = std::make_unique<SensorDeHumedad>(60, 72, 81);
        std::cout << "Humedad promedio: " << sensor->promedio() << std::endl;
    }   // aqui muere "sensor" y se borra el objeto
    std::cout << "Fin del programa" << std::endl;
    return 0;
}