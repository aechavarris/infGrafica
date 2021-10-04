#pragma once

#include <iostream>
#include "../../../lib/geometry/vector/Vector.h"
#include "../../../lib/geometry/point/Point.h"
#include "Planet.h"
using namespace std;

Planet::Planet(){};

Planet::Planet (Point center, Vector axis, Point referenceCity) {
    float radio = axis.module() / 2;
    float radio2 = center.distanceBetweenPoint(referenceCity);
    cout << "Radio: " << radio << endl;
    cout << "Radio2: " << radio2 << endl;
    if ( abs(radio - radio2) <= pow(10, -6) ) {
        this->center = center;
        this->axis = axis;
        this->referenceCity = referenceCity;
    }
    else {
        cerr << "El planeta que se ha intentado crear no cumple las restricciones" << endl;
    }
}