#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "scenes/scene.h"

#include <iostream>
#include <algorithm>

using namespace std;

scene scene = fushigi();

bool isInShadow = false;
int maxReflectionDepth = 3;
int currentReflectionDepth = 0;
int returns = 0;

color ray_color(const ray& r) {
    auto objects = scene.objects;
    // loop over every object in the scene (triangles, spheres)
    unsigned int indexMinT = 0;
    double minT = numeric_limits<double>::infinity();

    bool hitObject = false;
    bool drawObject = false;
    color shadowColor;
    color reflectionColor = color(0.0, 0.0, 0.0);
    for (unsigned int i = 0; i < scene.objects.size(); i++) {

        auto object= scene.objects.at(i);

        if (scene.objects[i]->hit(r)) {
            drawObject = true;
            hitObject = true;
        }
        else {
            hitObject = false;
        }
        if (hitObject && r.shadowRay()) {
            isInShadow = true;
            return color(0.0,0.0,0.0);
        }
//        if (hitObject && r.reflectionRay()) {
//            return scene.objects[i]->computePhong(r, scene.directionToLight, scene.ambientLight, scene.lightColor);
//        }
        if (hitObject && !r.shadowRay()){
            if (object->getT() < minT){
                minT = object->getT();
                indexMinT = i;
            }
        }
    }

//    auto closestObject= scene.objects[indexMinT];

    if (drawObject) {
        vec3 offset = scene.objects[indexMinT]->getNormal() * 0.0001;
        vec3 shadowRayOrigin = r.at(scene.objects[indexMinT]->getT()) + offset;
        vec3 shadowRayDirection = unit_vector(scene.directionToLight); // only subtract from ray hit if point light
        ray shadowRay(shadowRayOrigin, shadowRayDirection);
        shadowRay.setIsShadowRay(true);
        shadowColor = ray_color(shadowRay);
    }

    if (drawObject && scene.objects[indexMinT]->getRefl() > 0 && currentReflectionDepth < maxReflectionDepth) {
        currentReflectionDepth++;

        vec3 normal = scene.objects[indexMinT]->getNormal();
        vec3 offset = normal * 0.0001;
        vec3 reflectionRayOrigin = r.at(scene.objects[indexMinT]->getT()) + offset;

        double n_dot_l;
        if (scene.objects[indexMinT]->getType() == "sphere"){
            n_dot_l = max(dot(normal, unit_vector(scene.directionToLight)), 0.0);
        }
        else {
            n_dot_l = dot(normal, unit_vector(scene.directionToLight));
        }

        vec3 reflectionRayDirection = unit_vector((2 * n_dot_l * normal) - unit_vector(scene.directionToLight));

        ray reflectionRay(reflectionRayOrigin, reflectionRayDirection);
        reflectionRay.setIsReflectionRay(true);
        reflectionColor += ray_color(reflectionRay);
        currentReflectionDepth--;

    }

    if (drawObject && isInShadow){
        isInShadow = false;
        return shadowColor;
    }

    if (drawObject && !r.shadowRay()){
        color pixelColor = scene.objects[indexMinT]->computePhong(r, scene.directionToLight, scene.ambientLight, scene.lightColor) +
               reflectionColor * scene.objects[indexMinT]->getRefl();
        return pixelColor;
    }

    return color(scene.backgroundColor);
}

int main() {
    // Image:
    //-----------------------------------------------------------------------------------------------------------------
    /*
    Here we define the dimensions of the output image. We set an aspect ratio with a given width. From there we can
    determine the height of the image. Image height must at least be 1 and whole number. We can't have fractions
    of a pixel
     */
    auto aspect_ratio = 1.0 / 1.0;
    int image_width = 500;

    // calculate image height and ensure it is 1 or greater
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    //-----------------------------------------------------------------------------------------------------------------

    // Camera
    //-----------------------------------------------------------------------------------------------------------------
    /*
    Here we set up the viewport for the camera and a focal length. Together these give the field of view. We
    calculate vector for the horizontal and vertical axis of the viewport, then we calculate an offset to get the
    middle of the pixel. We then start from the middle of the upper left pixel.
     */
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);

    // Calculate the vectors across the horizontal and down the vertical viewport edges
    auto viewport_u = vec3(viewport_width, 0,0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // calculate the horizontal and vertical delta vectors from pixel to pixel
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel
    auto viewport_upper_left = scene.cameraLookAt - scene.cameraLookFrom - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    //-----------------------------------------------------------------------------------------------------------------

    // Render
    //-----------------------------------------------------------------------------------------------------------------
    /*

     */
    cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++){
        clog << "\rScanLines remaining: " << (image_height - j) << ' ' << flush;
        for (int i = 0; i < image_width; i++){
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - scene.cameraLookFrom;
            ray r(scene.cameraLookFrom, ray_direction);

            color pixel_color = ray_color(r);
            write_color(cout, pixel_color);

            returns++;
            if (returns == 129){
                int yell;
            }
        }
    }

    clog << "\rDone.                   \n";
    //-----------------------------------------------------------------------------------------------------------------
}