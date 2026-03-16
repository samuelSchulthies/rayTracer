#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "scenes/scene.h"

#include <iostream>

using namespace std;

scene scene = fushigi();

bool isInShadow = false;

color ray_color(const ray& r) {
    auto objects = scene.objects;

    // loop over every object in the scene (triangles, spheres)
    for (unsigned int i = 0; i < scene.objects.size(); i++) {
        auto object= scene.objects.at(i);
        color shadowColor;
        bool hitObject = false;
        if (scene.objects[i]->hit(r)) {
            hitObject = true;
        }
        if (hitObject && !r.shadowRay()){
            vec3 offset = object->getNormal() * 0.0001;
            vec3 shadowRayOrigin = r.at(object->getT()) + offset;
            vec3 shadowRayDirection = unit_vector(scene.directionToLight); // only subtract from ray hit if point light
//            double test = dot(shadowRayDirection, scene.directionToLight);
            ray shadowRay(shadowRayOrigin, shadowRayDirection);
            shadowRay.setIsShadowRay(true);
            shadowColor = ray_color(shadowRay);
        }
        if (hitObject && r.shadowRay()) {
            isInShadow = true;
            return color(1.0,0.0,0.0);
        }
        if (hitObject && isInShadow){
            isInShadow = false;
            return shadowColor;
        }
        if (hitObject && !isInShadow && !r.shadowRay()){
            return scene.objects[i]->computePhong(r, scene.directionToLight, scene.ambientLight, scene.lightColor);
        }
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
        }
    }

    clog << "\rDone.                   \n";
    //-----------------------------------------------------------------------------------------------------------------
}