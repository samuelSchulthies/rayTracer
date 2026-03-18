#pragma once

#include "../sphere.h"
#include "../polygon.h"

class scene {
public:
    scene() {}

    scene(const double &focalLength,
          const vec3 &cameraLookAt,
          const vec3 &cameraLookFrom,
          const vec3 &cameraLookUp,

          const vec3 &directionToLight,
          const vec3 &lightColor,
          const vec3 &ambientLight,
          const vec3 &backgroundColor,

          vector<hittable*> &objects)

          :

          focalLength(focalLength),
          cameraLookAt(cameraLookAt),
          cameraLookFrom(vec3(cameraLookFrom.x(), cameraLookFrom.y(), focalLength)),
          cameraLookUp(cameraLookUp),

          directionToLight(directionToLight),
          lightColor(lightColor),
          ambientLight(ambientLight),
          backgroundColor(backgroundColor),

          objects(objects)
          {}


    double focalLength;
    vec3 cameraLookAt;
    vec3 cameraLookFrom;
    vec3 cameraLookUp;

    vec3 directionToLight;
    vec3 lightColor;
    vec3 ambientLight;
    vec3 backgroundColor;

    vector<hittable*> objects;
};


scene magentaSphere();
scene threeSpheres();
scene spiralSpheres();

scene fushigi();
scene penetration();
scene complex();