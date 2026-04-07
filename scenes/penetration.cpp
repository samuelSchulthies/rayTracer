#include "scene.h"

scene penetration() {

    vector<hittable*> objects;
    // white sphere
    objects.push_back(new sphere({0.5, 0.0, -0.15},
                                 0.05,
                                 0.8,
                                 0.1,
                                 0.3,
                                 {1.0, 1.0, 1.0},
                                 {1.0, 1.0, 1.0},
                                 4.0,
                                 0.0,
                                 0.0));
    //red sphere
    objects.push_back(new sphere({0.3, 0.0, -0.1},
                                 0.08,
                                 0.8,
                                 0.8,
                                 0.1,
                                 {1.0, 0.0, 0.0},
                                 {0.5, 1.0, 0.5},
                                 32.0,
                                 0.0,
                                 0.0));
    // green sphere
    objects.push_back(new sphere({-0.6, 0.0, 0.0},
                                 0.3,
                                 0.7,
                                 0.5,
                                 0.1,
                                 {0.0, 1.0, 0.0},
                                 {0.5, 1.0, 0.5},
                                 64.0,
                                 0.0,
                                 0.0));
    // reflective sphere
    objects.push_back(new sphere({0.1, -0.55, 0.25},
                                 0.3,
                                 0.0,
                                 0.1,
                                 0.1,
                                 {0.75, 0.75, 0.75},
                                 {1.0, 1.0, 1.0},
                                 10.0,
                                 0.9,
                                 0.0));
    // blue triangle
    objects.push_back(new polygon({{0.3, -0.3, -0.4},
                                   {0.0, 0.3, -0.1},
                                   {-0.3, -0.3, 0.2}},
                                  0.9,
                                  0.9,
                                  0.1,
                                  {0.0, 0.0, 1.0},
                                  {1.0, 1.0, 1.0},
                                  32.0,
                                  0.0,
                                  0.0));
    // yellow triangle
    objects.push_back( new polygon({{-0.2, 0.1, 0.1},
                                    {-0.2, -0.5, 0.2},
                                    {-0.2, 0.1, -0.3}},
                                   0.9,
                                   0.5,
                                   0.1,
                                   {1.0, 1.0, 0.0},
                                   {1.0, 1.0, 1.0},
                                   4.0,
                                   0.0,
                                   0.0));

    return scene(1.0,
                 vec3(0, 0, 0),
                 vec3(0,0,0),
                 vec3(0, 1, 0),

                 vec3(1.0, 0.0, 0.0),
                 vec3(1.0, 1.0, 1.0),
                 vec3(0.1, 0.1, 0.1),
                 vec3(0.2, 0.2, 0.2),

                 objects);
}