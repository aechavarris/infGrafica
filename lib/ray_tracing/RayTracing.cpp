#pragma once

#include "RayTracing.h"

RayTracing::RayTracing(){};

RayTracing::RayTracing (Camera camera, int numRaysPerPixel, int width, int height) {
    this->camera = camera;
    this->numRaysPerPixel = numRaysPerPixel;
    this->width = width;
    this->height = height;
    this->baseChange = Matrix(camera.u, camera.i, camera.f, camera.origin);
    this->projection.resize(height);
    for(int i = 0; i < height; i++){
        this->projection[i].resize(width);
    }
};

void RayTracing::shootingRays() {
    Point origen = this->camera.origin;
    RGB color = RGB(0.0, 0.0, 0.0);
    Primitive* masCercano;
    RGB* colorPrimitive = new RGB(0.0,0.0,0.0);
    RGB countColor = RGB(0.0,0.0,0.0);

    float pixelXSide = (float)2 / this->height;
    float pixelYSide = (float)2 / this->width;

    srand(time(0));
    
    cout <<"Starting ray tracing..."<<endl;
    
    int total=width*height*numRaysPerPixel;
    int progress=0;
    for (float i = 0; i < this->height; i++){

        for (float j = 0; j < this->width; j++) {

            color.r = 0.0;
            color.g = 0.0;
            color.b = 0.0;
            countColor.r = 0.0;
            countColor.g = 0.0;
            countColor.b = 0.0;

            float x = i * pixelXSide - 1.0; 
            float y = j * pixelYSide - 1.0;
            
            float minDist = numeric_limits<float>::max();
            for (int n = 0; n < this->numRaysPerPixel; n++) {
                
                // This two lines have been taken from https://stackoverflow.com/questions/686353/random-float-number-generation
                float xIter = x + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((x + pixelXSide) - x)));
                float yIter = y + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((y + pixelYSide) - y)));
                Point image_point = Point(xIter, yIter, -this->camera.f.z); 
                
                Point p = this->baseChange.productMatrixPoint(image_point);
                Vector dir = Vector(p.x - origen.x, p.y - origen.y, p.z - origen.z);
                Ray actual_ray = Ray(origen, Vector(dir.x / dir.module(), dir.y / dir.module(), dir.z / dir.module())); 
                int saliente=-1;
                float* t = new float;
                bool isIntersect = false;
                while(true){
                    for (int m = 0; m < this->primitives.size(); m++) {
                        if(saliente != m){
                            if (this->primitives[m]->intersect(actual_ray, t, colorPrimitive)){ 
                                //cout<<" Distancia: "<<*t<<endl;
                                if( abs(*t) < minDist){
                                    saliente = m;
                                    minDist = abs(*t); 
                                    masCercano = this->primitives[m];
                                    countColor.r = colorPrimitive->r;
                                    countColor.r = colorPrimitive->g;
                                    countColor.r = colorPrimitive->b;
                                    isIntersect = true;
                                }
                            }
                        }
                    }
                    delete t;
                    if(isIntersect){
                        if(masCercano->isLight){ // Si emite luz
                            color.r = color.r + countColor.r;
                            color.g = color.g + countColor.g;
                            color.b = color.b + countColor.b;
                            break;
                        }
                        else {
                            string accion = masCercano->russianRoulette();
                            if (accion == "termina"){
                                color.r = color.r + 0.0;
                                color.g = color.g + 0.0;
                                color.b = color.b + 0.0;
                                isIntersect = false;
                                break;
                            }
                            else if(accion == "difusion"){
                                actual_ray = Ray(origen, dir);
                            }else if(accion == "especular"){
                                actual_ray = Ray(origen, dir);
                            }else if(accion == "refraccion"){
                                actual_ray = Ray(origen, dir);
                            }
                             
                            
                        }
                        
                    }
                    minDist = numeric_limits<float>::max();
                }
                progress++;
                if(progress == total / 4){
                    cout<<"25% of pixels processed"<<endl;
                }else if(progress == total / 2){
                    cout<<"50% of pixels processed"<<endl;
                }else if(progress == 3 * total / 4){
                    cout<<"75% of pixels processed"<<endl;
                }
                
            }
            //cout<<"Pixel: "<<i<<" "<<j<<"  Color: "<<color.r<<" "<<color.g<<" "<<color.b<<endl;
            this->projection[i][j].r = color.r / numRaysPerPixel;
            this->projection[i][j].g = color.g / numRaysPerPixel;
            this->projection[i][j].b = color.b / numRaysPerPixel;
        }
    }
    cout<<"100% of pixels processed"<<endl;
};
/*
void RayTracing::shootingRays() {

    // The info to use thread has been taken from https://www.bogotobogo.com/cplusplus/C11/1_C11_creating_thread.php
    //int nThreadsSupported = (int) std::thread::hardware_concurrency();
    int nThreadsSupported = 4;
    vector<thread> threads;

    int start = 0;
    int end = this->height / nThreadsSupported;

    for ( int i = 0; i < nThreadsSupported; i++) {
        threads[i] = thread(&RayTracing::shootingRaysAux, this, start, end);
        start = end;
        end = (i == nThreadsSupported - 2) ? this->height : end + this->height / nThreadsSupported;
    }

    for ( int i = 0; i < nThreadsSupported; i++) {
        threads[i].join();
    }
}
*/