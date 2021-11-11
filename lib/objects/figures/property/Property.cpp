#pragma once

#include "Property.h"

Property::Property(){};

Property::Property(float lambertian, float deltaBRDF, float deltaBTDF) {
    if ( (lambertian + deltaBRDF + deltaBTDF) <= 1.0 ) {
        this->lambertianDiffuse = lambertian;
        this->deltaBRDF = deltaBRDF;
        this->deltaBTDF = deltaBTDF;
    }
    else {
        cout << "El sumatorio de Lambertian, DeltaBRDF y DeltaBTDF debe ser <= 1.0" << endl;
    }
}