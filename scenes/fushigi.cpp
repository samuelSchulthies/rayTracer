#include "scene.h"

scene fushigi() {
    sphere reflectiveSphere({0.0, 0.3, -1.0},
                       0.25,
                       0.0,
                       0.1,
                       0.1,
                       {0.75, 0.75, 0.75},
                       {1.0, 1.0, 1.0},
                       10.0,
                       0.9);
    polygon blueTriangle({{0.0, -0.7, -0.5},
                                  {1.0, 0.4, -1.0},
                                  {0.0, -0.7, -1.5}},
                         0.9,
                         1.0,
                         0.1,
                         {0.0, 0.0, 1.0},
                         {1.0, 1.0, 1.0},
                         4.0,
                         0.0);
    polygon yellowTriangle({{0.0, -0.7, -0.5},
                                    {0.0, -0.7, -1.5},
                                    {-1.0, 0.4, -1.0}},
                         0.9,
                         1.0,
                         0.1,
                         {1.0, 1.0, 0.0},
                         {1.0, 1.0, 1.0},
                         4.0,
                         0.0);

    return scene(1.0,
                 vec3(0, 0, 0),
                 vec3(0,0,0),
                 vec3(0, 1, 0),

                 vec3(1.0, 0.0, 0.0),
                 vec3(1.0, 1.0, 1.0),
                 vec3(0.1, 0.1, 0.1),
                 vec3(0.2, 0.2, 0.2),

                 vector<sphere>{reflectiveSphere},
                 vector<polygon>{blueTriangle, yellowTriangle});
}