#pragma once

#include "hittable.h"

using namespace std;

class hittable_list : hittable {
public:
    vector<shared_ptr<hittable>> objects;

    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() {
        objects.clear();
    }

    void add(shared_ptr<hittable> object) {
        objects.push_back(object);
        bbox = aabb(bbox, object->bounding_box());
    }

    aabb bounding_box() const {
        return bbox;
    }

    int getSize(){
        return objects.size();
    }

    shared_ptr<hittable> getObject(int i){
        return objects.at(i);
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec){

    }


    // TODO: refactor to remove this
    vec3 shade(const ray& ray, vec3 directionToLight, vec3 ambientLight, vec3 lightColor, double t, vec3 newNorm){}
    double getT(){}
    vec3 getNormal(){}
    double getRefl(){}
    double getRefractIndex(){}
    string getType(){}


private:
    aabb bbox;
};