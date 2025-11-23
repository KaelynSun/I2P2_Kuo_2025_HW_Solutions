#include <bits/stdc++.h>
using namespace std;

class Function{
    public:
    static Function *parse(stringstream &ss);
    virtual Function *differential() = 0;
    virtual double eval(double) = 0;
};

