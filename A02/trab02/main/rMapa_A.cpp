# include <vector> // vector
# include <array> // array
# include <string> // string
# include <iostream> // cout, endl
# include <cmath> // sqrt, pow, M_PI, round

// ROOT
# include "TGraph.h" // TGraph
# include "TCanvas.h" // TCanvas
# include "TAxis.h" // TAxis
# include "TMultiGraph.h" // TMultiGraph
#include "TEllipse.h"
# include "Lightmap.hpp"

const string FILENAME_DISTANCE = "FIG_source_power_distance.png";
const string FILENAME_LARGE_DISTANCE = "FIG_source_power_large_distance.png";

using namespace std;

// Plane dimensions
const array<float, 2> size = {200, 200}; // m

// Number of cells (10 * 10 cm)
const array<int, 2> ncell = {20, 20};

float radiant_intensity(lightsource S, double r, array<float, 2> dimensions) {
    float area = dimensions[0] * dimensions[1]; // cm^2
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

void MakeDistancePowerGraph(string filename, array<float, 2> z_range, int step) {
    vector<float> x1, y1;
    vector<float> x2, y2;

    auto PAnalytical = [](float P, float z) {return P / (4.0f * M_PI * z*z / 1000) * 40;}; // W

    for (float z = z_range[0]; z <= z_range[1]; z += step) { // cm
        lightsource S;
        S.coordinates = {100, 100, z}; // cm
        S.power = 100; // W

        lightmap L(S, ncell, size);
        L.UpdatePower();

        x1.push_back(z);
        y1.push_back(L.GetTotalPower());

        x2.push_back(z);
        y2.push_back(PAnalytical(S.power, z));
    }

    // Create a TCanvas
    TCanvas canvas("canvas", "Graphs", 800, 600);

    TGraph graph1(x1.size(), x1.data(), y1.data());

    // Create the second TGraph object and fill it with data points
    TGraph graph2(x2.size(), x2.data(), y2.data());

    // Create a TMultiGraph and add the graphs to it
    TMultiGraph mg;
    mg.Add(&graph1);
    mg.Add(&graph2);

    // Set the marker and line styles for the graphs as needed
    graph1.SetMarkerStyle(20);
    graph1.SetLineColor(kGreen + 1);
    graph2.SetMarkerStyle(21);
    graph2.SetLineColor(kBlue + 2);

    // Set the axis titles
    mg.GetXaxis()->SetTitle("Distance (cm)");
    mg.GetYaxis()->SetTitle("Power (W)");

    // Draw the TMultiGraph
    mg.Draw("ALP"); // "ALP" draws the graphs as lines with markers

    // Update the canvas
    canvas.Update();
    canvas.SaveAs(filename.c_str());
}

int main() {
    // Light sources
    lightsource S1;
    S1.coordinates = {100, 100, 25}; // m
    S1.power = 100; // W

    // Create lightmap
    lightmap L(S1, ncell, size);

    // Update cell power
    L.UpdatePower();

    vector<cell> ordered_cells = L.GetOrderedCells();
    for (int i = 0; i < 10; i++) {
        cell& c = ordered_cells[i];
        cout << "Cell distance: " << L.distance2cell(c.center_coordinates, S1.coordinates) << " m" << endl;
        cout << "Cell power: " << c.power << " W" << endl;
    }

    // Print cell coordinates and power
    cout << "Total power: " << L.GetTotalPower() << " W" << endl;

    // Create histogram of cell power
    L.CreateHistogram("histogram.pdf");

    // Create graph of total power vs distance
    MakeDistancePowerGraph(FILENAME_DISTANCE, {10, 100}, 10);
    MakeDistancePowerGraph(FILENAME_LARGE_DISTANCE, {1000, 10000}, 300);

    return 0;
}