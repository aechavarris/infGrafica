/*****************************************************************
 * File:    RGB.cpp
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Fichero de la implementación de la clase RGB
 *****************************************************************/

#pragma once

#include "RGB.h"

RGB::RGB(){
    this->r = 0;
    this->g = 0;
    this->b = 0;
};

RGB::RGB(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
};