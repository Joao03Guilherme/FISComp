# include <iostream>
using namespace std;

class Point2D {
    public:
        Point2D(double x, double y);
        friend &ofstream operator<<(&ofstream s, const Point2D& p);

    private:
        double x = 0, y = 0;
};

class Point3D : Point2D {
    public:
        Point3D(double x, double y, double z);
        friend &ofstream operator<<(&ofstream s, const Point2D& p);

    private:
        double z;
};

Point2D::Point2D(double x, double y) x(x), y(y) {;}
ofstream& Point2D::operator<<(Point2D& p, &ofstream s) {
    s << p
}

Point3D::Point3D(double x, double y, double z) : Point2D(x, y), z(z) {;}

int main() {
    return 0;
}
