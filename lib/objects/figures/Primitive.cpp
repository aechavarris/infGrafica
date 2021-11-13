#pragma once

#include "Primitive.h"

Primitive::Primitive(){};

bool Primitive::intersect(Ray ray, float *t, RGB *color) { return 0; };

string Primitive::russianRoulette(int rebotes)
{
    float lambertianDiffuse = this->matProperties.lambertianDiffuse;
    float deltaBRDF = this->matProperties.deltaBRDF;
    float deltaBTDF = this->matProperties.deltaBTDF;

    float sum = lambertianDiffuse + deltaBRDF + deltaBTDF;
    //cout<<"Rusian sumatorio: "<<sum<<endl;
    if (sum > 0.9f)
    { // Si el sumatorio es mayor que 0.9
        lambertianDiffuse = lambertianDiffuse * (0.9f / sum);
        deltaBRDF = deltaBRDF * (0.9f / sum);
        deltaBTDF = deltaBTDF * (0.9f / sum);
    }
    
    float randomNumber = floatRand(0.0f, 1.0f); // Genera un número entre 0.0 y 1.0
    

    if(rebotes >= 5){
        randomNumber = randomNumber - lambertianDiffuse;
    }else{
        randomNumber = -lambertianDiffuse;
    }   
    if (randomNumber < 0.0) return "difusion";
    if(rebotes >= 5){
        randomNumber = randomNumber - deltaBRDF;
    }else{
        randomNumber = -deltaBRDF;
    }
    
    if (randomNumber < 0.0) return "especular";
    if(rebotes >= 5){
        randomNumber = randomNumber - deltaBTDF;
    }else{
        randomNumber = -deltaBTDF;
    }
    
    if (randomNumber < 0.0) return "refraccion";

    return "fin";
}

Vector Primitive::difusion(Ray ray, float distancia, Point p)
{
    float randomNumber = floatRand(0.0f,1.0f);  // Genera un número entre 0.0 y 1.0
    float randomNumber2 = floatRand(0.0f,1.0f); // Genera un número entre 0.0 y 1.0

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

    //cout <<"Rayo direccion: "<< ray.direction.x<<" "<<ray.direction.y<<" "<<ray.direction.z<<endl;
    //cout <<"Normal: "<< z.x<<" "<<z.y<<" "<<z.z<<endl;
    Matrix baseChange = Matrix(x, y, z, p);
    
    dirRebote = baseChange.productMatrixVector(dirRebote);
    //cout <<"Rayo rebote: "<< dirRebote.x<<" "<<dirRebote.y<<" "<<dirRebote.z<<endl;
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
    //cout <<"Normal: "<< normal.x<<" "<<normal.y<<" "<<normal.z<<endl;
    //cout <<"Ray * normal: "<< dotRayNormal<<endl;
    //cout << "Dir rebote: "<< dirRebote.x<<" "<<dirRebote.y<<" "<<dirRebote.z<<endl;
    return dirRebote;
}

float Primitive::floatRand(const float & min, const float & max) {
    static thread_local mt19937 generator;
    uniform_real_distribution<float> distribution(min,max);
    return distribution(generator);
}