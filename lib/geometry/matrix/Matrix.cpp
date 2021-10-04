#pragma once

#include "Matrix.h"

Matrix::Matrix(){
    m[0][0] = 1;    m[0][1] = 0;    m[0][2] = 0;    m[0][3] = 0;
	m[1][0] = 0;    m[1][1] = 1;    m[1][2] = 0;    m[1][3] = 0;
	m[2][0] = 0;    m[2][1] = 0;    m[2][2] = 1;    m[2][3] = 0;
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
    Point mp = Point(0.0,0.0,0.0);

    mp.x = mp.x + p.x * this->m[0][0];
    mp.x = mp.x + p.x * this->m[0][1];
    mp.x = mp.x + p.x * this->m[0][2];

    mp.y = mp.y + p.y * this->m[1][0];
    mp.y = mp.y + p.y * this->m[1][1];
    mp.y = mp.y + p.y * this->m[1][2];

    mp.z = mp.z + p.z * this->m[2][0];
    mp.z = mp.z + p.z * this->m[2][1];
    mp.z = mp.z + p.z * this->m[2][2];

    return mp;
}

Point Matrix::productMatrixVector(Point p) {
    Point mv = Point();

    mv.x = mv.x + p.x * this->m[0][0];
    mv.x = mv.x + p.y * this->m[0][1];
    mv.x = mv.x + p.z * this->m[0][2];

    mv.y = mv.y + p.x * this->m[1][0];
    mv.y = mv.y + p.y * this->m[1][1];
    mv.y = mv.y + p.z * this->m[1][2];

    mv.z = mv.z + p.x * this->m[2][0];
    mv.z = mv.z + p.y * this->m[2][1];
    mv.z = mv.z + p.z * this->m[2][2];

    return mv;
}