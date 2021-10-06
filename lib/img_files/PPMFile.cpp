#pragma once

#include "PPMFile.h"

PPMFile::PPMFile(string name,string path){
    this->name = name;
    this->path = path;
    this->HDR_RESOLUTION = 1.0;
};

void PPMFile::initializeVectorComponents() {
    this->RGBTuples.resize(this->height);
    for(int i = 0; i < this->height; i++){
        this->RGBTuples.at(i).resize(this->width);
    }
};

void PPMFile::readFile(){
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
                        getline(my_file, line);
                        this->format = line;
                        break;

                    // It takes the comments of the file
                    case 1:
                        while(my_file.peek() == '#') {
                            getline(my_file, line, '\n');
                            string aux = line.substr(0,5);
                            if(aux.compare("#MAX=") == 0){
                                line.erase(0, 5);
                                this->HDR_RESOLUTION = stof(line);
                            }
                        }
                        break;

                    // It takes the resolution of the file
                    case 2:
                        my_file >> w >>h;
                        getline(my_file, line, '\n');
                        this->width = w;
                        this->height = h;
                        this->initializeVectorComponents();
                        break;

                    // It takes the potential color of the file
                    case 3:
                        getline(my_file, line, '\n');
                        this->potentialColor = atoi((char*) line.c_str());
                        break;

                    // It takes the ordered RGB tuples of the file
                    case 4:
                        int r, g, b;
                        for (int n = 0; n < this->height; n++){
                            for (int m = 0; m < this->width; m++){
                                my_file >> r >> g >> b;
                                
                                // Loading from disk to memory
                                RGB actual = RGB(r * this->HDR_RESOLUTION / this->potentialColor, g * this->HDR_RESOLUTION / this->potentialColor, b * this->HDR_RESOLUTION / this->potentialColor);             
                                this->RGBTuples.at(n).at(m) = actual;    
                            }
                        }
                        break;
                }
        }
	}
	my_file.close();
};

float hdr_function(float v, float m){
    cout << v / m << endl;
    if (v / m < 1.0){
        return v / m;
    }
    else{
        return 1.0;
    }
}
   
void PPMFile::writeFile(string path, string format){
    ofstream my_file(path + this->name+".ppm");
    const float LDR_RESOLUTION = 255.0f;

    my_file << this->format << endl;
    my_file << "#MAX=" << this->HDR_RESOLUTION << endl;
    my_file << "# " << this->name << ".ppm" << endl;
    my_file << this->width << " " << this->height << endl;
    if (format == "LDR") {
        my_file << LDR_RESOLUTION << endl;
    }
    else {
        my_file << this->potentialColor << endl;
    }

    float final_r = 0.0;
    float final_g = 0.0;
    float final_b = 0.0;
    for (int i = 0; i < this->height; i++){
        for (int j = 0; j < this->width; j++){
            
            final_r = this->RGBTuples.at(i).at(j).r;
            final_g = this->RGBTuples.at(i).at(j).g;
            final_b = this->RGBTuples.at(i).at(j).b;
            
            if(format == "LDR"){
                final_r = final_r * LDR_RESOLUTION;
                final_g = final_g * LDR_RESOLUTION;
                final_b = final_b * LDR_RESOLUTION;

                my_file << int(final_r) << "  ";
                my_file << int(final_g) << "  ";
                my_file << int(final_b) << "      ";
            }
            else {
                final_r = hdr_function(final_r, this->HDR_RESOLUTION);
                final_g = hdr_function(final_g, this->HDR_RESOLUTION);
                final_b = hdr_function(final_b, this->HDR_RESOLUTION);

                my_file << final_r * this->potentialColor << "  ";
                my_file << final_g * this->potentialColor  << "  ";
                my_file << final_b * this->potentialColor << "      ";
            }
        }
        my_file << '\n';
    }

	my_file.close();
};