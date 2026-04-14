#include "scene.h"

scene penetration() {

    hittable_list objects;

    sphere whiteSphere = sphere({0.5, 0.0, -0.15},
                                     0.05,
                                     0.8,
                                     0.1,
                                     0.3,
                                     {1.0, 1.0, 1.0},
                                     {1.0, 1.0, 1.0},
                                     4.0,
                                     0.0,
                                     0.0);

    sphere redSphere = sphere({0.3, 0.0, -0.1},
                              0.08,
                              0.8,
                              0.8,
                              0.1,
                              {1.0, 0.0, 0.0},
                              {0.5, 1.0, 0.5},
                              32.0,
                              0.0,
                              0.0);

    sphere greenSphere = sphere({-0.6, 0.0, 0.0},
                                0.3,
                                0.7,
                                0.5,
                                0.1,
                                {0.0, 1.0, 0.0},
                                {0.5, 1.0, 0.5},
                                64.0,
                                0.0,
                                0.0);

    sphere reflectiveSphere = sphere({0.1, -0.55, 0.25},
                                     0.3,
                                     0.0,
                                     0.1,
                                     0.1,
                                     {0.75, 0.75, 0.75},
                                     {1.0, 1.0, 1.0},
                                     10.0,
                                     0.9,
                                     0.0);

    polygon blueTriangle = polygon({{0.3, -0.3, -0.4},
                                    {0.0, 0.3, -0.1},
                                    {-0.3, -0.3, 0.2}},
                                   0.9,
                                   0.9,
                                   0.1,
                                   {0.0, 0.0, 1.0},
                                   {1.0, 1.0, 1.0},
                                   32.0,
                                   0.0,
                                   0.0);

    polygon yellowTriangle = polygon({{-0.2, 0.1, 0.1},
                                      {-0.2, -0.5, 0.2},
                                      {-0.2, 0.1, -0.3}},
                                     0.9,
                                     0.5,
                                     0.1,
                                     {1.0, 1.0, 0.0},
                                     {1.0, 1.0, 1.0},
                                     4.0,
                                     0.0,
                                     0.0);

    objects.add(make_shared<sphere>(whiteSphere));
    objects.add(make_shared<sphere>(redSphere));
    objects.add(make_shared<sphere>(greenSphere));
    objects.add(make_shared<sphere>(reflectiveSphere));
    objects.add(make_shared<polygon>(blueTriangle));
    objects.add(make_shared<polygon>(yellowTriangle));


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