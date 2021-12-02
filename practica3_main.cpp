#include <iostream>
#include <string.h>
#include "lib/img_files/PPMFile.h"
#include "lib/tone_mapping/ToneMapping.h"
#include "lib/ray_tracing/RayTracing.h"
#include "lib/ray_tracing/cameraModel/Camera.h"
#include "lib/geometry/vector/Vector.h"
#include "lib/objects/figures/Primitive.h"
#include "lib/objects/figures/plane/Plane.h"
#include "lib/objects/figures/sphere/Sphere.h"


using namespace std;

int main(int argv,char* argc[]) {
    
    vector<PPMFile*> textures=vector<PPMFile*>();
    if(argv < 3){
        cout <<"El numero de argumentos no es valido"<<endl;
        exit(1);
    }if(argv >4){ 
        for(int i = 4; i < argv;i++){

            string t = string(argc[i]);
            PPMFile* texture= new PPMFile(t + ".ppm","lib/textures/" + t + ".ppm");
            if(!texture->readFile()){
                cout <<": El archivo de textura no ha sido encontrado"<<endl;
                exit(2);
            }
            textures.push_back(texture);
            cout <<"Textura cargada: "<<texture->name<<endl;
            cout<< "Tamaño: "<< texture->width <<" x "<<texture->height <<endl;
        }
    }
    int width = atoi(argc[1]);
    int height = atoi(argc[2]);
    int raysPerPixel = atoi(argc[3]);
    Vector n_techo = Vector(0.0, 1.0, 0.0);
    Vector n_suelo = Vector(0.0, -1.0, 0.0);
    Vector n_pDe = Vector(-1.0, 0.0, 0.0);
    Vector n_pIz = Vector(1.0, 0.0, 0.0);
    Vector n_fondo = Vector(0.0, 0.0, 1.0);
    Vector n_fondo_camara = Vector(0.0, 0.0, -1.0);

    RGB color_gris =  RGB(0.5, 0.5, 0.5);
    RGB color_r = RGB(1.0, 0.0,0.0);
    RGB color_g = RGB(0.0, 1.0,0.0);
    RGB color_a = RGB(1.0, 1.0,0.0);
    RGB color_b = RGB(0.0, 0.0, 1.0);
    RGB color_w = RGB(1.0, 1.0, 1.0);
    RGB color_n = RGB(0.0, 0.0, 0.0);
    RGB color_pared_xokas = RGB(35.7/255.0, 30.6/255.0, 30.2/255.0);
    
    Property aux=Property(1.0,0.0,0.0,0.0);
    Property aux2=Property(0.0,1.0,0.0,0.0);
    Property aux3=Property(0.0,0.0,1.0,1.5);

    Property plastico=Property(0.25,0.5,0.0,1.0);
    Property dielectrico=Property(0.0,0.25,0.5,1.0);
    Property difuso=Property(0.5,0.0,0.25,1.0);

    Plane techo = Plane(Point(0.0, -20, 0.0), n_techo, color_w,color_w,color_w,aux,false);
    Plane suelo = Plane(Point(0.0, 20, 0.0), n_suelo, color_gris,color_gris,color_gris,aux,false);
    Plane pIz = Plane(Point(-20, 0.0, 0.0), n_pDe, color_r,color_r,color_r,aux,false);
    Plane pDe = Plane(Point(20, 0.0, 0.0), n_pIz, color_g,color_g,color_g,aux,false);
    Plane fondo = Plane(Point(0.0,0.0,-100.0), n_fondo, color_gris,color_gris,color_gris,aux,false);
    Plane fondoCamara = Plane(Point(0.0,0.0,10.0), n_fondo_camara, color_n,color_n,color_n,aux,false);
    Sphere esfera(Point(10,13,-70.0), 6.5, color_w,color_w,color_w,aux3,false);
    Sphere esfera2(Point(-10,13,-80.0), 6.5, color_w,color_w,color_w,aux2,false);

    for(int i = 0; i<textures.size();i++){
        switch(i){
            case 0:
                fondo = 
                    Plane(Point(0.0,0.0,-100.0), n_fondo, color_gris,color_gris,
                                color_gris,aux,false,textures.at(i));
                break;
            case 1:
                suelo = 
                    Plane(Point(0.0, 20, 0.0), n_suelo, color_gris,color_gris,
                                color_gris,aux,false,textures.at(i));
                break;
            case 2:
                pIz = 
                    Plane(Point(-20, 0.0, 0.0), n_pDe, color_pared_xokas,
                                color_pared_xokas,color_pared_xokas,aux,false,textures.at(i));
                break;
            case 3:
                pDe = 
                    Plane(Point(20, 0.0, 0.0), n_pIz, color_pared_xokas,
                                color_pared_xokas,color_pared_xokas,aux,false,textures.at(i));
                break;
            case 4:
                techo = 
                    Plane(Point(0.0, -20, 0.0), n_techo, color_w,
                                color_w,color_w,aux,false,textures.at(i));
                break;
            case 5:
                fondoCamara =
                    Plane(Point(0.0,0.0,10.0), n_fondo_camara, color_n,
                                color_n,color_n,aux,false,textures.at(i));
                break;
            case 6:
                esfera = Sphere(Point(10,13,-70.0), 6.5, color_w,
                                            color_w,color_w,aux,false,textures.at(i));
                break;
            case 7:
                esfera2= Sphere(Point(-10,13,-80.0), 6.5, color_w,
                                            color_w,color_w,aux2,false,textures.at(i));
                break;
        }
    }
    
    

    Point origin = Point(0, 0, 0);
    Vector f = Vector(0, 0, 1.5);
    Vector u = Vector(0, 1, 0);
    Vector r = Vector(1, 0, 0);

    Camera camera = Camera(origin, f, u, r); 
    //Creacion escena 1
    int i[1] ={150}; 
    // //int i[7] ={1,1,1,1,1,1,1}; 
    // //for (int n = 0; n < 7; n++) {

    //cout << "Escena 1 " << i[n]<<" rayos"<<endl;
    RayTracing escena1 = RayTracing(camera,  raysPerPixel, width, height);
    escena1.backgroundLeft = Point(-20,-20,-100);
    escena1.frontRight = Point(20,20,0.0);
    escena1.primitives.push_back(&techo);
    escena1.primitives.push_back(&suelo);
    escena1.primitives.push_back(&pIz);
    escena1.primitives.push_back(&pDe);
    escena1.primitives.push_back(&fondo);
    escena1.primitives.push_back(&esfera);
    escena1.primitives.push_back(&esfera2);
    escena1.primitives.push_back(&fondoCamara);
    
    Light luz(Point(0,-12,-90.0), color_w);
    escena1.lights.push_back(&luz);
    
    escena1.shootingRays();

    PPMFile file = PPMFile("Escena1_"+to_string(raysPerPixel), "");
    ToneMapping mapping;
    file.width = width;
    file.height = height;
    file.potentialColor = 255.0;
    file.HDR_RESOLUTION = 1.0;
    file.format="P3";
    file.RGBTuples = escena1.projection; 
    file.writeFile("", "HDR"); 
    // //}
    //Creacion escena 2
    // techo = Plane(Point(0.0, -20, 0.0), n_techo, color_w,color_w,color_w,aux,false,false);
    // for (int n = 0; n < 7; n++) {
    //     cout << "Escena 2 " << i[n]<<" rayos"<<endl;
    //     RayTracing escena2 = RayTracing(camera,  i[n], width, height);
    //     escena2.backgroundLeft = Point(-20,-20,-100);
    //     escena2.frontRight = Point(20,20,0.0);
    //     escena2.texture = texture;
    //     escena2.primitives.push_back(&techo);
    //     escena2.primitives.push_back(&suelo);
    //     escena2.primitives.push_back(&pIz);
    //     escena2.primitives.push_back(&pDe);
    //     escena2.primitives.push_back(&fondo);
    //     escena2.primitives.push_back(&esfera);
    //     escena2.primitives.push_back(&esfera2);
    //     escena2.primitives.push_back(&fondoCamara);
        
    //     Light luz(Point(0,-12,-70.0), color_w);
    //     escena2.lights.push_back(&luz);

    //     escena2.shootingRays();

    //     PPMFile file = PPMFile("Escena2_"+to_string(i[n]), "");
    //     ToneMapping mapping;
    //     file.width = width;
    //     file.height = height;
    //     file.potentialColor = 255.0;
    //     file.HDR_RESOLUTION = 1.0;
    //     file.format="P3";
    //     file.RGBTuples = escena2.projection; 
    //     file.writeFile("", "HDR"); 
    // }
    return 0;
}