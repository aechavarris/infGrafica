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
    string newPath;
    file.writeFile(newPath);
    return 0;
}