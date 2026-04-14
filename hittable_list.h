#pragma once

#include "hittable.h"

using namespace std;

class hittable_list {
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

private:
    aabb bbox;
};