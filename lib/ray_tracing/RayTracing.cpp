#pragma once

#include "RayTracing.h"

RayTracing::RayTracing(){};

RayTracing::RayTracing(Camera camera, int numRaysPerPixel, int width, int height)
{
    this->camera = camera;
    this->numRaysPerPixel = numRaysPerPixel;
    this->width = width;
    this->height = height;
    this->baseChange = Matrix(camera.u, camera.i, camera.f, camera.origin);
    this->projection.resize(height);
    for (int i = 0; i < height; i++)
    {
        this->projection[i].resize(width);
    }
};

void RayTracing::shootingRays()
{
    Point origen = this->camera.origin; 
    Primitive *masCercano;

    RGB colorAcumulado = RGB(0.0, 0.0, 0.0);
    RGB colorLuzDirecta = RGB(0.0, 0.0, 0.0);
    RGB *colorPrimitive = new RGB(0.0, 0.0, 0.0);
    RGB actualColor = RGB(0.0, 0.0, 0.0);
    RGB rayColor = RGB(1.0, 1.0, 1.0);
    
    float pixelXSide = (float)2 / this->height;
    float pixelYSide = (float)2 / this->width;

    srand(time(0));

    cout << "Starting ray tracing..." << endl;

    int total = width * height * numRaysPerPixel;
    int progress = 0;
    int muertos=0;
    for (float i = 0; i < this->height; i++)
    {

        for (float j = 0; j < this->width; j++)
        {

            colorAcumulado = RGB(0.0, 0.0, 0.0);         //This variable save the final color of each pixel.    
            
            float x = i * pixelXSide - 1.0;
            float y = j * pixelYSide - 1.0;

            float minDist = numeric_limits<float>::max();
            for (int n = 0; n < this->numRaysPerPixel; n++)
            {
                
                // This two lines have been taken from https://stackoverflow.com/questions/686353/random-float-number-generation
                float xIter = x + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / ((x + pixelXSide) - x)));
                float yIter = y + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / ((y + pixelYSide) - y)));
                Point image_point = Point(xIter, yIter, -this->camera.f.z);

                Point p = this->baseChange.productMatrixPoint(image_point);
                Vector dir = Vector(p.x - origen.x, p.y - origen.y, p.z - origen.z);
                Ray actual_ray = Ray(origen, Vector(dir.x / dir.module(), dir.y / dir.module(), dir.z / dir.module()));

                int nRebotes = 1;
                
                bool isIntersect = false;
                bool end = false;

                rayColor = RGB(1.0, 1.0, 1.0);          //This variable save the color of the actual ray.
                colorLuzDirecta = RGB(0.0, 0.0, 0.0);   //This variable save the color of the direct light.

                while (!end)
                {
                    float *t = new float;
                    for (int m = 0; m < this->primitives.size(); m++)
                    {

                        if (this->primitives[m]->intersect(actual_ray, t, colorPrimitive))
                        {
                            //cout<<" Distancia: "<<*t<<endl;
                            if (*t < minDist)
                            {
                                minDist = *t;
                                masCercano = this->primitives[m];
                                actualColor = *colorPrimitive; 
                                //cout<<"Pixel "<<i<<" "<<j<<" Mas cercano: "<<actualColor.r<<" "<<actualColor.g<<" "<<actualColor.b<<endl;             
                                isIntersect = true;
                            }
                        }
                    }
                    delete t;

                    if (isIntersect)
                    {
                        if (masCercano->isLight) // Se checkea si es luz de área
                        { 
                            rayColor.r = rayColor.r * actualColor.r;
                            rayColor.g = rayColor.g * actualColor.g;
                            rayColor.b = rayColor.b * actualColor.b;
                            minDist = numeric_limits<float>::max();
                            //cout<<"Soy luz"<<endl;
                            end=true;
                            break;
                        }
                        else
                        {
                            string accion = masCercano->russianRoulette();
                            Point newOrigen = Point(actual_ray.origin.x + actual_ray.direction.x * minDist,
                                                    actual_ray.origin.y + actual_ray.direction.y * minDist,
                                                    actual_ray.origin.z + actual_ray.direction.z * minDist);

                            if (accion == "fin")
                            {
                                // Color negro
                                //rayColor = RGB(0.0, 0.0, 0.0);
                                end = true;
                                muertos++;
                                break;
                                //cout<<"C muere"<<endl;
                            }
                            else if (accion == "difusion")
                            {
                                //cout<< "Rayo difusion: "<<endl;
                                dir = masCercano->difusion(actual_ray, minDist, newOrigen);
                                actual_ray = Ray(newOrigen, dir);
                                rayColor.r = rayColor.r * actualColor.r;
                                rayColor.g = rayColor.g * actualColor.g;
                                rayColor.b = rayColor.b * actualColor.b;
                                //cout<<"Rayo: "<<rayColor.r<<" "<<rayColor.g<<" "<<rayColor.b<<endl;
                                nRebotes++;
                            }
                            else if (accion == "especular")
                            {
                                //cout<<"Rayo especular: "<<actual_ray.direction.x<<" "<<actual_ray.direction.y<<" "<<actual_ray.direction.z<<endl;;
                                dir = masCercano->especular(actual_ray, minDist);
                                actual_ray = Ray(origen, dir);
                                nRebotes++;
                            }
                            else if (accion == "refraccion")
                            {
                                dir = masCercano->refraccion(actual_ray, minDist,newOrigen);
                                actual_ray = Ray(origen, dir);
                                rayColor.r = 1.0;
                                rayColor.g = 1.0;
                                rayColor.b = 1.0;
                            }
                        }
                        
                        isIntersect = false;
                        minDist = numeric_limits<float>::max();
                    }
                    else {
                        rayColor = RGB(0.0, 0.0, 0.0);
                        end = true;
                    }
                }

                colorAcumulado.r = colorAcumulado.r + rayColor.r;
                colorAcumulado.g = colorAcumulado.g + rayColor.g;
                colorAcumulado.b = colorAcumulado.b + rayColor.b;

                progress++;
                if (progress == total / 4)
                {
                    cout << "25% of pixels processed" << endl;
                }
                else if (progress == total / 2)
                {
                    cout << "50% of pixels processed" << endl;
                }
                else if (progress == 3 * total / 4)
                {
                    cout << "75% of pixels processed" << endl;
                }
            }
            //cout<<"Pixel: "<<i<<" "<<j<<"  Color: "<<colorAcumulado.r<<" "<<colorAcumulado.g<<" "<<colorAcumulado.b<<endl;
            this->projection[i][j].r = colorAcumulado.r / numRaysPerPixel;
            this->projection[i][j].g = colorAcumulado.g / numRaysPerPixel;
            this->projection[i][j].b = colorAcumulado.b / numRaysPerPixel;
        }
    }
    cout << "100% of pixels processed" << endl;
    cout <<"Rayos totales: "<<this->height*this->width*numRaysPerPixel<<endl;
    cout<<"Rayos muertos: "<<muertos<<endl;
};

/*void RayTracing::shootingRays()
{

    // The info to use thread has been taken from https://www.bogotobogo.com/cplusplus/C11/1_C11_creating_thread.php
    int nThreadsSupported = (int)std::thread::hardware_concurrency();
    vector<thread> threads;

    int start = 0;
    int end = this->height / nThreadsSupported;

    for (int i = 0; i < nThreadsSupported; i++)
    {
        threads[i] = thread(&RayTracing::shootingRaysAux, this, start, end);
        start = end;
        end = (i == nThreadsSupported - 2) ? this->height : end + this->height / nThreadsSupported;
    }

    for (int i = 0; i < nThreadsSupported; i++)
    {
        threads[i].join();
    }
};*/