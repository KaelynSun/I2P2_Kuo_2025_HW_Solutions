#include <iostream>
#include <string>
#include <sstream>
#include "13891.h"
using namespace std;

void CamelCase::convert(){
    this->converted = true;

    stringstream ss(this->name);
    string token, result;
    while(getline(ss, token, '-')){
        if(token.empty()) break;
        token[0] = (char)toupper(token[0]);
        result += token;
    }
    this->name = result;
}

void CamelCase::revert(){
    this->converted = false;

    stringstream ss;
    string token, result;
    bool isFirst = true;
    for(char &c: this->name){
        if(isupper(c)){
            if(!isFirst) ss << '-';
            isFirst = false;
            ss << (char)tolower(c);
        } else ss << c;
    }
    getline(ss, result);
    this->name = result;
}

ostream& operator << (ostream &os, Case &data){
    data.show(os);
    return os;
}

void convert_revert(Case &data){
    if(!data.is_converted()) data.convert();
    else data.revert();
}

int main(){
    string input_string;
    getline(cin, input_string);

    SnakeCase snake(input_string);
    convert_revert(snake);
    cout << "Snake Case (converted): " << snake << "\n";
    convert_revert(snake);
    cout << "Snake Case (reverted): " << snake << "\n";

    CamelCase camel(input_string);
    convert_revert(camel);
    cout << "Camel Case (converted): " << camel << "\n";
    convert_revert(camel);
    cout << "Camel Case (reverted): " << camel << "\n";
    return 0;
}
