#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include "../../../lib/geometry/matrix/Matrix.h"
#include "../../../lib/geometry/vector/Vector.h"
#include "../../../lib/geometry/point/Point.h"
#include "../../../lib/objects/planet/Planet.h"

#ifndef _PLANETARY_STATION
#define _PLANETARY_STATION

class PlanetaryStation {
    public:
        float inclination;
        float azimuth;
        Planet planet;

        Point position;
        Vector surfaceNormal;
        Vector longitudeTangentDirection;
        Vector latitudeTangentDirection;

        /*
         * Constructor de la clase PlanetaryStation
         */
        PlanetaryStation();
        PlanetaryStation (Planet p, float inclination, float azimuth);
        Vector connectionBetweenStations(PlanetaryStation ps);

    private:
        /*
         * Pre:
         * Post:
         */
        Point calculatePositionUCS();

        /*
         * Pre:
         * Post:
         */
        Vector calculateSurfaceNormal();

        /*
         * Pre:
         * Post:
         */
        Vector calculateLongitudeTangent();

        /*
         * Pre:
         * Post:
         */
        Vector calculateLatitudeTangent();

        /*
         * Pre:
         * Post:
         */
        bool isPosibleToConnect(PlanetaryStation ps);
};

#include  "PlanetaryStation.cpp"
#endif