#include <iostream>
#include "lib/hdr_files/HDRFile.h"
using namespace std;

int main(int argv,char* argc[]) {
    if(argv<2){
        cout <<"El numero de argumentos no es valido"<<endl;
        exit(1);
    }
    HDRFile file=HDRFile("prueba1",argc[1]);
    file.readFile();
    cout << file.path << endl;
    cout << file.name << endl;
    cout << file.format << endl;
    cout << file.comments << endl;
    cout << file.width << endl;
    cout << file.height << endl;
    cout << file.potentialColor << endl;  

    for (int i = 0; i < 1; i++){
        for (int j = 0; j < 5; j++){
            cout << file.RGBTuples.at(i*file.height+j).r << "  ";
            cout << file.RGBTuples.at(i*file.height+j).g << "  ";
            cout << file.RGBTuples.at(i*file.height+j).b << endl;
        }
    }
    return 0;
}