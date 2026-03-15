#pragma once

#include "vec3.h"
#include "vec2.h"
#include "ray.h"
#include "color.h"

class hittable {
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& ray) = 0;

    virtual vec3 computePhong(const ray& ray, vec3 directionToLight, vec3 ambientLight, vec3 lightColor) = 0;

    virtual double getT() = 0;
};

//double hit(const point3& center, double radius, const ray& r);
//tuple<int, double, vec3>  hit(const vector<vec3>& vertices, const ray& ray);