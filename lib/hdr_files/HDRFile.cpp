#pragma once

#include "HDRFile.h"

HDRFile::HDRFile(){};

void HDRFile::readFile(){
    fstream my_file;
	my_file.open(this->path, ios::in);
	if (!my_file) {
		cout << "No such file";
	}
	else {
		string line;
        for (int i = 0; i < 5; i++ ){
            while (!my_file.eof()) {
                getline(my_file,line);
                switch (i)
                {
                    // It takes the format of the file
                    case 0:
                        this->format = line;
                        break;

                    // It takes the comments of the file
                    case 1:
                        this->comments = line;
                        break;

                    // It takes the resolution of the file
                    case 2:
                        char* pch = strtok ((char*) line.c_str(), " ");
                        while (pch != NULL) 
                        {
                            printf ("%s\n", pch);
                            this->width = atoi(pch);
                            pch = strtok (NULL, " ");
                        }
                        break;

                    // It takes the potential color of the file
                    case 3:
                        this->potentialColor = atoi((char*) line.c_str());
                        break;

                    // It takes the ordered RGB tuples of the file
                    case 4:
                        int r, g, b;
                        for (int n = 0; n < this->height; n++){
                            
                            for (int m = 0; m < this->width; m++){
                                for (int c = 0; c < 3; c++){
                                    char* pch = strtok ((char*) line.c_str(), " ");
                                    while (pch != NULL) 
                                    {
                                        printf ("%s\n", pch);
                                        switch (c)
                                        {
                                        case 0:
                                            r = atoi(pch);
                                            break;
                                        
                                        case 1:
                                            g = atoi(pch);
                                            break;
                                        case 2:
                                            b = atoi(pch);
                                            break;
                                        }
                                        pch = strtok (NULL, " ");
                                    }
                                }
                                RGB actual = RGB(r, g, b);
                                this->RGBTuples[n][m] = actual;
                            }
                        }
                        break;
                }
            }
        }
	}
	my_file.close();
};
   
void HDRFile::writeFile(){

};