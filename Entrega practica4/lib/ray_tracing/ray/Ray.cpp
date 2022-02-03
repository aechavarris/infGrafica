/*****************************************************************
 * File:    Ray.cpp
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Fichero de la implementación de la clase Ray
 *****************************************************************/

#pragma once

#include "Ray.h"

Ray::Ray(){};

Ray::Ray(Point origin, Vector dir) {
    this->origin = origin;
    this->direction = dir;
};