#include "scene.h"

scene magentaSphere() {
    hittable_list objects;

    sphere magenta = sphere({0.0, 0.0, 0.0},
                                0.4,
                                0.7,
                                0.2,
                                0.1,
                                {1.0, 0.0, 1.0},
                                {1.0, 1.0, 1.0},
                                16.0,
                                0.0,
                                0.0);
    objects.add(make_shared<sphere>(magenta));

    return scene(1.0,
                 vec3(0, 0, 0),
                 vec3(0,0,0),
                 vec3(0, 1, 0),

                 vec3(0.0, 1.0, 0.0),
                 vec3(1.0, 1.0, 1.0),
                 vec3(0.0, 0.0, 0.0),
                 vec3(0.2, 0.2, 0.2),

                 objects);
}