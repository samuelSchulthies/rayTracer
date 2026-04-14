#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "scenes/scene.h"
#include "utility.h"
#include "bvh.h"

#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

scene scn = refraction();

bool isInShadow = false;
int maxReflectionDepth = 3;
int currentReflectionDepth = 0;

// TODO: goals:
// TODO: - multi sampling DONE
// TODO: - refraction DONE?
// TODO: - AABB
// TODO: - obj importing
// extras:
// TODO: - texture mapping
// TODO: - DoF
// TODO: - Metalness
// TODO: - Point light

color shadow(vec3 minNormal, double minT, ray r);
color reflection(vec3 currentNormal, ray r, double currentT);
color refraction(vec3 currentNormal, ray r, double currentT, auto object);

color ray_color(const ray& r) {
    auto objects = scn.objects;
//    objects = hittable_list(make_shared<bvh_node>(objects));

    double currentT = numeric_limits<double>::infinity();
    vec3 currentNormal;
    double minT = numeric_limits<double>::infinity();
    unsigned int indexMinT = 0;
    vec3 minNormal;

    bool hitObject = false;
    bool drawObject = false;

    color shadowColor;
    color reflectionColor;
    color transmissionColor;

    for (unsigned int i = 0; i < scn.objects.getSize(); i++) {

        auto object= scn.objects.getObject(i);

        if (scn.objects.getObject(i)->hit(r)) {
            currentNormal = object->getNormal();
            currentT = object->getT();

            //TODO: redundant code, refactor
            hit_record rec;
            rec.normal = currentNormal;
            rec.t = currentT;

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
        if (hitObject && !r.shadowRay()){
            if (currentT < minT){
                minT = currentT;
                minNormal = currentNormal;
                indexMinT = i;
            }
        }
    }

    auto object= scn.objects.getObject(indexMinT);

    if (drawObject && object->getRefl() == 0 && object->getRefractIndex() == 0 && !r.shadowRay()) {
        shadowColor = shadow(minNormal, minT, r);
    }

    if (drawObject && isInShadow){
        isInShadow = false;
        return shadowColor;
    }

    if (drawObject && object->getRefl() > 0 && currentReflectionDepth < maxReflectionDepth && !r.shadowRay()) {
        reflectionColor = reflection(currentNormal, r, currentT);
    }

    if (drawObject && object->getRefractIndex() > 0 && !r.transmissionRay() && !r.shadowRay()){
        return refraction(currentNormal, r, currentT, object);
    }

    if (drawObject && !r.shadowRay()){ // don't think I need extra shadow ray check here
        color pixelColor = object->shade(r, scn.directionToLight, scn.ambientLight, scn.lightColor, minT, minNormal) +
               reflectionColor * object->getRefl();
        return pixelColor;
    }

    return color(scn.backgroundColor);
}

color shadow(vec3 minNormal, double minT, ray r){
    vec3 offset = minNormal * 0.001;
    vec3 shadowRayOrigin = r.at(minT) + offset;
    vec3 shadowRayDirection = unit_vector(scn.directionToLight); // only subtract from ray hit if point light
    ray shadowRay(shadowRayOrigin, shadowRayDirection, 1.0003);
    shadowRay.setIsShadowRay(true);
    return ray_color(shadowRay);
}

color reflection(vec3 currentNormal, ray r, double currentT){
    currentReflectionDepth++;

    vec3 offset = currentNormal * 0.001;
    vec3 reflectionRayOrigin = r.at(currentT) + offset;

    vec3 reflectionRayDirection = unit_vector(unit_vector(r.direction()) - (2 * currentNormal * dot(unit_vector(r.direction()), currentNormal)));

    ray reflectionRay(reflectionRayOrigin, reflectionRayDirection, 1.0003);
    reflectionRay.setIsReflectionRay(true);

    currentReflectionDepth--;

    return ray_color(reflectionRay);
}

color refraction(vec3 currentNormal, ray r, double currentT, auto object){
    vec3 offset = currentNormal * -0.001;
    vec3 transmissionRayOrigin = r.at(currentT) + offset;

    double n1 = r.getRefractIndex();
    double n2 = object->getRefractIndex();
    double quotient = n1 / n2;
    double cosTheta = fmin(dot(unit_vector(-r.direction()), currentNormal), 1.0);

    vec3 rPerp = quotient * (unit_vector(r.direction()) + cosTheta * currentNormal);
    vec3 rParallel = -currentNormal * sqrt(fabs(1.0 - rPerp.length_squared()));
    vec3 transmissionRayDirection = rPerp + rParallel;

    ray transmissionRay(transmissionRayOrigin, transmissionRayDirection, object->getRefractIndex());
    transmissionRay.setIsTransmissionRay(true);

    return ray_color(transmissionRay);
}

void multiSample(vec3 pixel00_loc, ofstream& outputImage, double i, double j, vec3 pixel_delta_u, vec3 pixel_delta_v){
    vec3 pixelSum;
    int sampleAmount = 1;

    if (sampleAmount == 1){
        auto pixelCenter = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
        auto ray_direction = pixelCenter - scn.cameraLookFrom;
        ray r(scn.cameraLookFrom, ray_direction, 1.0003);
        return write_color(outputImage, ray_color(r));
    }

    for (unsigned int k = 0; k < sampleAmount; k++) {
        vec3 offset = vec3(randomDouble() + 0.5, randomDouble() + 0.5, 0.0);
        vec3 jitteredRay = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

        auto ray_direction = jitteredRay - scn.cameraLookFrom;
        ray r(scn.cameraLookFrom, ray_direction, 1.0003);

        pixelSum += ray_color(r);
    }
    pixelSum /= sampleAmount;
    write_color(outputImage, pixelSum);
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
    auto viewport_upper_left = scn.cameraLookAt - scn.cameraLookFrom - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    //-----------------------------------------------------------------------------------------------------------------

    // Render
    //-----------------------------------------------------------------------------------------------------------------
    /*

     */
    ofstream outputImage("../image.ppm");

    if(!outputImage.is_open()){
        cout << "Error opening output file";
        return 0;
    }

    outputImage << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        clog << "\rScanLines remaining: " << (image_height - j) << ' ' << flush;
        for (int i = 0; i < image_width; i++) {
            multiSample(pixel00_loc, outputImage, i, j, pixel_delta_u, pixel_delta_v);
        }
    }
    outputImage.close();
    clog << "\rDone.                   \n";
    //-----------------------------------------------------------------------------------------------------------------
}