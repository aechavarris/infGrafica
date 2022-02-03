/*****************************************************************
 * File:    PPMFile.h
 * Authors: Marcos Nuez Martinez & Álvaro Echavarri Sola
 * Coms:    Implementa la lectura y escritura de ficheros .ppm 
 *          (en LDR y HDR)
 *****************************************************************/

#pragma once

#include <iostream>
#include <ostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>
#include "../../lib/rgb/RGB.h"
using namespace std;

#ifndef _HDR_FILE
#define _HDR_FILE

class PPMFile{

    public:
        string name;
        string path;
        string format;
        int width, height;
        int potentialColor;
        float HDR_RESOLUTION;
        vector<vector<RGB> > RGBTuples;

        /*
         * Constructores de la clase PPMFile
         */
        PPMFile();
        PPMFile(string name, string path);


        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        /*
         * Pre:
         * Post:
         */
        bool readFile();

        /*
         * Pre:
         * Post:
         */
        void writeFile(string path,string format);

    private:

        /*
         * Pre:
         * Post:
         */
        void initializeVectorComponents();
};

#include  "PPMFile.cpp"
#endif