#include "scene.h"

scene refraction() {

    hittable_list objects;
    // refractive sphere
    sphere refractiveSphere = sphere({0.0, 0.0, 0.0},
                                     0.1,
                                     0.8,
                                     0.5,
                                     0.5,
                                     {0.75, 0.75, 0.9},
                                     {1.0, 1.0, 1.0},
                                     10.0,
                                     0.0,
                                     1.5);

//    polygon triforceRight = polygon({{0.4, -0.4, 0.0},
//                                     {0.2, -0.1, 0.0},
//                                     {0.0, -0.4, 0.0}},
//                                    0.9,
//                                    0.9,
//                                    0.1,
//                                    {1.0, 1.0, 0.0},
//                                    {1.0, 1.0, 1.0},
//                                    32.0,
//                                    0.0,
//                                    0.0);
//
//    polygon triforceLeft = polygon({{0.0, -0.4, 0.0},
//                                    {-0.2, -0.1, 0.0},
//                                    {-0.4, -0.4, 0.0}},
//                                   0.9,
//                                   0.9,
//                                   0.1,
//                                   {1.0, 1.0, 0.0},
//                                   {1.0, 1.0, 1.0},
//                                   32.0,
//                                   0.0,
//                                   0.0);
//
    polygon groundPoly = polygon({{1.0, -1.0, 0.0}, // right
                                   {1.0, 0.2, -5.0}, // top
                                   {-1.0, -1.0, -0.0}}, // left
                                  0.9,
                                  0.9,
                                  0.1,
                                  {0.0, 1.0, 0.0},
                                  {1.0, 1.0, 1.0},
                                  32.0,
                                  0.0,
                                  0.0);
    sphere groundSphere = sphere({0.0, -10000.5, 0.0},
                               10000.0,
                               0.9,
                               0.0,
                               0.1,
                               {0.0, 1.0, 0.0},
                               {1.0, 1.0, 1.0},
                               16.0,
                               0.0,
                               0.0);

    objects.add(make_shared<sphere>(refractiveSphere));
    objects.add(make_shared<sphere>(groundSphere));
//    objects.add(make_shared<polygon>(groundPoly));
//    objects.add(make_shared<polygon>(triforceRight));
//    objects.add(make_shared<polygon>(triforceLeft));
//    objects.add(make_shared<polygon>(triforceTop));

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