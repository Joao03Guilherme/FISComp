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

using namespace std;

const int Z = 100; // cm

struct cell { 
    array<float, 3> center_coordinates {0, 0, Z}; // Cell center (cm)
    float area; // Cell area (cm^2)
    float power; // Cell incident power (W)
};

struct lightsource {
    array<float, 3> coordinates; // Light source coordinates (cm)
    float power; // source power (W)
};

float dot_product(array<float, 3> A, array<float, 3> B) {
    return A[0]*B[0] + A[1]*B[1] + A[2]*B[2];
}

class lightmap {
    public:
        // Constructors
        // ... number of cells along x and y and plane dimensions (size)
        lightmap() = default;
        lightmap(array<int,2> ncell, array<float,2> size);
        lightmap(lightsource S, array<int,2> ncell, array<float,2> size);

        // Getters
        pair<int,int> GetCellIndex(float x, float y) const; // return cell index 
        pair<float,float> GetCellCoo(int index_x, int index_y) const; // return cell coordinates
        double GetCellPower(int index_x, int index_y) const; // return cell power
        double GetCellPower(float x, float y) const;
        int GetCellNx() const; // get number of cells along x
        int GetCellNy() const; // get number of cells along y
        const vector<vector<cell>>& GetCells() const; 
        vector<vector<cell>>& GetCells(); // return cells grid
        array<float,3> GetNormal(); // return normal to plane
        vector<cell> GetOrderedCells() const; // return cells ordered by power
        float GetTotalPower() const; // return total power (W)

        // other functions
        void AddLightSource(lightsource S); // add sources
        const cell& GetMaxCell() const; // get cell with max power
        float distance2cell(array<float, 3> SourceCoo, array<float, 3> PointCoo); // return distance between source and cell center
        float radiant_intensity(lightsource S, double r, array<float, 2> dimensions) const; // return radiant intensity
        float Irradiance(array<float,3> PointCoo); // return irradiance at point
        float CellPower(cell C); // return average cell power
        void UpdatePower(); // update cell power
        float FindQuotient(vector<cell> ordered_cells) const; // return quotient between max and median cell power
        void CreateHistogram(string filename) const; // create histogram of cell power

    private:
        void initializeGrid(array<int,2> ncell, array<float,2> size); // initialize grid cells

        vector<vector<cell>> GRID; // cells grid
        vector<lightsource> SOURCES; // light sources
        array<float, 2> SIZE; // plane dimensions (cm)
        array<float, 3> NORMAL; // plane normal
};

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
    for (int i = 0; i < GRID.size(); i++) {
        for (int j = 0; j < GRID[0].size(); j++) {
            ordered_cells.push_back(GRID[i][j]);
        }
    }
    sort(ordered_cells.begin(), ordered_cells.end(), [](cell A, cell B) {return A.power > B.power;});
    return ordered_cells;
}

float lightmap::GetTotalPower() const {
    float total_power = 0;
    for (int i = 0; i < GRID.size(); i++) {
        for (int j = 0; j < GRID[0].size(); j++) {
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

float radiant_intensity(lightsource S, double r, array<float, 2> dimensions) {
    float area = dimensions[0] * dimensions[1] * 1e-4; // m^2
    float domega = area / (r*r); // sr
    return S.power / domega; // W/sr
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
    for (int i = 0; i < GRID.size(); i++) {
        for (int j = 0; j < GRID[0].size(); j++) {
            GRID[i][j].power = CellPower(GRID[i][j]);
        }
    }
}

float lightmap::FindQuotient(vector<cell> ordered_cells) const {
    float max_power = ordered_cells[0].power;
    float median_power = max_power;

    if (ordered_cells.size() % 2 == 0) {
        float median_power = (ordered_cells[ordered_cells.size()/2].power + ordered_cells[ordered_cells.size()/2 - 1].power) / 2;
    }
    else {
        float median_power = ordered_cells[ordered_cells.size()/2].power;
    }
    return max_power / median_power;
}

void lightmap::CreateHistogram(string filename) const {
    vector<cell> ordered_cells = GetOrderedCells();

    TH2F *powerHist = new TH2F("Power (W)", "Lightmap", GRID.size(), 0, SIZE[0], GRID[0].size(), 0, SIZE[1]);
    powerHist->SetXTitle("x (cm)");
    powerHist->SetYTitle("y (cm)");

    for (int i = 0; i < GRID.size(); i++) {
        for (int j = 0; j < GRID[0].size(); j++) {
            powerHist->SetBinContent(i + 1, j + 1, GRID[i][j].power);
        }
    }

    TCanvas *c = new TCanvas("c", "c", 800, 600);
    powerHist->Draw("colz");
    c->SaveAs(filename.c_str());
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

float GetTotalPowerSize(array<float, 2> dimensions, array<float, 2> size) {
    lightsource S;
    S.coordinates = {0, 100, 100}; // default location (cm)
    S.power = 100; // default power (W)

    array<int, 2> ncell = {(int) round(dimensions[0]/size[0]), (int) round(dimensions[1]/size[1])};
    lightmap L(S, ncell, size);
    
    L.UpdatePower();
    return L.GetTotalPower();
}

void CreateGraph(vector<float> x, vector<float> y, string name) {
    TGraph *g = new TGraph(x.size(), &x[0], &y[0]); 
    TCanvas *c = new TCanvas("c", "c", 800, 600);

    // Set x-axis label
    g->GetXaxis()->SetTitle("Size (cm)");

    // Set y-axis label
    g->GetYaxis()->SetTitle("Power (W)");

    // Set graph title
    g->SetTitle("Power vs cell size");

    g->Draw("AC*");
    c->SaveAs(name.c_str());
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

    CreateGraph(sizes, total_power, "total_power.pdf");
    return 0;
}