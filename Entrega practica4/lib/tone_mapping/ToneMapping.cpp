/*****************************************************************
 * File:    ToneMapping.cpp
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Fichero de la implementación de la clase ToneMapping 
 *****************************************************************/

#pragma once

#include "ToneMapping.h"
using namespace std;

ToneMapping::ToneMapping(){};

void ToneMapping::clamping(PPMFile &f) {
    for (int i = 0; i < f.height; i++) {
        for (int j = 0; j < f.width; j++) {
            if (f.RGBTuples[i][j].r > 1.0) f.RGBTuples[i][j].r = 1.0;
            if (f.RGBTuples[i][j].g > 1.0) f.RGBTuples[i][j].g = 1.0;
            if (f.RGBTuples[i][j].b > 1.0) f.RGBTuples[i][j].b = 1.0;
        }
    }
};

void ToneMapping::equalization(PPMFile &f, float maxValue){
    for (int i = 0; i < f.height; i++) {
        for (int j = 0; j < f.width; j++) {
            if (f.RGBTuples[i][j].r > maxValue) f.RGBTuples[i][j].r = 1.0;
            else f.RGBTuples[i][j].r = f.RGBTuples[i][j].r / maxValue;
            
            if (f.RGBTuples[i][j].g > maxValue) f.RGBTuples[i][j].g = 1.0;
            else f.RGBTuples[i][j].g = f.RGBTuples[i][j].g / maxValue;

            if (f.RGBTuples[i][j].b > maxValue) f.RGBTuples[i][j].b = 1.0;
            else f.RGBTuples[i][j].b = f.RGBTuples[i][j].b / maxValue;
        }
    }
};

void ToneMapping::gammaCurve(PPMFile &f, float gamma, float maxValue ){
    for (int i = 0; i < f.height; i++) {
        for (int j = 0; j < f.width; j++) {
            if (f.RGBTuples[i][j].r > maxValue) f.RGBTuples[i][j].r = 1.0;
            else f.RGBTuples[i][j].r = pow(f.RGBTuples[i][j].r / maxValue, gamma);

            if (f.RGBTuples[i][j].g > maxValue) f.RGBTuples[i][j].g = 1.0;
            else f.RGBTuples[i][j].g = pow(f.RGBTuples[i][j].g / maxValue, gamma);

            if (f.RGBTuples[i][j].b > maxValue) f.RGBTuples[i][j].b = 1.0;
            else f.RGBTuples[i][j].b = pow(f.RGBTuples[i][j].b / maxValue, gamma);
        }
    }
};