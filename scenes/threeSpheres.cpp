#include "scene.h"

scene threeSpheres() {
    sphere whiteSphere({0.45, 0.0, -0.15},
                       0.15,
                       0.8,
                       0.1,
                       0.3,
                       {1.0, 1.0, 1.0},
                       {1.0, 1.0, 1.0},
                       4.0);
    sphere redSphere({0.0, 0.0, -0.1},
                     0.2,
                     0.6,
                     0.3,
                     0.1,
                     {1.0, 0.0, 0.0},
                     {1.0, 1.0, 1.0},
                     32.0);
    sphere greenSphere({-0.60, 0.0, 0.0},
                       0.3,
                       0.7,
                       0.2,
                       0.1,
                       {0.0, 1.0, 0.0},
                       {0.5, 1.0, 0.5},
                       64.0);
    sphere blueSphere({0.0, -10000.5, 0.0},
                      10000.0,
                      0.9,
                      0.0,
                      0.1,
                      {0.0, 0.0, 1.0},
                      {1.0, 1.0, 1.0},
                      16.0);

    return scene(1.0,
                 vec3(0, 0, 0),
                 vec3(0,0,0),
                 vec3(0, 1, 0),

                 vec3(1, 1, 1),
                 vec3(1.0, 1.0, 1.0),
                 vec3(0.1, 0.1, 0.1),
                 vec3(0.2, 0.2, 0.2),

                 vector<sphere>{whiteSphere, redSphere, greenSphere, blueSphere});
}