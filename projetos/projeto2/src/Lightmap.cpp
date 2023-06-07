# include <iostream> // for cout, endl
# include <array> // for array
# include <vector> // for vector
# include <cmath> // for sqrt, pow, M_PI, round
# include <algorithm> // for sort

// ROOT
#include <TGraph.h> // for TGraph
#include <TH2F.h> // for TH2F
#include <TCanvas.h> // for TCanvas
#include <TFile.h> // for TFile

# include "Lightmap.hpp"

using namespace std;

// Constructors
lightmap::lightmap(array<int,2> ncell, array<float,2> size) {
    initializeGrid(ncell, size);
}

lightmap::lightmap(lightsource S, array<int,2> ncell, array<float,2> size) {
    initializeGrid(ncell, size);
    AddLightSource(S);
}

// Getters
pair<int,int> lightmap::GetCellIndex(float x, float y) const {
    int index_x = (int) (x/SIZE[0]*GRID.size());
    int index_y = (int) (y/SIZE[1]*GRID[0].size());
    return make_pair(index_x, index_y);
}

pair<float,float> lightmap::GetCellCoo(int index_x, int index_y) const {
    cell C = GRID[index_x][index_y];
    return make_pair(C.center_coordinates[0], C.center_coordinates[1]);
}

double lightmap::GetCellPower(int index_x, int index_y) const {
    cell C = GRID[index_x][index_y];
    return C.power;
}

double lightmap::GetCellPower(float x, float y) const {
    pair<int,int> index = GetCellIndex(x, y);
    return GetCellPower(index.first, index.second);
}

int lightmap::GetCellNx() const {
    return GRID.size();
}

int lightmap::GetCellNy() const {
    return GRID[0].size();
}

const vector<vector<cell>>& lightmap::GetCells() const {
    return GRID;
}

vector<vector<cell>>& lightmap::GetCells() {
    return GRID;
}

array<float,3> lightmap::GetNormal() {
    return NORMAL;
}

vector<cell> lightmap::GetOrderedCells() const {
    vector<cell> ordered_cells;
    for (int i = 0; i < (int) GRID.size(); i++) {
        for (int j = 0; j < (int) GRID[0].size(); j++) {
            ordered_cells.push_back(GRID[i][j]);
        }
    }
    sort(ordered_cells.begin(), ordered_cells.end(), [](cell A, cell B) {return A.power > B.power;});
    return ordered_cells;
}

float lightmap::GetTotalPower() const {
    float total_power = 0;
    for (int i = 0; i < (int) GRID.size(); i++) {
        for (int j = 0; j < (int) GRID[0].size(); j++) {
            total_power += GRID[i][j].power;
        }
    }
    return total_power;
}

// other functions
void lightmap::AddLightSource(lightsource S) {
    SOURCES.push_back(S);
}

const cell& lightmap::GetMaxCell() const {
    vector<cell> ordered_cells = GetOrderedCells();
    return ordered_cells[0];
}

float lightmap::distance2cell(array<float, 3> SourceCoo, array<float, 3> PointCoo) {
    float dx = SourceCoo[0] - PointCoo[0];
    float dy = SourceCoo[1] - PointCoo[1];
    float dz = SourceCoo[2] - PointCoo[2];
    return sqrt(dx*dx + dy*dy + dz*dz);
}

float lightmap::Irradiance(array<float,3> PointCoo) {
    float E = 0;
    for (lightsource S : SOURCES) {
        float r = distance2cell(S.coordinates, PointCoo);
        E += S.power / (4*M_PI*r*r) * dot_product(NORMAL, PointCoo); 
    }
    return E;
}

float lightmap::CellPower(cell C) {
    return Irradiance(C.center_coordinates) * C.area;
}

void lightmap::UpdatePower() {
    for (int i = 0; i < (int) GRID.size(); i++) {
        for (int j = 0; j < (int) GRID[0].size(); j++) {
            GRID[i][j].power = CellPower(GRID[i][j]);
        }
    }
}

float lightmap::FindQuotient(vector<cell> ordered_cells) const {
    float max_power = ordered_cells[0].power;
    float median_power = max_power;

    if (ordered_cells.size() % 2 == 0) {
        median_power = (ordered_cells[ordered_cells.size()/2].power + ordered_cells[ordered_cells.size()/2 - 1].power) / 2;
    }
    else {
        median_power = ordered_cells[ordered_cells.size()/2].power;
    }
    return max_power / median_power;
}

void lightmap::CreateHistogram(string filename) {
    vector<cell> ordered_cells = GetOrderedCells();

    // Create histogram
    TH2F h("Power (W)", "Power (W)", GRID.size(), 0, GRID.size(), GRID[0].size(), 0, GRID[0].size());

    // Fill histogram
    for (int i = 0; i < (int) GRID.size(); i++) {
        for (int j = 0; j < (int) GRID[0].size(); j++) {
            h.Fill(i, j, GRID[i][j].power);
        }
    }

    // Create canvas
    TCanvas c("c", "c", 800, 600);

    // Set x-axis label
    h.GetXaxis()->SetTitle("x (cm)");

    // Set y-axis label
    h.GetYaxis()->SetTitle("y (cm)");

    // Set graph title
    h.SetTitle("Power distribution");

    // Draw histogram
    h.Draw("COLZ");

    // Save histogram
    c.SaveAs(filename.c_str());
}

void lightmap::CreateGraph(vector<float> x, vector<float> y, string name) {
    // Create graph
    TGraph g(x.size(), &x[0], &y[0]);

    // Create canvas
    TCanvas c("c", "c", 800, 600);

    // Set x-axis label
    g.GetXaxis()->SetTitle("Cell size (cm)");

    // Set y-axis label
    g.GetYaxis()->SetTitle("Total power (W)");

    // Set graph title
    g.SetTitle("Total power vs cell size");

    // Draw graph
    g.Draw("AC*");

    // Save graph
    c.SaveAs(name.c_str());
}

// Private functions
void lightmap::initializeGrid(array<int,2> ncell, array<float,2> size) {
    GRID.resize(ncell[0]);
    for (int i = 0; i < ncell[0]; i++) {
        GRID[i].resize(ncell[1]);
    }
    SIZE = size;
    NORMAL = {0, 0, 1};

    for (int i = 0; i < ncell[0]; i++) {
        for (int j = 0; j < ncell[1]; j++) {
            cell& C = GRID[i][j];
            C.center_coordinates[0] = (i+0.5)*size[0]/ncell[0];
            C.center_coordinates[1] = (j+0.5)*size[1]/ncell[1];
            C.area = size[0]*size[1]/(ncell[0]*ncell[1]);
            C.power = 0;
        }
    }
}

float lightmap::dot_product(array<float, 3> A, array<float, 3> B) {
    return A[0]*B[0] + A[1]*B[1] + A[2]*B[2];
}