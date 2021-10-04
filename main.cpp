#include <iostream>
#include "lib/geometry/vector/Vector.h"
#include "lib/geometry/point/Point.h"
#include "lib/geometry/matrix/Matrix.h"
#include "objects/planet/Planet.h"
#include "objects/planetaryStation/PlanetaryStation.h"
using namespace std;

int main() {
    Point reference = Point(5.0, 5.0, 4.0);
    Point center = Point(5.0, 5.0, 5.0);
    Vector axis = Vector(0.0, 2.0, 0.0);

    Planet p = Planet(center, axis,reference );
    PlanetaryStation station= PlanetaryStation(p, 90, 0);//PlanetaryStation station= PlanetaryStation(p, 0.4966431349286087, 1.4054748615365447);
    
    cout << "Position x: " << station.position.x << endl;
    cout << "Position y: " << station.position.y << endl; 
    cout << "Position z: " << station.position.z << endl;
    cout << endl;
    cout << "Surface Normal x: " << station.surfaceNormal.x << endl;
    cout << "Surface Normal y: " << station.surfaceNormal.y << endl;
    cout << "Surface Normal z: " << station.surfaceNormal.z << endl;
    cout << "Surface Module: " << station.surfaceNormal.module() << endl;

    return 0;
}