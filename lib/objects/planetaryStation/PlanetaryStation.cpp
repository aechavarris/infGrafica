#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include "../../../lib/geometry/matrix/Matrix.h"
#include "../../../lib/geometry/vector/Vector.h"
#include "../../../lib/geometry/point/Point.h"
#include "../../../lib/objects/planet/Planet.h"
#include "../../../lib/objects/planetaryStation/PlanetaryStation.h"

PlanetaryStation::PlanetaryStation(){};

PlanetaryStation::PlanetaryStation(Planet p, float inclination, float azimuth){
    this->inclination = inclination * M_PI / 180;
    this->azimuth = azimuth * M_PI / 180;
    this->planet = p;

    this->position = calculatePositionUCS();
    this->surfaceNormal = calculateSurfaceNormal();
    this->longitudeTangentDirection = calculateLongitudeTangent();  
    this->latitudeTangentDirection = calculateLatitudeTangent(); 
}

Point PlanetaryStation::calculatePositionUCS() {
    float radio = this->planet.axis.module() / 2;

    Matrix inclinationMatrix = Matrix(
        cos(this->inclination),   -sin(this->inclination),   0.0,              0.0,
        sin(this->inclination),   cos(this->inclination),    0.0,              0.0,
        0.0,                0.0,                 1.0,              0.0,
        0.0,                0.0,                 0.0,              1.0
    );

    Matrix azimuthMatrix = Matrix(
        cos(this->azimuth),   0.0,    sin(this->azimuth), 0.0,
        0.0,            1.0,    0.0,          0.0,
        -sin(this->azimuth),  0.0,    cos(this->azimuth), 0.0,
        0.0,            0.0,    0.0,          1.0
    );

    Point tmp=inclinationMatrix.productMatrixPoint(this->planet.referenceCity);
    Point result=azimuthMatrix.productMatrixPoint(tmp);

    return result;
}

Vector PlanetaryStation::calculateSurfaceNormal() {
    Vector axis = Vector(this->planet.axis.x/this->planet.axis.module(),
                         this->planet.axis.y/this->planet.axis.module(),
                         this->planet.axis.z/this->planet.axis.module());

    float x = this->position.x - this->planet.center.x;
    float y = this->position.y - this->planet.center.y;
    float z = this->position.z - this->planet.center.z;
    
    Vector tmp = Vector(x, y, z);
    Vector surface = Vector(x / tmp.module(), y / tmp.module(), z / tmp.module());

    return surface;
}

Vector PlanetaryStation::calculateLongitudeTangent() {
    Vector longitude = this->planet.axis.cross(this->surfaceNormal);
    return Vector(longitude.x / longitude.module(), longitude.y / longitude.module(), longitude.z / longitude.module());
}

Vector PlanetaryStation::calculateLatitudeTangent() {
    Vector latitude = this->planet.axis.cross(this->longitudeTangentDirection);
    return Vector(latitude.x / latitude.module(), latitude.y / latitude.module(), latitude.z / latitude.module());
}

Vector PlanetaryStation::connectionBetweenStations(PlanetaryStation ps) { 
    float x = ps.position.x - this->position.x;
    float y = ps.position.y - this->position.y;
    float z = ps.position.z - this->position.z;
    Vector between1 = Vector(x, y, z);
    Vector between2 = Vector(-between1.x, -between1.y, -between1.z);
    if(!this->isPosibleToConnect(ps)){
        cout << "!!Warning!! Connection is not posible" << endl;
        cout << "Trajectory of the matter traverses any of the two planets" << endl;
    }
    return between1;
}

bool PlanetaryStation::isPosibleToConnect(PlanetaryStation ps){

    float x = ps.position.x - this->position.x;
    float y = ps.position.y - this->position.y;
    float z = ps.position.z - this->position.z;
    Vector between = Vector(x, y, z);
    Point start = this->position;
    float minimumCheck = 0.001 * this->planet.axis.module() / 2;
    
    x = start.x + between.x * minimumCheck;
    y = start.y + between.y * minimumCheck;
    x = start.z + between.z * minimumCheck;

    return true;
}
