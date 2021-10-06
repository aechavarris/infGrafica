#include <iostream>
#include "lib/img_files/PPMFile.h"
using namespace std;

int main(int argv,char* argc[]) {
    if(argv < 3){
        cout <<"El numero de argumentos no es valido"<<endl;
        exit(1);
    }
    PPMFile file = PPMFile("prueba1",argc[1]);
    file.readFile();
    string newPath;
    file.writeFile(newPath,argc[2]);
    return 0;
}