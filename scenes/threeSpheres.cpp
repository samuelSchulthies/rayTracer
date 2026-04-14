#include "scene.h"

scene threeSpheres() {
    hittable_list objects;

    sphere whiteSphere = sphere({0.45, 0.0, -0.15},
                                0.15,
                                0.8,
                                0.1,
                                0.3,
                                {1.0, 1.0, 1.0},
                                {1.0, 1.0, 1.0},
                                4.0,
                                0.0,
                                0.0);

    sphere redSphere = sphere({0.0, 0.0, -0.1},
                              0.2,
                              0.6,
                              0.3,
                              0.1,
                              {1.0, 0.0, 0.0},
                              {1.0, 1.0, 1.0},
                              32.0,
                              0.0,
                              0.0);

    sphere greenSphere = sphere({-0.60, 0.0, 0.0},
                                0.3,
                                0.7,
                                0.2,
                                0.1,
                                {0.0, 1.0, 0.0},
                                {0.5, 1.0, 0.5},
                                64.0,
                                0.0,
                                0.0);

    sphere blueSphere = sphere({0.0, -10000.5, 0.0},
                                 10000.0,
                                 0.9,
                                 0.0,
                                 0.1,
                                 {0.0, 0.0, 1.0},
                                 {1.0, 1.0, 1.0},
                                 16.0,
                                 0.0,
                                 0.0);

    objects.add(make_shared<sphere>(whiteSphere));
    objects.add(make_shared<sphere>(redSphere));
    objects.add(make_shared<sphere>(greenSphere));
    objects.add(make_shared<sphere>(blueSphere));

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