#pragma once

#include <iostream>
#include <math.h>
#include "ToneMapping.h"
#include "../../lib/hdr_files/HDRFile.h"

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
        void clamping(HDRFile &f);

        /*
         * Pre:
         * Post:
         */
        void equalization(HDRFile &f, float maxValue);

        /*
         * Pre:
         * Post:
         */
        void gammaCurve(HDRFile &f);
    
};

#include  "ToneMapping.cpp"
#endif