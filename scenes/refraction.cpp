#include "scene.h"

scene refraction() {

    vector<hittable*> objects;
    // refractive sphere
    objects.push_back(new sphere({0.0, -0.05, 0.6},
                                 0.1,
                                 0.8,
                                 0.5,
                                 0.5,
                                 {0.75, 0.75, 0.9},
                                 {1.0, 1.0, 1.0},
                                 10.0,
                                 0.0,
                                 1.52));
    // triforce
    // right
    objects.push_back(new polygon({{0.4, -0.4, -1.0},
                                   {0.2, -0.1, -1.0},
                                   {0.0, -0.4, -1.0}},
                                  0.9,
                                  0.9,
                                  0.1,
                                  {1.0, 1.0, 0.0},
                                  {1.0, 1.0, 1.0},
                                  32.0,
                                  0.0,
                                  0.0));

    // left
    objects.push_back(new polygon({{0.0, -0.4, -1.0}, // right
                                   {-0.2, -0.1, -1.0}, // top
                                   {-0.4, -0.4, -1.0}}, // left
                                  0.9,
                                  0.9,
                                  0.1,
                                  {1.0, 1.0, 0.0},
                                  {1.0, 1.0, 1.0},
                                  32.0,
                                  0.0,
                                  0.0));
    // top
    objects.push_back(new polygon({{0.2, -0.1, -1.0}, // right
                                   {0.0, 0.2, -1.0}, // top
                                   {-0.2, -0.1, -1.0}}, // left
                                  0.9,
                                  0.9,
                                  0.1,
                                  {1.0, 1.0, 0.0},
                                  {1.0, 1.0, 1.0},
                                  32.0,
                                  0.0,
                                  0.0));

    return scene(1.0,
                 vec3(0, 0, 0),
                 vec3(0,0,0),
                 vec3(0, 1, 0),

                 vec3(0.0, 1.0, 2.0),
                 vec3(1.0, 1.0, 1.0),
                 vec3(0.1, 0.1, 0.1),
                 vec3(0.5, 0.7, 1.0),

                 objects);
}