#pragma once

#include "Matrix.h"

Matrix::Matrix(){
    m[0][0] = 1;    m[0][1] = 0;    m[0][2] = 0;    m[0][3] = 0;
	m[1][0] = 0;    m[1][1] = 1;    m[1][2] = 0;    m[1][3] = 0;
	m[2][0] = 0;    m[2][1] = 0;    m[2][2] = 1;    m[2][3] = 0;
	m[3][0] = 0;    m[3][1] = 0;    m[3][2] = 0;    m[3][3] = 1;
};

Matrix::Matrix(const Vector v0, const Vector v1, const Vector v2, const Point p) {
	m[0][0] = v0.x; m[0][1] = v1.x; m[0][2] = v2.x ;m[0][3] = p.x;
	m[1][0] = v0.y; m[1][1] = v1.y; m[1][2] = v2.y ;m[1][3] = p.y;
	m[2][0] = v0.z; m[2][1] = v1.z; m[2][2] = v2.z ;m[2][3] = p.z;
	m[3][0] = 0;    m[3][1] = 0;    m[3][2] = 0;    m[3][3] = 1;
};

Matrix::Matrix(float f[4][4]){
    m[0][0] = f[0][0];  m[0][1] = f[0][1];  m[0][2] = f[0][2];   m[0][3] = f[0][3];
	m[1][0] = f[1][0];  m[1][1] = f[1][1];  m[1][2] = f[1][2];   m[1][3] = f[1][3];
	m[2][0] = f[2][0];  m[2][1] = f[2][1];  m[2][2] = f[2][2];   m[2][3] = f[2][3];
	m[3][0] = f[3][0];  m[3][1] = f[3][1];  m[3][2] = f[3][2];   m[3][3] = f[3][3];
};

Matrix::Matrix(float f00, float f01, float f02, float f03,
               float f04, float f05, float f06, float f07,                                         
               float f08, float f09, float f10, float f11,
               float f12, float f13, float f14, float f15) {
    m[0][0] = f00;  m[0][1] = f01; m[0][2] = f02; m[0][3] = f03;
	m[1][0] = f04;  m[1][1] = f05; m[1][2] = f06; m[1][3] = f07;
	m[2][0] = f08;  m[2][1] = f09; m[2][2] = f10; m[2][3] = f11;
	m[3][0] = f12;  m[3][1] = f13; m[3][2] = f14; m[3][3] = f15;
};

Matrix Matrix::transposeMatrix() {
    return Matrix(this->m[0][0], this->m[1][0], this->m[2][0], this->m[3][0],
                  this->m[0][1], this->m[1][1], this->m[2][1], this->m[3][1],
                  this->m[0][2], this->m[1][2], this->m[2][2], this->m[3][2],
                  this->m[0][3], this->m[1][3], this->m[2][3], this->m[3][3]);
}

Matrix Matrix::productMatrixMatrix(Matrix p) {
    Matrix mm = Matrix();
    for(int i = 0; i < 4; i++ ){
        for(int j = 0; j < 4; j++){
            mm.m[i][j] = this->m[i][0] * p.m[0][j] + this->m[i][1] * p.m[1][j]  +  this->m[i][2] * p.m[2][j] + this->m[i][3] * p.m[3][j];
        }
    }
    return mm;
}

Point Matrix::productMatrixPoint(Point p) {
    Point mp = Point(0.0, 0.0, 0.0);
    
    mp.x = mp.x + this->m[0][0] * p.x;
    mp.x = mp.x + this->m[0][1] * p.y;
    mp.x = mp.x + this->m[0][2] * p.z;
    
    mp.y = mp.y + this->m[1][0] * p.x;
    mp.y = mp.y + this->m[1][1] * p.y;
    mp.y = mp.y + this->m[1][2] * p.z;

    mp.z = mp.z + this->m[2][0] * p.x;
    mp.z = mp.z + this->m[2][1] * p.y;
    mp.z = mp.z + this->m[2][2] * p.z;

    return mp;
}

Vector Matrix::productMatrixVector(Vector v) {
    Vector mv = Vector();

    mv.x = mv.x + this->m[0][0] * v.x;
    mv.x = mv.x + this->m[0][1] * v.y;
    mv.x = mv.x + this->m[0][2] * v.z;         
    
    mv.y = mv.y + this->m[1][0] * v.x;
    mv.y = mv.y + this->m[1][1] * v.y;
    mv.y = mv.y + this->m[1][2] * v.z;

    mv.z = mv.z + this->m[2][0] * v.x;
    mv.z = mv.z + this->m[2][1] * v.y;
    mv.z = mv.z + this->m[2][2] * v.z;
    return mv;
}