#include "14309.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <cassert>

namespace oj {
    void Nut::setVolume(double v) {
        volume = v;
    }

    double Nut::getVolume() {
        return volume;
    }

    // Implementing all the constructors and handle inputs <= 0

    CuboidNut::CuboidNut(double h, double w, double l) : height(h), width(w), length (l){
        if(h <= 0 || w <= 0 || l <= 0){
            setVolume(0);
        } else{
            setVolume(h * w * l);
        }
    }

    SphereNut::SphereNut(double r) : radius(r) {
        if(r <= 0){
            setVolume(0);
        } else{
            setVolume((4.0000/3.0000) * oj::Nut::PI * r * r * r);
        }
    }

    ConeNut::ConeNut(double r, double h) : radius(r), height(h) {
        if(r <= 0 || h <= 0){
            setVolume(0);
        } else{
            setVolume((1.0/3.0000) * oj::Nut::PI * r * r * h);
        }
    }

    CylinderNut::CylinderNut(double r, double h) : radius(r), height(h) {
        if(r <= 0 || h <= 0){
            setVolume(0);
        } else{
            setVolume(oj::Nut::PI * r * r * h);
        }
    }

    CubeNut::CubeNut(double s) : CuboidNut(s, s, s){
    }
}

int main(void) {
    using namespace oj;
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;

    string shape;
    double totalVolume = 0.0;

    while (cin >> shape) {
        if (shape == "Cube") {
            double s;
            cin >> s;
            CubeNut cube(s);
            totalVolume += cube.getVolume();
        } else if (shape == "Cuboid") {
            double l, w, h;
            cin >> l >> w >> h;
            CuboidNut cuboid(l, w, h);
            totalVolume += cuboid.getVolume();
        } else if (shape == "Sphere") {
            double r;
            cin >> r;
            SphereNut sphere(r);
            totalVolume += sphere.getVolume();
        } else if (shape == "Cone") {
            double r, h;
            cin >> r >> h;
            ConeNut cone(r, h);
            totalVolume += cone.getVolume();
        } else if (shape == "Cylinder") {
            double r, h;
            cin >> r >> h;
            CylinderNut cylinder(r, h);
            totalVolume += cylinder.getVolume();
        } else {
            assert(false);
        }
    }

    cout << std::setprecision(4) << std::fixed;   // set precision to 4 decimal places
    cout << totalVolume << endl;

    return 0;
}
