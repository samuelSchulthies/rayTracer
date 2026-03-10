#include "vec3.h"
#include "ray.h"

double hitSphere(const point3& center, double radius, const ray& r);
double hitPolygon(const ray& r);