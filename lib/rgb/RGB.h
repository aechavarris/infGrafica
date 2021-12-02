/*****************************************************************
 * File:    RGB.h
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Implementa los colores RGB mediante una tupla (R, G, B),
 *          done cada valor float indica el tono rojo, verde y azul.
 *****************************************************************/

#pragma once

#include <iostream>
#include <math.h>
using namespace std;

#ifndef _RGB
#define _RGB

class RGB{

    public:

        float r, g, b;
    
        // -----------------------------------------
        // ------------ CONSTRUCTORES --------------
        // -----------------------------------------

        RGB();
        RGB(float r, float g, float b);


        // ---------------------------------------
        // --------- OPERADORES BÁSICOS ----------
        // ---------------------------------------

        RGB operator+(RGB color) const{
            return RGB(this->r + color.r, this->g + color.g, this->b + color.b);
        }

        RGB operator-(RGB color) const{
            return RGB(this->r + color.r, this->g + color.g, this->b + color.b);
        }

        RGB operator*(RGB color) const{
            return RGB(this->r * color.r, this->g * color.g, this->b * color.b);
        }

        RGB operator*(float num) const{
            return RGB(this->r * num, this->g * num, this->b * num);
        }

        RGB operator/(RGB color) const{
            return RGB(this->r / color.r, this->g / color.g, this->b / color.b);
        }

        RGB operator/(float num) const{
            return RGB(this->r / num, this->g / num, this->b / num);
        }  
};

#include  "RGB.cpp"
#endif