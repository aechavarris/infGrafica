#pragma once

#include <iostream>
#include <math.h>
using namespace std;

#ifndef _POINT
#define _POINT

class Point{
    public:
        float x;
        float y;
        float z;
        float w;

        /*
         * Constructor de la clase Point
         */
        Point();
        Point(float x, float y, float z);


        // ---------------------------------------
        // --------- OPERADORES BÁSICOS ----------
        // ---------------------------------------

        Point operator+(Point p) const{
            return Point(this->x + p.x, this->y + p.y, this->z + p.z);
        }
        
        Point operator+(float num) const{
            return Point(this->x + num, this->y + num, this->z + num);
        }

        Point operator-(Point p) const{
            return Point(this->x - p.x, this->y - p.y, this->z - p.z);
        }
        
        Point operator-(float num) const{
            return Point(this->x - num, this->y - num, this->z - num);
        }

        Point operator*(Point p) const{
            return Point(this->x * p.x, this->y * p.y, this->z * p.z);
        }
        
        Point operator*(float num) const{
            return Point(this->x * num, this->y * num, this->z * num);
        }

        Point operator/(Point p) const{
            return Point(this->x / p.x, this->y / p.y, this->z / p.z);
        }

        Point operator/(float num) const{
            return Point(this->x / num, this->y / num, this->z / num);
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
        float dot(Point p);
        
        /*
         * Pre:
         * Post:
         */
        Point pointBetweenPoint(Point p);

        /*
         * Pre:
         * Post:
         */
        float distanceBetweenPoint(Point p);
};

#include  "Point.cpp"
#endif