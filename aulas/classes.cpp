# include <iostream>
# include <array>
# include <string>
# include <stdlib.h>
# include <stdio.h>
# include <vector>

// Root
// Inlucde form

using namespace std;

// Class declaration

class Point2D {
    public:
        Point2D(string name="", double x=0, double y=0); // Constructor
        Point2D(const Point2D&); // Copy constructor
        ~Point2D(); // Destructor

        void Print() const; // Print point coordinates
        friend ostream& operator<< (ostream&, const Point2D&); // Print point coordinates

        Point2D& operator= (const Point2D&);
        Point2D operator+ (const Point2D&);
        Point2D operator- (const Point2D&);

    protected:
        string name;
        array<double, 2> coords;
};

class Point3D : public Point2D { // Inheritance
    public:
        Point3D(string name="", double x=0, double y=0, double z=0) : Point2D(name, x, y) { // Constructor
            this->z = z;
        };

        void Print() const; // Print point coordinates
        friend ostream& operator<< (ostream&, const Point3D&); // Print point coordinates

    private:
        double z;
};

class Polygon {
    public:
        Polygon(vector<Point2D>&); // Constructor
    private:
        vector<Point2D> vertices;
};


// Implementation

Point2D::Point2D(string name, double x, double y) { // Constructor
    this->name = name;
    this->coords = {x, y};
}

Point2D::Point2D(const Point2D& P) { // Copy constructor
    this->name = P.name + "_copy";
    this->coords = P.coords;
}

Point2D::~Point2D() { // Destructor
    printf("[%s] %s: %.1f %.1f\n", __PRETTY_FUNCTION__, name.c_str(), coords[0], coords[1]);
}

void Point2D::Print() const { // Print point coordinates
    printf("%s : %.1f %.1f\n" , name.c_str(), coords[0], coords[1]);
}

// Friend function
ostream& operator<<(ostream& os, const Point2D& P) { // Print point coordinates
    os << P.name << " : " << P.coords[0] << " " << P.coords[1] << endl;
    return os;
}

Point2D& Point2D::operator= (const Point2D& P) {
    if (this == &P) return *this;

    this->name = P.name;
    this->coords = P.coords;
    return *this;
}

Point2D Point2D::operator+ (const Point2D& P) {
    return Point2D(this->name + " + " + P.name, this->coords[0] + P.coords[0], this->coords[1] + P.coords[1]);
}

Point2D Point2D::operator- (const Point2D& P) {
    return Point2D(this->name + " - " + P.name, this->coords[0] - P.coords[0], this->coords[1] - P.coords[1]);
}

void Point3D::Print() const { // Print point coordinates
    printf("%s : %.1f %.1f %.1f\n" , name.c_str(), coords[0], coords[1], z);
}

// Friend function
ostream& operator<<(ostream& os, const Point3D& P) { // Print point coordinates
    os << P.name << " : " << P.coords[0] << " " << P.coords[1] << " " << P.z << endl;
    return os;
}

// Main program
int main() {
    Point2D P1("A", 1, 1);
    Point2D P2("B", 2, 2);
    Point2D P3(P2);

    // cout << P1 << P2 << P3;

    Point2D P4 = P1 + P2;
    Point3D P3D("C", 3, 3, 3);

    cout << P3D;
    cout << P4;
}