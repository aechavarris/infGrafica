#pragma once

#include "Sphere.h"

Sphere::Sphere(){};

Sphere::Sphere(Point center, float radius, RGB rgb) {
    this->center = center;
    this->radius = radius;
    this->rgb = rgb;
};


bool Sphere::intersect(Ray ray, float* t, RGB* color) { 
    //solve for tc
	Point L = Point(this->center.x - ray.origin.x, this->center.y - ray.origin.y, this->center.z - ray.origin.z);
	float tc = L.dot(ray.direction);
	
	if ( tc > 0.0 ) return false;
	float d2 = (tc * tc) - (L.dot(L));
	
	float radius2 = this->radius * this->radius;
	if ( d2 > radius2) return false;

	//solve for t1c
	float t1c = sqrt( radius2 - d2 );

	//solve for intersection points
	*t = abs( tc - t1c);
	color->r = this->rgb.r;
    color->g = this->rgb.g;
    color->b = this->rgb.b;
	//cout << "Soy esfera color "<<this->rgb.r<<" "<<this->rgb.g<<" "<<this->rgb.b<<endl;
	return true;
}
