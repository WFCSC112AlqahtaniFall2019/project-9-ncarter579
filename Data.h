//
// Created by carte on 11/25/2019.
//

#ifndef PROJECT9_DATA_H
#define PROJECT9_DATA_H
#include <iostream>
using namespace std;

class Data{
public:
    friend ostream& operator<<( ostream& os, const Data& d); //output stream overload operator
    bool operator<(const Data &rt) const;     //overload operator for <
    bool operator>(const Data &rt) const;    //overload operator for >
    Data(int loc, double pres, double temper, double humid);     //constructor
    Data(){};   //default constructor
private:
    int location;              //four data points
    double pressure;
    double temperature;
    double  humidity;
};

#endif //PROJECT9_DATA_H
