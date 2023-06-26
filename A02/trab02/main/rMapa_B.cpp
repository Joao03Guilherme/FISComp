# include <stdlib.h>
#include <iostream>
#include <cmath>
#include <functional>
# include "Lightmap.hpp"
using namespace std;

// Plane dimensions
const array<float, 2> size = {200, 200}; // m

const array<int, 2> ncell = {200, 200};

lightmap L;

class Integrator {
public:
    Integrator() = default;
    ~Integrator() = default;

    static float trapz(const function<float(float, float)>& f, float x0, float x1, float y0, float y1, int nx,  int ny); // 2D integration
    // static float romberg(const function<float(float, float)>& f, float x0, float x1, float y0, float y1, int maxIter); // 2D integration
};

float Integrator::trapz(const function<float(float, float)>& f, float x0, float x1, float y0, float y1, int nx,  int ny) {
    float dx = (x1 - x0) / nx;
    float dy = (y1 - y0) / ny;
    float sum = 0.0f;

    for (int i = 0; i < nx; i++) {
        float x = x0 + i * dx;
        for (int j = 0; j < ny; j++) {
            float y = y0 + j * dy;
            sum += f(x, y);
        }
    }

    return sum * dx * dy;
}

float irradiance(float x, float y) {
    return L.Irradiance({x, y, 0});
}

int main() {
    float x0 = 0.0f;
    float x1 = 200.0f;
    float y0 = 0.0f;
    float y1 = 200.0f;
    int nx = 40; // Change precision of integral (I11, I21)
    int ny = 40;

    Integrator I;

    lightsource S;
    S.coordinates = {100, 100, 25}; // default location (cm)
    S.power = 100; // default power (W)

    // Create lightmap
    L = lightmap(S, ncell, size);

    // Update power
    L.UpdatePower();

    // Get total power
    cout << "Total power: " << L.GetTotalPower() << " W" << endl;
    cout << "Total power: " << I.trapz(irradiance, x0, x1, y0, y1, nx, ny) << " W" << endl;
}