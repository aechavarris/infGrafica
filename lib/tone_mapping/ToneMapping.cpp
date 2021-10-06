#pragma once

#include "ToneMapping.h"
using namespace std;

ToneMapping::ToneMapping(){};

void ToneMapping::clamping(PPMFile &f){
    for (int i = 0; i < f.height; i++){
        for (int j = 0;j < f.width; j++){
            if(f.RGBTuples[i][j].r>1.0){
                f.RGBTuples[i][j].r=1.0;
            }
            if(f.RGBTuples[i][j].g>1.0){
                f.RGBTuples[i][j].g=1.0;
            }
            if(f.RGBTuples[i][j].b>1.0){
                f.RGBTuples[i][j].b=1.0;
            }
        }
    }
};

void ToneMapping::equalization(PPMFile &f, float maxValue){

};

void ToneMapping::gammaCurve(PPMFile &f){

};