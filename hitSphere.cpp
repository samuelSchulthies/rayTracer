#include "hittable.h"

double hitSphere(const point3& center, double radius, const ray& r) {
    vec3 rayToSphere = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), rayToSphere);
    auto c = dot(rayToSphere, rayToSphere) - radius*radius;
    auto discriminant = b*b - 4*a*c;

    if (discriminant >= 0){
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
    return -1.0;
}