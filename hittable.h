#include "vec3.h"
#include "vec2.h"
#include "ray.h"
#include "sphere.h"
#include "polygon.h"

class hittable {
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& ray);
};

//double hit(const point3& center, double radius, const ray& r);
//tuple<int, double, vec3>  hit(const vector<vec3>& vertices, const ray& ray);