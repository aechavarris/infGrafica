#include <iostream>
#include <string.h>
#include "lib/img_files/PPMFile.h"
using namespace std;

string getName(char path[]){

    char * pch;
    char * name;
    pch = strtok (path,"/");
    while (pch != NULL)
    {
        name=pch;
        pch = strtok (NULL, "/");
    }
    string name_s(name);
    return name_s.erase(name_s.length()-4,4);
}
int main(int argv,char* argc[]) {
    if(argv < 3){
        cout <<"El numero de argumentos no es valido"<<endl;
        exit(1);
    }
    string path=argc[1];
    string name=getName(argc[1]);
    PPMFile file = PPMFile(name,path);
    file.readFile();
    string newPath;
    file.writeFile(newPath,argc[2]);
    return 0;
}