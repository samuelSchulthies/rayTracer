#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"

#include <iostream>
#include <algorithm>

using namespace std;

// Scene
double focal_length = 1.0;
vec3 cameraLookAt = point3(0, 0, 0);
vec3 cameraLookFrom = point3(0,0,focal_length);
vec3 cameraLookUp = point3(0, 1, 0);

vec3 directionToLight(0.0, 1.0, 1.0);
vec3 lightColor(1.0, 1.0, 1.0);
vec3 ambientLight(0.1, 0.1, 0.1);
vec3 backgroundColor(0.2, 0.2, 0.2);

vec3 computePhong(sphere sphere, ray ray, double t);

vector<sphere> buildSpheresTest3(){
    vector<sphere> spheres;
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double radius = 0.2;
    double r = 0.3;
    double g = 0.6;
    double b = 1.0;
    double angle = 0.0;
    for(int i = 0; i < 9; i++) {
        spheres.push_back(sphere({x, y, z},
                                 radius,
                                 0.8,
                                 0.1,
                                 0.3,
                                 {r, g, b},
                                 {1.0, 1.0, 1.0},
                                 4.0));
        angle += 1.0;
        x += cos(angle) * radius;
        y += sin(angle) * radius;
        z -= 0.05;
        radius -= 0.025;
        r -= 0.05;
        g += 0.05;
        b -= 0.05;
    }
    return spheres;
}

vector<sphere> buildSpheresTest2(){
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
    sphere greenSphere({-0.6, 0.0, 0.0},
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

    return vector<sphere>{whiteSphere, redSphere, greenSphere, blueSphere};

}

// place a sphere
double hit_sphere(const point3& center, double radius, const ray& r) {
    /*
    This uses the quadratic formula to calculate if the ray hits the sphere. Returns true if the discriminant of the
    formula is greater than or equal to 0, meaning we have 1 or two solutions. If it returns less than 0, we are not
    intersecting the sphere and return false.
    */
    vec3 rayToSphere = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), rayToSphere);
    auto c = dot(rayToSphere, rayToSphere) - radius*radius;
    auto discriminant = b*b - 4*a*c;

    if (discriminant >= 0){
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
    return -1.0;
}

color ray_color(const ray& ray) {
    /*
    This function takes in a ray and sends it to our hit function to see if that ray intersects a provided sphere,
    represented by point3 with a given radius. If it returns true, we hit the sphere and it colors that pixel purple
    in our ppm file.

    If it does not return true, we return grey for the background. Commented out code was for interpolating across the
    background for a gradient

     */
    for (sphere sphere : buildSpheresTest3()){
        double t = hit_sphere(sphere.getCenter(), sphere.getRadius(), ray);
        if (t > 0.0){
            return computePhong(sphere, ray, t);
        }
    }
    return color(backgroundColor);

//    vec3 unit_direction = unit_vector(ray.direction());
//    auto a = 0.5 * (unit_direction.y() + 1.0);
//    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

vec3 computePhong(sphere sphere, ray ray, double t){

    vec3 normal = unit_vector(ray.at(t) - sphere.getCenter());

    // uncomment to check normals
    // return 0.5*color(normal.x()+1, normal.y()+1, normal.z()+1);

    double n_dot_l = max(dot(normal, unit_vector(directionToLight)), 0.0);
    vec3 reflection = unit_vector((2 * n_dot_l * normal) - directionToLight); // This made spec show up but spec is wrong

    vec3 ambient = sphere.getKa() * ambientLight * sphere.getOd();
    vec3 diffuse = sphere.getKd() * lightColor * sphere.getOd() * n_dot_l;
    vec3 specular = sphere.getKs() * lightColor * sphere.getOs() * (pow(max(dot(ray.origin(), reflection), 0.0), sphere.getKgls()));

    vec3 lightTotal = ambient + diffuse + specular;

    return color(lightTotal);
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
    auto viewport_upper_left = cameraLookAt - cameraLookFrom - viewport_u/2 - viewport_v/2;
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
            auto ray_direction = pixel_center - cameraLookFrom;
            ray r(cameraLookFrom, ray_direction);

            color pixel_color = ray_color(r);
            write_color(cout, pixel_color);
        }
    }

    clog << "\rDone.                   \n";
    //-----------------------------------------------------------------------------------------------------------------
}