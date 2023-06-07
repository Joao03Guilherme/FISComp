# include <vector> // vector
# include <array> // array
# include <string> // string
# include <iostream> // cout, endl
# include <cmath> // sqrt, pow, M_PI, round

#include "Lightmap.hpp"

using namespace std;

float radiant_intensity(lightsource S, double r, array<float, 2> dimensions) {
    float area = dimensions[0] * dimensions[1] * 1e-4; // m^2
    float domega = area / (r*r); // sr
    return S.power / domega; // W/sr
}

float GetTotalPowerSize(array<float, 2> dimensions, array<float, 2> size) {
    lightsource S;
    S.coordinates = {0, 100, 100}; // default location (cm)
    S.power = 100; // default power (W)

    array<int, 2> ncell = {(int) round(dimensions[0]/size[0]), (int) round(dimensions[1]/size[1])};
    lightmap L(S, ncell, size);
    
    L.UpdatePower();
    return L.GetTotalPower();
}

int main() {
    // Plane dimensions
    array<float, 2> size = {200, 300}; // cm

    // Number of cells (10 * 10 cm)
    array<int, 2> ncell = {20, 30};

    // Light sources
    lightsource S1;
    S1.coordinates = {100, 250, 50}; // cm
    S1.power = 100; // W

    lightsource S2;
    S2.coordinates = {100, 50, 50}; // cm
    S2.power = 100; // W´

    // Create lightmap
    lightmap L(S1, ncell, size);

    // Add light source
    L.AddLightSource(S2);

    // Update cell power
    L.UpdatePower();

    // Get cell with max power
    const cell& C = L.GetMaxCell();

    // Print cell coordinates and power
    cout << "Cell coordinates: (" << C.center_coordinates[0] << ", " << C.center_coordinates[1] << ", " << C.center_coordinates[2] << ")" << endl;
    cout << "Cell power: " << C.power << " W" << endl;

    // Create histogram of cell power
    L.CreateHistogram("histogram.pdf");

    // 20 cm, 12.5 cm, 6.25 cm, 4 cm, 2.5 cm, 2 cm, 1 cm
    vector<float> sizes = {20, 12.5, 6.25, 4, 2.5, 2, 1};
    vector<float> total_power;

    for (float s : sizes) {
        total_power.push_back(GetTotalPowerSize(size, {s, s}));
    }

    L.CreateGraph(sizes, total_power, "total_power.pdf");
    return 0;
}