#pragma once

#include "vec3.h"
#include "vec2.h"
#include "ray.h"
#include "color.h"
#include "aabb.h"

class hit_record {
public:
    vec3 normal;
    double t;
};

class hittable {
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& ray) = 0;

    virtual aabb bounding_box() const = 0;

    virtual vec3 shade(const ray& ray, vec3 directionToLight, vec3 ambientLight, vec3 lightColor, double t, vec3 newNorm) = 0;

    virtual double getT() = 0;
    virtual vec3 getNormal() = 0;
    virtual double getRefl() = 0;
    virtual double getRefractIndex() = 0;
    virtual string getType() = 0;

};