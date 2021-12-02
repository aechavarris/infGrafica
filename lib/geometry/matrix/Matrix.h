/*****************************************************************
 * File:    Matrix.h
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Representa una matriz de 4x4 y todas sus operaciones 
 *          posibles
 *****************************************************************/

#pragma once

#include <iostream>
#include <math.h>
#include "../../../lib/geometry/vector/Vector.h"
#include "../../../lib/geometry/point/Point.h"
using namespace std;

#ifndef _MATRIX
#define _MATRIX

class Matrix{

    public:
    
        /*
         * Constructores de la clase Matrix
         */
        Matrix();
        Matrix(Vector v0, Vector v1, Vector v2, Point p);
        Matrix(float f[4][4]);
        Matrix(float f00, float f01, float f02, float f03,
            float f04, float f05, float f06, float f07,                                         
            float f08, float f09, float f10, float f11,
            float f12, float f13, float f14, float f15);


        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        /*
         * Pre:
         * Post:
         */
        Matrix transposeMatrix();

        /*
         * Pre:
         * Post:
         */
        Matrix productMatrixMatrix(Matrix m);

        /*
         * Pre:
         * Post:
         */
        Point productMatrixPoint(Point p);

        /*
         * Pre:
         * Post:
         */
        Vector productMatrixVector(Vector v);

        /*
         * Pre:
         * Post:
         */
        Matrix inverse();

    private:
        float m[4][4];
    
};

#include  "Matrix.cpp"
#endif