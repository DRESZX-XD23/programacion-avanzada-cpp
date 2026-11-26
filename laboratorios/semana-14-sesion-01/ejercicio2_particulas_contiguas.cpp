#include <iostream>
#include <vector>

const int PARTICULAS = 300000;
const int CUADROS = 600;

class Particula {
public:
    Particula(float x0, float y0, float vx0, float vy0) {
        x = x0;
        y = y0;
        vx = vx0;
        vy = vy0;
    }

    void actualizar(float dt) {
        vy -= 9.8f * dt;
        x += vx * dt;
        y += vy * dt;
        if (y < 0) {
            y = -y;
            vy = -vy * 0.5f;
        }
    }

    float getY() {
        return y;
    }

private:
    float x;
    float y;
    float vx;
    float vy;
};

int main() {
    std::vector<Particula> particulas;
    particulas.reserve(PARTICULAS);
    for (int i = 0; i < PARTICULAS; i++) {
        float vx = (i % 200) - 100.0f;
        float vy = (i % 97) * 1.5f;
        particulas.push_back(Particula(0.0f, 10.0f, vx, vy));
    }
    for (int cuadro = 0; cuadro < CUADROS; cuadro++) {
        for (int i = 0; i < PARTICULAS; i++) {
            particulas[i].actualizar(1.0f / 60.0f);
        }
    }
    double alturaTotal = 0;
    for (int i = 0; i < PARTICULAS; i++) {
        alturaTotal += particulas[i].getY();
    }
    std::cout << "Altura promedio al final: " << alturaTotal / PARTICULAS << std::endl;
    return 0;
}