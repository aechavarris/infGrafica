/*****************************************************************
 * File:    Light.cpp
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Fichero de la implementación de la clase Light 
 *****************************************************************/

#pragma once

#include "Light.h"

Light::Light(){};

Light::Light(Point center, RGB c,int i) {
    this->center = center;
    this->color = c;
    this->intensity = i;
}