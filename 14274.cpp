#include "14274.h"

#include <iomanip>
#include <iostream>

using namespace std;

Vector Vector::operator+(Vector const& rhs) const {
    return Vector(x + rhs.x, y + rhs.y);
}

double Vector::operator*(Vector const& rhs) const { //This is the DOT Product
    return x * rhs.x + y * rhs.y;
}

double Vector::operator^(Vector const& rhs) const {
    return x * rhs.y - y * rhs.x;
}

double Vector::area(Vector const& rhs) const {
    return abs((*this ^ rhs)) / 2.0;
}

Vector Vector::projection(Vector const& rhs) const {
    double scalar = (*this * rhs) / (rhs * rhs);
    return Vector(scalar * rhs.x, scalar * rhs.y);
}

//masukkin sampe sini trus 14274.h diganti jadi function.h

ostream& operator<<(ostream& os, Vector const& v) {
    return os << '(' << v.x << ',' << v.y << ')';
}

signed main() {
    double x, y;
    cin >> x >> y;
    Vector v1(x, y);
    cin >> x >> y;
    Vector v2(x, y);

    cout.precision(3);
    cout.setf(ios::fixed);
    cout << "v1 + v2 = " << v1 + v2 << endl;
    cout << "v1 dot v2 = " << v1 * v2 << endl;
    cout << "v1 cross v2 = " << (v1 ^ v2) << endl;
    cout << "Area of v1 v2: " << v1.area(v2) << endl;
    cout << "project v1 onto v2 = " << v1.projection(v2) << endl;

    return 0;
}
