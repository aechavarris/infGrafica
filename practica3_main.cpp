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
    int width = 2000;
    int height = 2000;
    
    Point origin = Point(-1600, 0, 0);
    Vector n_techo = Vector(0.0, 1.0, 0.0);
    Vector n_suelo = Vector(0.0, -1.0, 0.0);
    Vector n_pIz = Vector(0.0, 0.0, 1.0);
    Vector n_pDe = Vector(0.0, 0.0, -1.0);
    Vector n_fondo = Vector(-1.0, 0.0, 0.0);

    RGB color_r = RGB(1.0, 0.0, 0.0);
    RGB color_g = RGB(0.0, 1.0,0.0);
    RGB color_b = RGB(0.0, 0.0, 1.0);
    RGB color_w = RGB(1.0, 1.0, 1.0);

    Plane* techo =new Plane(Point(0.0, 20.0, 0.0), n_techo, color_w);
    Plane* suelo =new Plane(Point(0.0, -20.0, 0.0), n_suelo, color_w);
    Plane* pIz =new Plane(Point(0.0, 0.0, 15.0), n_pIz, color_r);
    Plane* pDe =new Plane(Point(0.0, 0.0, -15.0), n_pDe, color_g);
    Plane* fondo =new Plane(Point(-1550.0, 0.0, 0.0), n_fondo, color_w);

    Sphere* esfera = new Sphere(Point(-1560.0, 8.0, 9.0), 6.5, RGB(0.0, 1.0, 1.0));
    Sphere* esfera2 = new Sphere(Point(-1550.0, -8.0, -9.0), 6.5, RGB(1.0, 0.5, 0.2));

    Vector f = Vector(1500 - origin.x, 0 - origin.y, 0 - origin.z);
    Vector u = Vector(-1600 - origin.x, 0 - origin.y, height - origin.z) ;
    Vector r = Vector(-1600 - origin.x, width - origin.y, 0 - origin.z) ;

    Camera camera = Camera(origin, f, u, r); 

    RayTracing* escena = new RayTracing(camera,  5, width, height);
    escena->addPrimitive(techo);
    escena->addPrimitive(suelo);
    escena->addPrimitive(pIz);
    escena->addPrimitive(pDe);
    escena->addPrimitive(fondo);
    escena->addPrimitive(esfera);
    escena->addPrimitive(esfera2);
    escena->shootingRays();
    PPMFile file = PPMFile("Escena1", "");
    file.width = width;
    file.height = height;
    file.potentialColor = 1.0;
    file.HDR_RESOLUTION = 2.0;
    file.format="P3";
    file.RGBTuples = escena->projection;
    file.writeFile("", "LDR");
    return 0;
}