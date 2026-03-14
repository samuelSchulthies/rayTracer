#include "scene.h"

scene spiralSpheres(){
    vector<sphere> spheres;
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double radius = 0.2;
    double r = 0.3;
    double g = 0.6;
    double b = 1.0;
    double angle = 0.0;
    for(int i = 0; i < 9; i++) {
        spheres.push_back(sphere({x, y, z},
                                 radius,
                                 0.8,
                                 0.1,
                                 0.3,
                                 {r, g, b},
                                 {1.0, 1.0, 1.0},
                                 4.0,
                                 0.0));
        angle += 1.0;
        x += cos(angle) * radius;
        y += sin(angle) * radius;
        z -= 0.05;
        radius -= 0.025;
        r -= 0.05;
        g += 0.05;
        b -= 0.05;
    }
    vector<hittable*> objects;
    for(int i = 0; i < spheres.size(); i++) {
        objects.push_back(&spheres.at(i));
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