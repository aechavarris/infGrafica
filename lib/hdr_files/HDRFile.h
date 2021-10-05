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

class HDRFile{

    public:
        string name;
        string path;
        string format;
        string comments;
        int width, height;
        int potentialColor;
        vector<RGB> RGBTuples;

        /*
         * Constructores de la clase HDRFile
         */
        HDRFile();
        HDRFile(string name, string path);


        // ---------------------------------------
        // ------------- OPERACIONES -------------
        // ---------------------------------------

        /*
         * Pre:
         * Post:
         */
        void readFile();

        /*
         * Pre:
         * Post:
         */
        void writeFile(string path);
    
};

#include  "HDRFile.cpp"
#endif