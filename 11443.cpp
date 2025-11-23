#include <iostream>
#include <string>
#include "11443.h"
using namespace std;

namespace oj
{
    void Shape3D::setVolume(double v)
    {
        volume = v;
    }

    double Shape3D::getVolume()
    {
        return volume;
    }

    Sphere::Sphere(double r, double p) : radius(r), pi(p){
        if(r <= 0 || pi <= 0){
            setVolume(0);
        } else{
            setVolume((4.0/3.0) * p * r *r * r);
        }
    }

    Cone::Cone(double r, double h, double p) : radius(r), height(h), pi(p){
        if(r <= 0 || h <= 0 || p <= 0){
            setVolume(0);
        } else{
            setVolume((1.0/3.0) * p * r * r * h);
        }
    }

    Cuboid::Cuboid(double l, double w, double h) : length(l), width(w), height(h) {
        if(l <= 0 || w <= 0 || h <= 0){
            setVolume(0);
        } else{
            setVolume(l * w * h);
        }
    }

    Cube::Cube(double s) : Cuboid(s, s, s){}

}


int main(void)
{
    using namespace oj;

    string s;
    double a, b, c;
    double totalVolume = 0.0, totalPerimeter = 0.0;

    while(cin >> s) {
        if(s == "Sphere") {
            cin >> a >> b;
            Sphere sphere(a, b);
            totalVolume += sphere.getVolume();
            //cout << "Ball: " << sphere.getVolume() << endl;
        }
        if(s == "Cone") {
            cin >> a >> b >> c;
            Cone cone(a, b, c);
            totalVolume += cone.getVolume();
            //cout << "Cone: " << cone.getVolume() << endl;
        }
        if(s == "Cuboid") {
            cin >> a >> b >> c;
            Cuboid cuboid(a, b, c);
            totalVolume += cuboid.getVolume();
            //cout << "Cuboid: " << cuboid.getVolume() << endl;
        }
        if(s == "Cube") {
            cin >> a;
            Cube cube(a);
            totalVolume += cube.getVolume();
            //cout << "Cube: " << cube.getVolume() << endl;
        }
    }

    cout << totalVolume << endl;

    return 0;
}
