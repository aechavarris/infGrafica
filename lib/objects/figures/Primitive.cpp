#pragma once

#include "Primitive.h"

Primitive::Primitive(){};

bool Primitive::intersect(Ray ray, float *t, RGB *color) { return 0; };

string Primitive::russianRoulette()
{
    float lambertianDiffuse = this->matProperties.lambertianDiffuse;
    float deltaBRDF = this->matProperties.deltaBRDF;
    float deltaBTDF = this->matProperties.deltaBTDF;

    float sum = lambertianDiffuse + deltaBRDF + deltaBTDF;
    //cout<<"Rusian sumatorio: "<<sum<<endl;
    if (sum > 0.9f)
    { // Si el sumatorio es mayor que la probabilidad de matar el rayo
        lambertianDiffuse = 0.9f / sum;
        deltaBRDF = 0.9f / sum;
        deltaBTDF = 0.9f / sum;
    }
    
    float randomNumber = floatRand(0.0f,1.0f); // Genera un número entre 0.0 y 1.0
    //cout<<"Rusian random: "<<randomNumber<<endl;
    randomNumber = randomNumber - lambertianDiffuse;
    if (randomNumber < 0.0) return "difusion";

    randomNumber = randomNumber - deltaBRDF;
    if (randomNumber < 0.0) return "especular";

    randomNumber = randomNumber - deltaBTDF;
    if (randomNumber < 0.0) return "refraccion";

    return "fin";
}

Vector Primitive::difusion(Ray ray, float distancia, Point p)
{
    float randomNumber = static_cast<float>(rand());  // Genera un número entre 0.0 y 1.0
    float randomNumber2 = static_cast<float>(rand()); // Genera un número entre 0.0 y 1.0

    float inclination = acos(sqrt(randomNumber));
    float azimuth = randomNumber2 * PI * 2.0f; 
    Vector dirRebote = Vector(sin(inclination) * cos(azimuth), sin(inclination) * sin(azimuth), cos(inclination));

    Vector z = this->getNormal(ray, distancia);
    Vector y = z.cross(ray.direction);
    y.x = y.x / y.module();
    y.y = y.y / y.module();
    y.z = y.z / y.module();
    Vector x = z.cross(y);
    x.x = x.x / x.module();
    x.y = x.y / x.module();
    x.z = x.z / x.module();

    Matrix baseChange = Matrix(x, y, z, p);
    dirRebote = baseChange.productMatrixVector(dirRebote);

    return Vector(dirRebote.x / dirRebote.module(), dirRebote.y / dirRebote.module(), dirRebote.z / dirRebote.module());
}

Vector Primitive::refraccion(Ray ray, float distancia, Point o)
{
    return Vector();
}

Vector Primitive::especular(Ray ray, float distancia)
{
    Vector normal = this->getNormal(ray, distancia);
    float dotRayNormal = ray.direction.dot(normal);
    Vector aux = Vector(normal.x * dotRayNormal * 2.0f, normal.y * dotRayNormal * 2.0f, normal.z * dotRayNormal * 2.0f);

    Vector dirRebote = Vector(ray.direction.x - aux.x, ray.direction.y - aux.y, ray.direction.z - aux.z);
    dirRebote.x = dirRebote.x / dirRebote.module();
    dirRebote.y = dirRebote.y / dirRebote.module();
    dirRebote.y = dirRebote.z / dirRebote.module();
    
    return dirRebote;
}

float Primitive::floatRand(const float & min, const float & max) {
    static thread_local mt19937 generator;
    uniform_real_distribution<float> distribution(min,max);
    return distribution(generator);
}