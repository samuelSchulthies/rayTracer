#include "scene.h"

scene magentaSphere() {

    sphere sphere({0.0, 0.0, 0.0},
                          0.4,
                          0.7,
                          0.2,
                          0.1,
                          {1.0, 0.0, 1.0},
                          {1.0, 1.0, 1.0},
                          16.0,
                          0.0);

    vector<hittable*> objects = {&sphere};

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