#pragma once

#include "Primitive.h"

Primitive::Primitive(){};

bool Primitive::intersect(Ray ray, float* t, RGB* color){return 0;};

string Primitive::russianRoulette() {
    srand(time(0));
    float lambertianDiffuse = this->matProperties.lambertianDiffuse;
    float deltaBRDF = this->matProperties.deltaBRDF;
    float deltaBTDF = this->matProperties.deltaBTDF;

    float sum = lambertianDiffuse + deltaBRDF + deltaBTDF;

    if (sum > 0.9f) { // Si el sumatorio es mayor que la probabilidad de matar el rayo
        lambertianDiffuse = 0.9f / sum;
        deltaBRDF = 0.9f / sum;
        deltaBTDF = 0.9f / sum;
    }

    float randomNumber = static_cast <float> (rand()); // Genera un número entre 0.0 y 1.0

    randomNumber = randomNumber - lambertianDiffuse;
    if ( randomNumber < 0.0 ) {
        return "difusion";
    }

    randomNumber = randomNumber - deltaBRDF;
    if ( randomNumber < 0.0 ) {
        return "especular";
    }

    randomNumber = randomNumber - deltaBTDF;
    if ( randomNumber < 0.0 ) {
        return "refraccion";
    }

    return "fin";
}

Vector Primitive::difusion(Ray ray,float distancia, Point* o) {
    float randomNumber = static_cast <float> (rand()); // Genera un número entre 0.0 y 1.0
    float randomNumber2 = static_cast <float> (rand()); // Genera un número entre 0.0 y 1.0

    float inclination = acos(sqrt(randomNumber));
    float azimuth = randomNumber2 * M_PI * 2.0f; 
    Vector dirRebote = Vector(sin(inclination)*cos(azimuth), sin(inclination)*sin(azimuth), cos(inclination));

    Vector z = this->getNormal(ray, distancia);
    Vector y = z.cross(ray.direction);
    y.x = y.x / y.module();
    y.y = y.y / y.module();
    y.z = y.z / y.module();
    Vector x = z.cross(y);
    x.x = x.x / x.module();
    x.y = x.y / x.module();
    x.z = x.z / x.module();
    Point p = Point(ray.origin.x + ray.direction.x * distancia,
                    ray.origin.y + ray.direction.y * distancia,
                    ray.origin.z + ray.direction.z * distancia);
    o->x = p.x;
    o->x = p.y;
    o->x = p.z;

    Matrix baseChange = Matrix(x, y, z, p);
    dirRebote = baseChange.productMatrixVector(dirRebote);
    
    return Vector(dirRebote.x / dirRebote.module(), dirRebote.y / dirRebote.module(), dirRebote.z / dirRebote.module());
}