#pragma once

#include "Primitive.h"

Primitive::Primitive(){};

bool Primitive::intersect(Ray ray, float* t, RGB* color, bool* end){return 0;};

string Primitive::russianRoulette() {
    if ( this->matProperties.lambertianDiffuse != 0.0 && this->matProperties.deltaBRDF != 0.0 ) { // Plastic Material

    }
    else if ( this->matProperties.deltaBRDF != 0.0 && this->matProperties.deltaBTDF != 0.0 ) { // Dielectric Material

    }
    else { // Pure Diffuse Material

    }
    return "";
}