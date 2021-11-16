#pragma once

#include "Primitive.h"

Primitive::Primitive(){};

bool Primitive::intersect(Ray ray, float *t) { return 0; };

string Primitive::russianRoulette(int rebotes,float* random) {

    float lambertianDiffuse = this->matProperties.lambertianDiffuse;
    float deltaBRDF = this->matProperties.deltaBRDF;
    float deltaBTDF = this->matProperties.deltaBTDF;

    float sum = lambertianDiffuse + deltaBRDF + deltaBTDF;
    float probFin = 0.9f; 
    if(sum > probFin){
        lambertianDiffuse = lambertianDiffuse * probFin / sum;
        deltaBRDF = deltaBRDF * probFin / sum;
        deltaBTDF = deltaBTDF * probFin / sum;
    }

    float random_p = floatRand(0.0f, 1.0f); //generate an uniform distribution random number from 0 to 1

    random_p = random_p - lambertianDiffuse;
    *random = 1 + random_p;
    if(random_p < 0){
        return "difusion";
    }
    *random = 1 + random_p;
    random_p = random_p - deltaBRDF;
    if(random_p < 0){
        return "specular";
    }
    *random = 1 + random_p;
    random_p = random_p - deltaBTDF;
    if(random_p < 0 ){
        return "refraccion";
    }

    return "fin";
}

Vector Primitive::difusion(Ray ray, float distancia, Point p,Matrix change_base)
{
    float randomNumber = floatRand(0.0f,1.0f);  // Genera un número entre 0.0 y 1.0
    float randomNumber2 = floatRand(0.0f,1.0f); // Genera un número entre 0.0 y 1.0

    float inclination = acos(sqrt(randomNumber));
    float azimuth = randomNumber2 * PI * 2.0f; 

    Vector dirRebote = Vector(sin(inclination) * cos(azimuth), sin(inclination) * sin(azimuth), cos(inclination));
    
    Vector z = this->getNormal(ray, distancia,change_base);
    
    //cout<<"Normal: "<<z.x<<" "<<z.y<<" "<<z.z<<endl;
    Vector y = z.cross(Vector(z.z,z.x,z.y)).normalize();//ray.direction);
    Vector x = z.cross(y).normalize();

    //cout <<"Rayo direccion: "<< ray.direction.x<<" "<<ray.direction.y<<" "<<ray.direction.z<<endl;
    //cout <<"Normal: "<< z.x<<" "<<z.y<<" "<<z.z<<endl;
    Matrix baseChange = Matrix(x, y, z, p);
    
    dirRebote = baseChange.productMatrixVector(dirRebote);
    //cout <<"Rayo rebote: "<< dirRebote.x<<" "<<dirRebote.y<<" "<<dirRebote.z<<endl;
    float tmp = dirRebote.dot(z);
    //cout << tmp << " "<< inclination << endl;
    return Vector(dirRebote.x / dirRebote.module(), dirRebote.y / dirRebote.module(), dirRebote.z / dirRebote.module());
}

Vector Primitive::refraccion(Ray ray, float distancia, Point o,Matrix change_base)
{
    return Vector();
}

Vector Primitive::especular(Ray ray, float distancia,Matrix change_base)
{
    Vector normal = this->getNormal(ray, distancia,change_base);
    float dotRayNormal = ray.direction.dot(normal);
    Vector aux = (normal * dotRayNormal * 2.0f);

    Vector dirRebote = (ray.direction - aux).normalize();

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