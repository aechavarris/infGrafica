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
#include "thread"

using namespace std;

int main(int argv,char* argc[]) {
    if(argv < 3){
        cout <<"El numero de argumentos no es valido"<<endl;
        exit(1);
    }

    int width = atoi(argc[1]);
    int height = atoi(argc[2]);
    int raysPerPixel=atoi(argc[3]);
    Vector n_techo = Vector(0.0, 1.0, 0.0);
    Vector n_suelo = Vector(0.0, -1.0, 0.0);
    Vector n_pIz = Vector(-1.0, 0.0, 0.0);
    Vector n_pDe = Vector(1.0, 0.0, 0.0);
    Vector n_fondo = Vector(0.0, 0.0, 1.0);

    RGB color_r = RGB(1.0, 0.0, 0.0);
    RGB color_g = RGB(0.0, 1.0,0.0);
    RGB color_b = RGB(0.0, 0.0, 1.0);
    RGB color_w = RGB(1.0, 1.0, 1.0);

    Plane techo = Plane(Point(0.0, 35, 0.0), n_techo, color_g);
    Plane suelo = Plane(Point(0.0, -35, 0.0), n_suelo, color_g);
    Plane pIz = Plane(Point(35, 0.0, 0.0), n_pIz, color_r);
    Plane pDe = Plane(Point(-35, 0.0, 0.0), n_pDe, color_r);
    Plane fondo = Plane(Point(0.0,0.0,1.0), n_fondo, color_w);

    Sphere esfera(Point(15,30.0,10.0), 4.5, RGB(0.0,1.0,1.0));
    Sphere esfera2(Point(-15.0,-15.0,20.0), 6.5, RGB(1.0,0.5,0.2));

    Point origin = Point(0, 0, 0);
    Vector f = Vector(0, 0, 1);
    Vector u = Vector(0, 1, 0);
    Vector r = Vector(1, 0, 0);

    Camera camera = Camera(origin, f, u, r); 

    RayTracing escena = RayTracing(camera,  raysPerPixel, width, height);
    escena.primitives.push_back(&techo);
    escena.primitives.push_back(&suelo);
    escena.primitives.push_back(&pIz);
    escena.primitives.push_back(&pDe);
    escena.primitives.push_back(&fondo);
    escena.primitives.push_back(&esfera);
    escena.primitives.push_back(&esfera2);
 
    escena.shootingRays();

    PPMFile file = PPMFile("Escena1", "");
    ToneMapping mapping;
    file.width = width;
    file.height = height;
    file.potentialColor = 255.0;
    file.HDR_RESOLUTION = 1.0;
    file.format="P3";
    file.RGBTuples = escena.projection; 
    file.writeFile("", "LDR"); 
    return 0;
}