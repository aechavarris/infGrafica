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

void RayTracing::shootingRaysAux(int start, int end,progresscpp::ProgressBar &progressBar)
{
    Point origen = this->camera.origin; 
    Primitive *masCercano;

    RGB colorAcumulado = RGB(0.0, 0.0, 0.0);
    RGB* colorLuzDirecta =new RGB(0.0, 0.0, 0.0);
    RGB rayColor = RGB(1.0, 1.0, 1.0);

    const int limit = this->width * this->height ;

    float pixelXSide = (float)2 / this->height;
    float pixelYSide = (float)2 / this->width;

    srand(time(0));

    int total = 0;
    int progress = 0;
    for (int i = start; i < end; i++)
    {

        for (int j = 0; j < this->width; j++)
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
                int saliente = -1;
                bool isIntersect = false;
                bool end = false;

                rayColor = RGB(1.0, 1.0, 1.0);          //This variable save the color of the actual ray.
                *colorLuzDirecta = RGB(0.0, 0.0, 0.0);   //This variable save the color of the direct light.
                
                while (!end)
                {
                    float *t1 = new float;
                    float *t2 = new float;
                    for (int m = 0; m < this->primitives.size(); m++)
                    {

                        if (this->primitives[m]->intersect(actual_ray, t1,t2,this->backgroundLeft,this->frontRight) )
                        {   
                                if (*t1 < minDist)
                                {
                                    minDist = *t1;
                                    
                                    masCercano = this->primitives[m]; 
                                    
                                    isIntersect = true;
                                    saliente = m;
                                }
                            
                        }
                    }
                    delete t1;
                    delete t2;
                    if (isIntersect)
                    {
                        if (masCercano->isLight) // Se checkea si es luz de área
                        { 
                            if(masCercano->texture->HDR_RESOLUTION!= -1.0){
                                Point newOrigen = Point(actual_ray.origin.x + actual_ray.direction.x * minDist,
                                                    actual_ray.origin.y + actual_ray.direction.y * minDist,
                                                    actual_ray.origin.z + actual_ray.direction.z * minDist);
                                float x = 0.0;
                                float y = 0.0;
                                Vector normal = masCercano->getNormal(actual_ray,minDist);
                                if(normal.x !=0.0){
                                        x = int((newOrigen.z - this->frontRight.z) *10) % masCercano->texture->width;
                                        y = int((newOrigen.y - this->frontRight.y) *10) % masCercano->texture->height;
                                    }else if (normal.y != 0.0){
                                        x = int((newOrigen.x - this->backgroundLeft.x) *10) % masCercano->texture->width;
                                        y = int((-newOrigen.z - this->frontRight.z) *10) % masCercano->texture->height;
                                    }else if (normal.z != 0.0){
                                        x = int((newOrigen.x - this->backgroundLeft.x) *10) % masCercano->texture->width;
                                        y = int((newOrigen.y - this->frontRight.y) *10) % masCercano->texture->height;
                                    }
                                if(x<0){
                                    x = masCercano->texture->width + x;
                                }if(y<0){
                                    y = masCercano->texture->height + y;
                                }
                                
                                
                                rayColor = rayColor * masCercano->texture->RGBTuples[y][x];
                            }else{
                                rayColor = rayColor * masCercano->emisionRGB;
                            }
                            
                            end = true;
                        }
                        else
                        {
                            
                            Ray auxRay = actual_ray;
                            float* random = new float;
                            string accion = masCercano->russianRoulette(nRebotes,random);
                            Point newOrigen = Point(actual_ray.origin.x + actual_ray.direction.x * minDist,
                                                    actual_ray.origin.y + actual_ray.direction.y * minDist,
                                                    actual_ray.origin.z + actual_ray.direction.z * minDist);
                            
                            if (accion == "fin")
                            {
                                // Color negro
                                rayColor = RGB(0.0, 0.0, 0.0);
                                end = true;
                                minDist = numeric_limits<float>::max();
                                break;
                            }
                            else if (accion == "difusion")
                            {
                                dir = masCercano->difusion(actual_ray, minDist, newOrigen,this->baseChange);
                                actual_ray = Ray(newOrigen, dir);
                                rayColor = rayColor * masCercano->matProperties.lambertianDiffuse;
                                if(masCercano->texture->HDR_RESOLUTION != -1.0){
                                    
                                    Vector normal = masCercano->getNormal(auxRay,minDist);
                                    float x = 0.0;
                                    float y = 0.0;
                                    if(normal.x !=0.0){
                                        x = int((newOrigen.z - this->frontRight.z) *10) % masCercano->texture->width;
                                        y = int((newOrigen.y - this->frontRight.y) *10) % masCercano->texture->height;
                                        if(x<0){
                                        x = masCercano->texture->width + x;
                                       
                                        }if(y<0){
                                            y = masCercano->texture->height + y;
                                        }
                                        rayColor = rayColor * masCercano->texture->RGBTuples[y][x];
                                    }else if (normal.y != 0.0){
                                        x = int((newOrigen.x - this->backgroundLeft.x) *10) % masCercano->texture->width;
                                        y = int((newOrigen.z - this->frontRight.z) *10) % masCercano->texture->height;
                                        if(x<0){
                                        x = masCercano->texture->width + x;
                                       
                                        }if(y<0){
                                            y = masCercano->texture->height + y;
                                        }
                                        rayColor = rayColor * masCercano->texture->RGBTuples[y][x];
                                    }else if (normal.z != 0.0){
                                        x = int((newOrigen.x - this->backgroundLeft.x) *10) % masCercano->texture->width;
                                        y = int((newOrigen.y - this->frontRight.y) *10) % masCercano->texture->height;
                                        if(x<0){
                                        x = masCercano->texture->width + x;
                                       
                                        }if(y<0){
                                            y = masCercano->texture->height + y;
                                        }
                                        rayColor = rayColor * masCercano->texture->RGBTuples[y][x];
                                    }
                                    
                                }else{
                                    rayColor = rayColor * masCercano->emisionRGB;
                                }
                                nRebotes++;
                                this->checkLights(masCercano,auxRay,minDist,rayColor,colorLuzDirecta,progressBar);
                            }
                            else if (accion == "especular")
                            {
                                dir = masCercano->especular(actual_ray, minDist,this->baseChange);
                                actual_ray = Ray(newOrigen, dir);
                                rayColor = rayColor * masCercano->matProperties.deltaBRDF ;
                                nRebotes++;
                            }
                            else if (accion == "refraccion")
                            {
                                actual_ray = masCercano->refraccion(actual_ray, minDist,this->baseChange,this->backgroundLeft,this->frontRight);
                                rayColor = rayColor * masCercano->matProperties.deltaBTDF ;
                            }
                            delete random;
                        }
                        
                        isIntersect = false;
                        minDist = numeric_limits<float>::max();
                    }
                    else {
                        rayColor = RGB(0.0, 0.0, 0.0);
                        end = true;
                    }            
                }
                colorAcumulado = colorAcumulado + rayColor + *colorLuzDirecta/ (float) nRebotes;
            }

            ++progressBar;
            total++;
            if(total % 100 == 0){
                progressBar.display();
            }
            this->projection[i][j].r = colorAcumulado.r / numRaysPerPixel;
            this->projection[i][j].g = colorAcumulado.g / numRaysPerPixel;
            this->projection[i][j].b = colorAcumulado.b / numRaysPerPixel;
        }
    }
};

void RayTracing::shootingRays()
{

    // The info to use thread has been taken from https://www.bogotobogo.com/cplusplus/C11/1_C11_creating_thread.php
    int nThreadsSupported = (int)std::thread::hardware_concurrency();
    vector<thread> threads=vector<thread>();

    int start = 0;
    int end = this->height / nThreadsSupported;

    // initialize the bar
    int limit = this->width * this->height;
    progresscpp::ProgressBar progressBar(limit, 70); //This progressbar has been taken from https://github.com/prakhar1989/progress-cpp
    
    cout << "Starting ray tracing..." << endl;
    for (int i = 0; i < nThreadsSupported; i++)
    {
        
        threads.push_back(thread(&RayTracing::shootingRaysAux, this, start, end, ref(progressBar)));
        start = end;
        end = (i == nThreadsSupported - 2) ? this->height : end + this->height / nThreadsSupported;
    }

    for (int i = 0; i < nThreadsSupported; i++)
    {
        threads.at(i).join();
    }
    progressBar.done();
    cout <<"Rayos totales: "<<this->height*this->width*numRaysPerPixel<<endl;
    
};

void RayTracing::checkLights(Primitive* mas_cercano,Ray ray,float distancia,RGB raycolor,RGB* luzDirecta,progresscpp::ProgressBar &progressBar){
    float intensity = 4000;
    for (auto i : this->lights)
    {
        Point p = Point(ray.origin.x + ray.direction.x * distancia,
                    ray.origin.y + ray.direction.y * distancia,
                    ray.origin.z + ray.direction.z * distancia);
        Vector light_direction = Vector(i->center - p);
        Ray lightRay = Ray(p, light_direction.normalize());
        float light_distance = light_direction.module();
        float *t2 = new float;
        float *t1 = new float;
        bool puntual = true;

        for (auto n : this->primitives)
        {

            if (n->intersect(lightRay, t1,t2,this->backgroundLeft,this->frontRight) )
            {
                    if (*t1 < light_distance)
                    {
                        puntual = false;
                        break;
                    } 
            }
        }
    
        if(puntual){

            RGB lightIntensity = i->color * intensity;
            float tCuadrado = light_distance * light_distance;
            if(tCuadrado < 1.0) tCuadrado = 1.0;
            Vector normal = mas_cercano->getNormal(ray,distancia);
            
            float cos = fabs(normal.dot(light_direction.normalize()));
            
            if(mas_cercano->texture->HDR_RESOLUTION != -1.0 &&
                    (fabs(normal.x)==1 || fabs(normal.y) == 1 || fabs(normal.z) == 1)){
                        
                Point aux = Point(ray.origin.x + ray.direction.x * distancia,
                    ray.origin.y + ray.direction.y * distancia,
                    ray.origin.z + ray.direction.z * distancia);
                float x = 0.0;
                float y = 0.0;
                if(normal.x !=0.0){
                    x = int((aux.z - this->frontRight.z) *10) % mas_cercano->texture->width;
                    y = int((aux.y - this->frontRight.y) *10) % mas_cercano->texture->height;
                    if(x<0){
                    x = mas_cercano->texture->width + x;
                                    
                    }if(y<0){
                        y = mas_cercano->texture->height + y;
                    }
                    *luzDirecta = *luzDirecta +  ( (lightIntensity / tCuadrado) *  mas_cercano->texture->RGBTuples[y][x] * (mas_cercano->matProperties.lambertianDiffuse / PI) * cos);
                }else if (normal.y != 0.0){
                    x = int((aux.x - this->backgroundLeft.x) *10) % mas_cercano->texture->width;
                    y = int((aux.z - this->frontRight.z) *10) % mas_cercano->texture->height;
                    if(x<0){
                    x = mas_cercano->texture->width + x;
                                    
                    }if(y<0){
                        y = mas_cercano->texture->height + y;
                    }
                    *luzDirecta = *luzDirecta +  ( (lightIntensity / tCuadrado) *  mas_cercano->texture->RGBTuples[y][x] * (mas_cercano->matProperties.lambertianDiffuse / PI) * cos);

                }else if (normal.z != 0.0){
                    x = int((aux.x - this->backgroundLeft.x) *10) % mas_cercano->texture->width;
                    y = int((aux.y - this->frontRight.y) *10) % mas_cercano->texture->height;
                    if(x<0){
                    x = mas_cercano->texture->width + x;
                                    
                    }if(y<0){
                        y = mas_cercano->texture->height + y;
                    }
                    *luzDirecta = *luzDirecta +  ( (lightIntensity / tCuadrado) *  mas_cercano->texture->RGBTuples[y][x] * (mas_cercano->matProperties.lambertianDiffuse / PI) * cos);
                }
            }else{
                *luzDirecta = *luzDirecta +  ( (lightIntensity / tCuadrado) *  mas_cercano->emisionRGB * (mas_cercano->matProperties.lambertianDiffuse / PI) * cos);
            }
            
        }
        
    
    delete t2;
    delete t1;

    }
    
}
