//
// Created by carte on 11/25/2019.
//
using namespace std;
#include <ostream>
#include "Data.h"


Data::Data(int loc, double pres, double temper, double humid) {     //constructor for the Data object
    location = loc;
    pressure = pres;
    temperature = temper;
    humidity = humid;
}
ostream &operator<<(ostream &os, const Data &d) {
    os << d.location << " " << d.pressure << " " << d.temperature << "  " << d.humidity << endl;    //printing the Data object
    return os;
}

bool Data::operator<(const Data &rt) const {    //comparing two ratings
    return rt.location < location;
}

bool Data::operator>(const Data &rt) const {    //comparing two ratings
    return rt.location > location;
}


