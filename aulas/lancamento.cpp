# include <iostream>
# include <vector>
# include <cstdio>

// ROOT
# include "TF1.h"
# include "TApplication.h"
# include "TCanvas.h"
# include "TSystem.h"

using namespace std;

int main() {
    double y0 = 200; // m
    double v0 = 25; // m/s
    double g = 9.80665; // m/s^2

    // lambda funtion
    auto y = [y0, v0, g](double t) { return y0 + v0 * t - 0.5 * g * t * t; };

    vector<pair<double, double>> points;

    // Start data aquisition
    for (double t = 0; t <= 10; t += 0.01) {
        points.push_back(make_pair(t, y(t)));
    }

    cout << "Vector size: " << points.size() << endl;
    cout << "y(0.5) = " << y(0.5) << endl;

    int idx;
    for (int i = 0; i < points.size() - 1; i++) {
        if (points[i].second * points[i+1].second < 0) {
            idx = i; break;
        }
    }

    // Print interval 
    printf("time = [%6.3f, %6.3f ] | positions = [%6.3f, %6.3f ]\n", 
            points[idx].first, points[idx+1].first, 
            points[idx].second, points[idx+1].second);

    double m_line = (points[idx+1].second - points[idx].second) / (points[idx+1].first - points[idx].first);
    double b_line = points[idx].second - m_line * points[idx].first;
    double time = -b_line / m_line;

    cout << "t_crossing = " << time << " " << "y(t_crossing) = " << y(time) << endl;

    auto f = [g](double* x, double* par) {
        // x[0]: time
        // par[0]: y0
        // par[1]: v0
        return par[0] + par[1] * x[0] - 0.5 * g * x[0] * x[0];
    };

    TF1 F("F", f, 0, 10, 2); 
    F.SetParameters(y0, v0); 
    F.SetLineWidth(5);
    F.SetLineColor(kBlue + 1);

    TApplication A("A", 0, 0);  
    TCanvas C("canvas", "canvas teste", 1000, 800);

    F.Draw();
    C.Update();
    gSystem->ProcessEvents();
    C.WaitPrimitive();
}