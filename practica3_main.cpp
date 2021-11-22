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
    if(argv < 3){
        cout <<"El numero de argumentos no es valido"<<endl;
        exit(1);
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

    RGB color_gris = RGB(0.5, 0.5, 0.5);
    RGB color_r = RGB(1.0, 0.0,0.0);
    RGB color_g = RGB(0.0, 1.0,0.0);
    RGB color_a = RGB(1.0, 1.0,0.0);
    RGB color_b = RGB(0.0, 0.0, 1.0);
    RGB color_w = RGB(1.0, 1.0, 1.0);
    RGB color_n = RGB(0.0, 0.0, 0.0);
    
    Property aux=Property(1.0,0.0,0.0,0.0);
    Property aux2=Property(0.0,1.0,0.0,0.0);
    Property aux3=Property(0.0,0.0,1.0,1.5);

    Property plastico=Property(0.25,0.5,0.0,1.0);
    Property dielectrico=Property(0.0,0.25,0.5,1.0);
    Property difuso=Property(0.5,0.0,0.25,1.0);

    Plane techo = Plane(Point(0.0, -20, 0.0), n_techo, color_w,color_w,color_w,aux,true);
    Plane suelo = Plane(Point(0.0, 20, 0.0), n_suelo, color_gris,color_gris,color_gris,aux,false);
    Plane pIz = Plane(Point(-20, 0.0, 0.0), n_pDe, color_r,color_r,color_r,aux,false);
    Plane pDe = Plane(Point(20, 0.0, 0.0), n_pIz, color_g,color_g,color_g,aux,false);
    Plane fondo = Plane(Point(0.0,0.0,-100.0), n_fondo, color_gris,color_gris,color_gris,aux,false);
    Plane fondoCamara = Plane(Point(0.0,0.0,10.0), n_fondo_camara, color_n,color_n,color_n,aux,false);
    Sphere esfera(Point(10,13,-70.0), 6.5, color_w,color_w,color_w,aux3,false);
    Sphere esfera2(Point(-10,13,-80.0), 6.5, color_w,color_w,color_w,aux2,false);
    

    Point origin = Point(0, 0, 0);
    Vector f = Vector(0, 0, 1.5);
    Vector u = Vector(0, 1, 0);
    Vector r = Vector(1, 0, 0);

    Camera camera = Camera(origin, f, u, r); 

    RayTracing escena = RayTracing(camera,  raysPerPixel, width, height);
    escena.backgroundLeft = Point(-20,-20,-100);
    escena.frontRight = Point(20,20,0.0);
    escena.primitives.push_back(&techo);
    escena.primitives.push_back(&suelo);
    escena.primitives.push_back(&pIz);
    escena.primitives.push_back(&pDe);
    escena.primitives.push_back(&fondo);
    escena.primitives.push_back(&esfera);
    escena.primitives.push_back(&esfera2);
    escena.primitives.push_back(&fondoCamara);
    
    Light luz(Point(0,-12,-90.0), color_w);
    escena.lights.push_back(&luz);

    escena.shootingRays();

    PPMFile file = PPMFile("Escena2", "");
    ToneMapping mapping;
    file.width = width;
    file.height = height;
    file.potentialColor = 255.0;
    file.HDR_RESOLUTION = 1.0;
    file.format="P3";
    file.RGBTuples = escena.projection; 
    file.writeFile("", "HDR"); 
    return 0;
}