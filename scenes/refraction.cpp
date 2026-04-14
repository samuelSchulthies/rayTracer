#include "scene.h"

scene refraction() {

    hittable_list objects;
    // refractive sphere
    sphere refractiveSphere = sphere({0.0, -0.05, 0.6},
                                     0.1,
                                     0.8,
                                     0.5,
                                     0.5,
                                     {0.75, 0.75, 0.9},
                                     {1.0, 1.0, 1.0},
                                     10.0,
                                     0.0,
                                     1.52);

    polygon triforceRight = polygon({{0.4, -0.4, -1.0},
                                     {0.2, -0.1, -1.0},
                                     {0.0, -0.4, -1.0}},
                                    0.9,
                                    0.9,
                                    0.1,
                                    {1.0, 1.0, 0.0},
                                    {1.0, 1.0, 1.0},
                                    32.0,
                                    0.0,
                                    0.0);

    polygon triforceLeft = polygon({{0.0, -0.4, -1.0},
                                    {-0.2, -0.1, -1.0},
                                    {-0.4, -0.4, -1.0}},
                                   0.9,
                                   0.9,
                                   0.1,
                                   {1.0, 1.0, 0.0},
                                   {1.0, 1.0, 1.0},
                                   32.0,
                                   0.0,
                                   0.0);

    polygon triforceTop = polygon({{0.2, -0.1, -1.0},
                                   {0.0, 0.2, -1.0},
                                   {-0.2, -0.1, -1.0}},
                                  0.9,
                                  0.9,
                                  0.1,
                                  {1.0, 1.0, 0.0},
                                  {1.0, 1.0, 1.0},
                                  32.0,
                                  0.0,
                                  0.0);

    objects.add(make_shared<sphere>(refractiveSphere));
    objects.add(make_shared<polygon>(triforceRight));
    objects.add(make_shared<polygon>(triforceLeft));
    objects.add(make_shared<polygon>(triforceTop));

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