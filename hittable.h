#include "vec3.h"
#include "vec2.h"
#include "ray.h"

double hitSphere(const point3& center, double radius, const ray& r);
tuple<int, vec3>  hitPolygon(const vector<vec3>& vertices, const ray& ray);