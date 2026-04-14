#include "scene.h"

scene tryforce() {

    hittable_list objects;
    sphere reflectiveSphere = sphere({0.0, 0.7, 0.3},
                                     0.5,
                                     0.5,
                                     0.1,
                                     0.1,
                                     {0.75, 0.75, 0.75},
                                     {1.0, 1.0, 1.0},
                                     10.0,
                                     0.9,
                                     0.0);

    polygon triforceRight = polygon({{0.4, -0.4, 0.0}, // right
                                     {0.2, -0.1, -0.1}, // top
                                     {0.0, -0.4, 0.0}}, // left
                                    0.9,
                                    0.9,
                                    0.1,
                                    {1.0, 1.0, 0.0},
                                    {1.0, 1.0, 1.0},
                                    32.0,
                                    0.9,
                                    0.0);

    polygon triforceLeft = polygon({{0.0, -0.4, 0.0},
                                    {-0.2, -0.1, -0.1},
                                    {-0.4, -0.4, 0.0}},
                                   0.9,
                                   0.9,
                                   0.1,
                                   {1.0, 1.0, 0.0},
                                   {1.0, 1.0, 1.0},
                                   32.0,
                                   0.9,
                                   0.0);

    polygon triforceTop = polygon({{0.2, -0.1, 0.0},
                                   {0.0, 0.2, -0.1},
                                   {-0.2, -0.1, 0.0}},
                                  0.9,
                                  0.9,
                                  0.1,
                                  {1.0, 1.0, 0.0},
                                  {1.0, 1.0, 1.0},
                                  32.0,
                                  0.4,
                                  0.0);

    objects.add(make_shared<sphere>(reflectiveSphere));
    objects.add(make_shared<polygon>(triforceRight));
    objects.add(make_shared<polygon>(triforceLeft));
    objects.add(make_shared<polygon>(triforceTop));

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