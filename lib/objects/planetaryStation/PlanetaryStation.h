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