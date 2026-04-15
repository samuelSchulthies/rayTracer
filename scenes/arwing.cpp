#include "scene.h"
#include "../tinyobjloader/tiny_obj_loader.cpp"

scene arwing(){
    string file = "arwing/arwing_low.obj";

    vector< vector<vec3> > arwing = getObj(file);
    hittable_list objects;

    for (vector<vec3> triangle : arwing){
        polygon triangleObject = polygon({triangle.at(0),
                 triangle.at(1),
                 triangle.at(2)},
                0.9,
                1.0,
                0.1,
                {1.0, 1.0, 0.0},
                {1.0, 1.0, 1.0},
                4.0,
                0.0,
                0.0);
        objects.add(make_shared<polygon>(triangleObject));
    }

    return scene(1.0,
                 vec3(0, 0, 0),
                 vec3(0,0,0),
                 vec3(0, 1, 0),

                 vec3(1.0, 1.0, 1.0),
                 vec3(1.0, 1.0, 1.0),
                 vec3(0.1, 0.1, 0.1),
                 vec3(0.2, 0.2, 0.2),

                 objects);
}