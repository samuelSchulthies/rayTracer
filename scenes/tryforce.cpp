#include "scene.h"

scene tryforce() {

    vector<hittable*> objects;
//    // reflective sphere
    objects.push_back(new sphere({0.0, 0.7, 0.3},
                                 0.5,
                                 0.5,
                                 0.1,
                                 0.1,
                                 {0.75, 0.75, 0.75},
                                 {1.0, 1.0, 1.0},
                                 10.0,
                                 0.9,
                                 0.0));
    // triforce
    // right
    objects.push_back(new polygon({{0.4, -0.4, 0.0},
                                   {0.2, -0.1, -0.1},
                                   {0.0, -0.4, 0.0}},
                                  0.9,
                                  0.9,
                                  0.1,
                                  {1.0, 1.0, 0.0},
                                  {1.0, 1.0, 1.0},
                                  32.0,
                                  0.9,
                                  0.0));

    // left
    objects.push_back(new polygon({{0.0, -0.4, 0.0}, // right
                                   {-0.2, -0.1, -0.1}, // top
                                   {-0.4, -0.4, 0.0}}, // left
                                  0.9,
                                  0.9,
                                  0.1,
                                  {1.0, 1.0, 0.0},
                                  {1.0, 1.0, 1.0},
                                  32.0,
                                  0.9,
                                  0.0));
    // top
    objects.push_back(new polygon({{0.2, -0.1, 0.0}, // right
                                   {0.0, 0.2, -0.1}, // top
                                   {-0.2, -0.1, 0.0}}, // left
                                  0.9,
                                  0.9,
                                  0.1,
                                  {1.0, 1.0, 0.0},
                                  {1.0, 1.0, 1.0},
                                  32.0,
                                  0.4,
                                  0.0));

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