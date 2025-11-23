#include <bits/stdc++.h>
#include "13890.h"
using namespace std;

class Constant : public Function{
private:
    double value;
public:
    static Constant *create(double x){
        Constant *c = new Constant;
        c->value = x;
        return c;
    }
    double eval(double x) override{
        return value;
    }
};

class Variable : public Function{
public:
    static Variable *create(string s){
        return new Variable();
    }
    double eval(double x){
        return x;
    }
};

class Polynomial : public Function{
private:
    Function *base;
    Function *exponent;

public:
    static Polynomial *create(Function *a, Function *b){
        Polynomial *p = new Polynomial(); //create a new polynomial object?
        p->base = a;
        p->exponent = b;
        return p;
    }
    double eval(double x) override{
        double b = base->eval(x);
        double e = exponent->eval(x);
        return pow(b, e);
    }
};

class Arithmetic : public Function{
private:
    Function *left;
    Function *right;
    char op;
public:
    static Arithmetic *create(Function *a, char op, Function *b){
        Arithmetic *ar = new Arithmetic();
        ar->left = a;
        ar->right = b;
        ar->op = op;
        return ar;
    }
    double eval(double x) override{
        double l = left->eval(x);
        double r = right->eval(x);
        switch(op){
            case '+' : return l + r;
            case '-' : return l - r;
            case '*' : return l * r;
            case '/' : return l / r;
            default: return 0;
        }
    }
};

class Sin : public Function{
private:
    Function *inner;
public:
    static Sin *create(Function *a){
        Sin * s = new Sin();
        s->inner = a;
        return s;
    }
    double eval(double x) override{
        return sin(inner->eval(x));
    }
};

class Cos : public Function{
private:
    Function *inner;
public:
    static Cos *create(Function *a){
        Cos *c = new Cos();
        c->inner = a;
        return c;
    }
    double eval(double x) override{
        return cos(inner->eval(x));
    }
};

Function* Function::parse(stringstream &ss){
    string s;
    ss >> s;
    if(s == "+" || s == "-" || s == "*" || s == "/"){
        Function *a = parse(ss), *b = parse(ss);
        Function *now = Arithmetic::create(a, s[0], b);
        return now;
    }else if(s[0] == 'x'){
        Function *now = Variable::create(s);
        return now;
    }else if(s == "**"){
        Function *a = parse(ss), *b = parse(ss);
        Function *now = Polynomial::create(a, b);
        return now;
    }else if(s == "sin"){
        Function *a = parse(ss);
        Function *now = Sin::create(a);
        return now;
    }else if(s == "cos"){
        Function *a = parse(ss);
        Function *now = Cos::create(a);
        return now;
    }else{
        Function *now = Constant::create(atoi(s.c_str()));
        return now;
    }
}

void solve(){
    string tmp;
    getline(cin, tmp);
    stringstream ss(tmp);
    Function *now = Function::parse(ss);
    int q; cin >> q;
    while(q--){
        double x; cin >> x;
        cout << fixed << setprecision(2) << now -> eval(x) << endl;
    }
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    solve();
    return 0;
}
