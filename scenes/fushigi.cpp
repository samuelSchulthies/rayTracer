#include "scene.h"

scene fushigi() {

    hittable_list objects;

    sphere reflectiveSphere = sphere({0.0, 0.3, -1.0},
                                                 0.25,
                                                 0.0,
                                                 0.1,
                                                 0.1,
                                                 {0.75, 0.75, 0.75},
                                                 {1.0, 1.0, 1.0},
                                                 10.0,
                                                 0.9,
                                                 0.0);
    polygon blueTriangle = polygon({{0.0, -0.7, -0.5},
                 {1.0, 0.4, -1.0},
                 {0.0, -0.7, -1.5}},
                0.9,
                1.0,
                0.1,
                {0.0, 0.0, 1.0},
                {1.0, 1.0, 1.0},
                4.0,
                0.0,
                0.0);
    polygon yellowTriangle = polygon({{0.0, -0.7, -0.5},
                 {0.0, -0.7, -1.5},
                 {-1.0, 0.4, -1.0}},
                0.9,
                1.0,
                0.1,
                {1.0, 1.0, 0.0},
                {1.0, 1.0, 1.0},
                4.0,
                0.0,
                0.0);

    objects.add(make_shared<sphere>(reflectiveSphere));
    objects.add(make_shared<polygon>(blueTriangle));
    objects.add(make_shared<polygon>(yellowTriangle));

    return scene(1.0,
                 vec3(0, 0, 0),
                 vec3(0,0,0),
                 vec3(0, 1, 0),

                 vec3(0.0, 1.0, 0.0),
                 vec3(1.0, 1.0, 1.0),
                 vec3(0.1, 0.1, 0.1),
                 vec3(0.2, 0.2, 0.2),

                 objects);
}