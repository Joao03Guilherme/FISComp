# ifndef __LIGHTMAP_HPP__
# define __LIGHTMAP_HPP__

# include <vector>
# include <array>
# include <string>

const int Z = 0; // m

using namespace std;

struct cell { 
    array<float, 3> center_coordinates {0, 0, Z}; // Cell center (m)
    float area; // Cell area (m^2)
    float power; // Cell incident power (W)
};

struct lightsource {
    array<float, 3> coordinates; // Light source coordinates (m)
    float power; // source power (W)
};

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
        void CreateHistogram(string filename); // create histogram of cell power
        void CreateGraph(vector<float> sizes, vector<float> total_power, string filename); // create graph of total power vs cell size

    private:
        void initializeGrid(array<int,2> ncell, array<float,2> size); // initialize grid cells
        float dot_product(array<float,3> A, array<float,3> B); // return dot product between two vectors

        vector<vector<cell>> GRID; // cells grid
        vector<lightsource> SOURCES; // light sources
        array<float, 2> SIZE; // plane dimensions (cm)
        array<float, 3> NORMAL; // plane normal
};

# endif // __LIGHTMAP_HPP__
