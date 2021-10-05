#pragma once

#include "HDRFile.h"

HDRFile::HDRFile(string name,string path){
    this->name = name;
    this->path = path;
};

void HDRFile::readFile(){
    fstream my_file;
	my_file.open(this->path, ios::in);
	if (!my_file) {
		cout << "No such file";
	}
	else {
		string line;
        string tmp;
        int w,h;
        for (int i = 0; i < 5; i++ ){
                switch (i)
                {
                    // It takes the format of the file
                    case 0:
                        getline(my_file,line);
                        this->format = line;
                        break;

                    // It takes the comments of the file
                    case 1:
                        
                        getline(my_file,line,'\n');
                        this->comments=line;
                        getline(my_file,line,'\n');
                        break;

                    // It takes the resolution of the file
                    case 2:
                        my_file >> w >>h;
                        getline(my_file,line,'\n');
                        this->width=w;
                        this->height=h;
                        break;
                    // It takes the potential color of the file
                    case 3:
                        getline(my_file,line,'\n');
                        this->potentialColor = atoi((char*) line.c_str());
                        break;

                    // It takes the ordered RGB tuples of the file
                    case 4:
                        int r, g, b;
                        for (int n = 0; n < this->height; n++){
                            for (int m = 0; m < this->width; m++){
                                
                                my_file >> r >> g >> b;
                                
                                RGB actual = RGB(r, g, b);
                                
                                this->RGBTuples.push_back(actual);
                            }
                        }
                        break;
                }
        }
	}
	my_file.close();
};
   
void HDRFile::writeFile(){

};