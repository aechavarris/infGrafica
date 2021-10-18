#pragma once

#include <iostream>
#include <math.h>
#include "ToneMapping.h"
#include "../../lib/img_files/PPMFile.h"

#ifndef _TONE_MAPPING
#define _TONE_MAPPING

class ToneMapping{

    public:
    
        /*
         * Constructores de la clase ToneMapping
         */
        ToneMapping();


        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        /*
         * Pre:
         * Post:
         */
        void clamping(PPMFile &f);

        /*
         * Pre:
         * Post:
         */
        void equalization(PPMFile &f, float maxValue);

        /*
         * Pre:
         * Post:
         */
        void gammaCurve(PPMFile &f,float gamma,float maxValue);   
};

#include  "ToneMapping.cpp"
#endif