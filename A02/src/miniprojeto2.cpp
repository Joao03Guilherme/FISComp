#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>
#include <fstream>

struct cell {
    std::array<float, 3> coo {0, 0, 100};
    float area; 
    float power;
    // ...
};

struct lightsource {
    std::array<float, 3> coo; 
    float power; 
};

class lightmap {
public:
    // construtores
    lightmap() = default;
    lightmap(std::array<int, 2> ncell, std::array<float, 2> size);
    lightmap(lightsource S, std::array<int, 2> ncell, std::array<float, 2> size);

    // getters
    std::pair<int, int> GetCellIndex(float x, float y) const;
    std::pair<float, float> GetCellCoo(int index_x, int index_y) const;
    double GetCellPower(int index_x, int index_y) const;
    double GetCellPower(float x, float y) const;
    int GetCellNx() const;
    int GetCellNy() const;
    const std::vector<std::vector<cell>>& GetCells() const;
    std::vector<std::vector<cell>>& GetCells();
    std::array<float, 3> GetNormal();

    // outras
    void AddLightSource(lightsource S);
    const cell& GetMaxCell() const;
    float distance2cell(std::array<float,3> SourceCoo,std::array<float,3> PointCoo);
    double calculocosseno();
    float Irradiance(std::array<float,3> SourceCoo,std::array<float,3> PointCoo);
    float CellPower(const cell& C);
    double calculatePowerQuotient();
    double potenciatotal();


private:
    std::vector<std::vector<cell>> GRID; // grid de células
    std::array<float, 2> size; // dimensão do plano
 
};

lightmap::lightmap(std::array<int, 2> ncell, std::array<float, 2> size)
    : size(size) {
    //criar o grid de células
    int nx = ncell[0];
    int ny = ncell[1];
    float cellWidth = size[0] / nx;
    float cellHeight = size[1] / ny;

    GRID.resize(nx, std::vector<cell>(ny));
    
    //preencher as células com suas coordenadas centrais, área e potência inicial
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            float cellCenterX = (i + 0.5) * cellWidth;
            float cellCenterY = (j + 0.5) * cellHeight;
            GRID[i][j].coo = {cellCenterX, cellCenterY, 100};
            GRID[i][j].area = cellWidth * cellHeight;
            GRID[i][j].power = 0.0; // power inicial
        }
    }
}

// construtor que já adiciona uma fonte de luz

lightmap::lightmap(lightsource S, std::array<int, 2> ncell, std::array<float, 2> size) : lightmap(ncell, size) {
    AddLightSource(S);
}


std::pair<int, int> lightmap::GetCellIndex(float x, float y) const {
    int nx = GetCellNx();
    int ny = GetCellNy();
    float cellWidth = size[0] / nx;
    float cellHeight = size[1] / ny;

    int index_x = std::floor(x / cellWidth);
    int index_y = std::floor(y / cellHeight);

        return std::make_pair(index_x, index_y);
}

std::pair<float, float> lightmap::GetCellCoo(int index_x, int index_y) const {
    int nx = GetCellNx();
    int ny = GetCellNy();
    float cellWidth = size[0] / nx;
    float cellHeight = size[1] / ny;

    float cellCenterX = (index_x + 0.5) * cellWidth;
    float cellCenterY = (index_y + 0.5) * cellHeight;

    return std::make_pair(cellCenterX, cellCenterY);
}

double lightmap::GetCellPower(int index_x, int index_y) const {
    return GRID[index_x][index_y].power;
}

double lightmap::GetCellPower(float x, float y) const {
    std::pair<int, int> cellIndex = GetCellIndex(x, y);
    return GetCellPower(cellIndex.first, cellIndex.second);
}

int lightmap::GetCellNx() const {
    return GRID.size();
}

int lightmap::GetCellNy() const {
    if (GRID.empty())
        return 0;
    else
        return GRID[0].size();
}

const std::vector<std::vector<cell>>& lightmap::GetCells() const {
    return GRID;
}

std::vector<std::vector<cell>>& lightmap::GetCells() {
    return GRID;
}

std::array<float, 3> lightmap::GetNormal() {
    // retorna o vetor normal ao plano
    return {0, 0, 1};
}

void lightmap::AddLightSource(lightsource S) {
    std::pair<int, int> cellIndex = GetCellIndex(S.coo[0], S.coo[1]);
    int index_x = cellIndex.first;
    int index_y = cellIndex.second;

    if (index_x >= 0 && index_x < GetCellNx() && index_y >= 0 && index_y < GetCellNy()) {
        GRID[index_x][index_y].power += S.power;
    } else {
        std::cout << "Erro!" << std::endl;
    }
}

//retorna a célula com maior potência
const cell& lightmap::GetMaxCell() const {
    int nx = GetCellNx();
    int ny = GetCellNy();
    int max_x = 0;
    int max_y = 0;
    double max_power = 0.0;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            if (GRID[i][j].power > max_power) {
                max_power = GRID[i][j].power;
                max_x = i;
                max_y = j;
            }
        }
    }
    return GRID[max_x][max_y];
}
//determinar a distancia r ao ponto

float lightmap::distance2cell(std::array<float,3> SourceCoo,std::array<float,3> PointCoo){
    return std::sqrt(std::pow(SourceCoo[0]-PointCoo[0],2)+std::pow(SourceCoo[1]-PointCoo[1],2)+std::pow(SourceCoo[2]-PointCoo[2],2));
}

//produto interno entre o vector direção fonte-ponto unitário r e o vector normal ao plano

double lightmap::calculocosseno(){
    std::array<float, 3> normal = GetNormal();
    std::array<float, 3> r = {0, 0, 1};
    float cosseno = (normal[0]*r[0]+normal[1]*r[1]+normal[2]*r[2]);
    return cosseno;
}

//irradiancia

float lightmap::Irradiance(std::array<float,3> SourceCoo,std::array<float,3> PointCoo){
    float r = distance2cell(SourceCoo,PointCoo);
    float cosseno = calculocosseno();
    float irradiancia = (100*cosseno)/(4*M_PI*r*r);
    return irradiancia;
}

//cell power

float lightmap::CellPower(const cell& C){
    //teste
    std::array<float, 3> source {0.0, 0.0, 100.0};
    std::array<float,3> cellcentercoo {GetCellCoo(GetCellIndex(C.coo[0],C.coo[1]).first,GetCellIndex(C.coo[0],C.coo[1]).second).first,GetCellCoo(GetCellIndex(C.coo[0],C.coo[1]).first,GetCellIndex(C.coo[0],C.coo[1]).second).second};
    int nx = GetCellNx();
    int ny = GetCellNy();
    float cellWidth = size[0] / nx;
    float cellHeight = size[1] / ny;
    double area = cellWidth*cellHeight;
    double potencia = Irradiance(source,cellcentercoo)*area;
    return potencia;

}

double lightmap::calculatePowerQuotient() {
    std::vector<cell> vGRID;
    for (const auto& row : GRID) {
        for (const auto& c : row) {
            vGRID.push_back(c);
        }
    }

    std::sort(vGRID.begin(), vGRID.end(), [](const cell& a, const cell& b) {
        return a.power < b.power;
    });

    const cell& maxCell = GetMaxCell(); 
    double maxPower = maxCell.power;
    int medianIndex = vGRID.size() / 2;
    const cell& medianCell = vGRID[medianIndex];
    double medianPower = medianCell.power;

    double powerQuotient = maxPower / medianPower;
    return powerQuotient;
}

//atualizar a potencia de cada célula no GRID
void atualizacao(std::vector<std::vector<cell>>& GRID) {
    lightmap L; 
    for (int i = 0; i < GRID.size(); i++) {
        for (int j = 0; j < GRID[i].size(); j++) {
            GRID[i][j].power = L.CellPower(GRID[i][j]); 
        }
    }
}

//função para calcular a soma da potencia de cada célula no GRID
double lightmap::potenciatotal(){
    double potenciatot = 0.0;
    for (int i = 0; i < GRID.size(); i++) {
        for (int j = 0; j < GRID[i].size(); j++) {
            potenciatot += GRID[i][j].power;
        }
    }
    return potenciatot;
}



int main() {
    const double PI = M_PI;
    const double fRad = 100.0; 
    const double dis = 1.0;
    const double rEsfera = dis;

    double intensidadeRadiante;
    double da;
    double ds = 0.0;

    // ângulo sólido

    for (double x = -1.0; x <= 1.0; x += 0.01) {
        for (double y = -1.5; y <= 1.5; y += 0.01) {
            if (x * x + y * y <= 1.0) {
                ds += 0.01 * 0.01;
            }
        }
    }
    da = ds / (rEsfera * rEsfera);

    //intensidade radiante
    intensidadeRadiante = fRad / da;

    std::cout << "A intensidade é: " << intensidadeRadiante << " Watts steradian ^ -1" << std::endl;

    //tests

    std::array<float, 3> SourceCoo = {0.0, 100.0};
    std::array<float, 3> PointCoo = {0.0, 0.0};

    lightsource S;
    S.coo = SourceCoo; 
    S.power = intensidadeRadiante; 

    lightmap L(S, {100, 100}, {2.0, 2.0});
    float irradiance = L.Irradiance(SourceCoo, PointCoo);

    std::cout << "A irradiância no ponto {0,0} é: " << L.Irradiance(SourceCoo,PointCoo) << " Watts m ^ -2" << std::endl;

    //teste cell power

    cell c;

    c.coo = {1.0, 2.0, 3.0};
    c.area = 10.0;
    c.power = 50.0;


    std::cout << "A potência da célula é: " << L.CellPower(c) << " Watts" << std::endl;

    //powerquotient

    std::cout << "O quociente de potência é: " << L.calculatePowerQuotient() << std::endl;

    //potencia total

    std::cout << "A potência total é: " << L.potenciatotal() << " Watts" << std::endl;


    return 0;
}

