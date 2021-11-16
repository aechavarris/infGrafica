#pragma once

#include <iostream>
#include <math.h>
#include "../../../lib/geometry/point/Point.h"
using namespace std;

#ifndef _VECTOR
#define _VECTOR

class Vector {
    public:
        float x;
        float y;
        float z;

        /*
         * Constructor de la clase Vector
         */
        Vector();
        Vector(float x, float y, float z);


        // ---------------------------------------
        // --------- OPERADORES BÁSICOS ----------
        // ---------------------------------------

        Vector operator+(Vector v) const{
            return Vector(this->x + v.x, this->y + v.y, this->z + v.z);
        }

        Vector operator+(float num) const{
            return Vector(this->x + num, this->y + num, this->z + num);
        }
        Vector operator+(Point p) const{
            return Vector(this->x + p.x, this->y + p.y, this->z + p.z);
        }
        Vector operator-(Vector v) const{
            return Vector(this->x - v.x, this->y - v.y, this->z - v.z);
        }

        Vector operator-(float num) const{
            return Vector(this->x - num, this->y - num, this->z - num);
        }

        Vector operator*(Vector v) const{
            return Vector(this->x * v.x, this->y * v.y, this->z * v.z);
        }

        Vector operator*(float num) const{
            return Vector(this->x * num, this->y * num, this->z * num);
        }

        Vector operator/(Vector v) const{
            return Vector(this->x / v.x, this->y / v.y, this->z / v.z);
        }

        Vector operator/(float num) const{
            return Vector(this->x / num, this->y / num, this->z / num);
        }


        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        /*
         * Pre:
         * Post:
         */
        float module();

        /*
         * Pre:
         * Post:
         */
        float dot(Vector v);

        /*
         * Pre:
         * Post:
         */
        float dot(Point p);

        /*
         * Pre:
         * Post:
         */
        Vector cross(Vector v);
        Vector normalize();
        /*
         * Pre:
         * Post:
         */
        Vector vectorBetweenVector(Vector v);

        /*
         * Pre:
         * Post:
         */
        float distanceBetweenVector(Vector v);
};

#include  "Vector.cpp"
#endif