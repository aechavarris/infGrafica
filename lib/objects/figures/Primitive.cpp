#pragma once

#include "Primitive.h"

Primitive::Primitive(){};

bool Primitive::intersect(Ray ray, float *t,float* t2, Point backgroundLeft, Point frontRight) { return 0; };

string Primitive::russianRoulette(int rebotes,float* random) {
    //if(rebotes>1){return "fin";}
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
        return "especular";
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
    
    Vector z = this->getNormal(ray, distancia);
    
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
    return dirRebote.normalize();
}

Ray Primitive::refraccion(Ray ray, float distancia,Matrix change_base, Point backgroundLeft, Point frontRight)
{
    const float ext_refraction = 1.0003;
    const float int_refraction = this->matProperties.snell;
    Vector z = this->getNormal(ray, distancia);
    
    //cout<<"Normal: "<<z.x<<" "<<z.y<<" "<<z.z<<endl;
    Vector normal = this->getNormal(ray, distancia);
    float cos1 = -ray.direction.dot(normal);
    float sin1 = 1.0 - cos1 * cos1;
    float coef = 1.0 - (ext_refraction / int_refraction) * (ext_refraction / int_refraction) * sin1;
    Point p = Point(ray.origin.x + ray.direction.x * distancia,
                    ray.origin.y + ray.direction.y * distancia,
                    ray.origin.z + ray.direction.z * distancia);
    Vector internal_direction=Vector();
    if (coef < 0.0){
        internal_direction = ray.direction;
    }else{
        internal_direction = ray.direction * (ext_refraction / int_refraction)
                             + normal * (ext_refraction / int_refraction * cos1 - sqrt(coef));
    }
    //First vector from outside to inside primitive
    
    
    Ray internal_ray=Ray(p,internal_direction);

    float* t1 = new float;
    float* t2 = new float;
    this->intersect(internal_ray, t1, t2, backgroundLeft, frontRight);

    p = Point(internal_ray.origin.x + internal_ray.direction.x * *t2,
                    internal_ray.origin.y + internal_ray.direction.y * *t2,
                    internal_ray.origin.z + internal_ray.direction.z * *t2);

    z = this->getNormal(internal_ray, *t2);
    
    //cout<<"Normal: "<<z.x<<" "<<z.y<<" "<<z.z<<endl;
    normal.x = -z.x;
    normal.y = -z.y;
    normal.z = -z.z;
    delete t1;
    delete t2;

    cos1 = -internal_ray.direction.dot(normal);
    sin1 = 1 - cos1 * cos1;
    coef = 1.0 - (ext_refraction / int_refraction) * (ext_refraction / int_refraction) * sin1;
    
    if (coef < 0.0){
        
        return  Ray(p,normal.cross(internal_ray.direction));
    }
    else{
        Vector tmp = internal_ray.direction * (int_refraction / ext_refraction)
                             + normal * (int_refraction / ext_refraction * cos1 - sqrt(coef));
        return Ray(p,tmp);
    }
    //Final direction result
}

Vector Primitive::especular(Ray ray, float distancia,Matrix change_base)
{
    Vector normal = this->getNormal(ray, distancia);
    float dotRayNormal = ray.direction.dot(normal);
    Vector aux = (normal * dotRayNormal * 2.0f);

    Vector dirRebote = (ray.direction - aux).normalize();

    //cout <<"Normal: "<< normal.x<<" "<<normal.y<<" "<<normal.z<<endl;
    //cout <<"Ray * normal: "<< dotRayNormal<<endl;
    //cout << "Dir rebote: "<< dirRebote.x<<" "<<dirRebote.y<<" "<<dirRebote.z<<endl;
    return dirRebote;
}
//This funtion has been taken from here: https://stackoverflow.com/questions/21237905/how-do-i-generate-thread-safe-uniform-random-numbers
float Primitive::floatRand(const float & min, const float & max) {
    static thread_local mt19937 generator;
    uniform_real_distribution<float> distribution(min,max);
    return distribution(generator);
}