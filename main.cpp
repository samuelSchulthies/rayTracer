#include "vec3.h"
#include "color.h"
#include "ray.h"

#include <iostream>
#include <algorithm>

using namespace std;

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

//    if (discriminant < 0) {
//        return -1.0;
//    } else {
//        return (-b - std::sqrt(discriminant) ) / (2.0*a);
//    }

    if (discriminant >= 0){
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
    return -1.0;
}

color ray_color(const ray& r) {
    /*
    This function takes in a ray and sends it to our hit function to see if that ray intersects a provided sphere,
    represented by point3 with a given radius. If it returns true, we hit the sphere and it colors that pixel purple
    in our ppm file.

    If it does not return true, we return grey for the background. Commented out code was for interpolating across the
    background for a gradient

     */
    vec3 directionToLight(0.0, 1.0, 0.0);
    vec3 lightColor(1.0, 1.0, 1.0);
    vec3 ambientLight(0.0, 0.0, 0.0);
    vec3 backgroundColor(0.2, 0.2, 0.2);
    vec3 sphere1(0.0, 0.0, 0.0);

    double t = hit_sphere(sphere1, 0.4, r);

    if (t > 0.0) {
        vec3 normal = unit_vector(r.at(t) - sphere1);

        // uncomment to check normals
//         return 0.5*color(normal.x()+1, normal.y()+1, normal.z()+1);

        double k_diffuse = 0.7;
        double k_specular = 0.2;
        double k_ambient = 0.1;
        vec3 Od(1.0, 0.0, 1.0);
        vec3 Os(1.0, 1.0, 1.0);
        double k_gls = 16.0;

        double n_dot_l = max(dot(normal, directionToLight), 0.0);
        vec3 reflection = (2 * n_dot_l * normal) - directionToLight;

        vec3 ambient = k_ambient * ambientLight * Od;
        vec3 diffuse = k_diffuse * lightColor * Od * n_dot_l;
        vec3 specular = k_specular * lightColor * Os * (pow(max(dot(r.origin(), reflection), 0.0), k_gls));

        vec3 lightTotal = ambient + diffuse + specular;

        return color(lightTotal);
    }
    return color(backgroundColor);


//    vec3 unit_direction = unit_vector(r.direction());
//    auto a = 0.5 * (unit_direction.y() + 1.0);
//    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
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
    Here we
     */
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);

    auto focal_length = 1.0;
    auto cameraLookAt = point3(0, 0, 0);
    auto cameraLookFrom = point3(0,0,focal_length);
    auto cameraLookUp = point3(0, 1, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges
    auto viewport_u = vec3(viewport_width, 0,0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // calculate the horizontal and vertical delta vectors from pixel to pixel
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel
    auto viewport_upper_left = cameraLookAt - cameraLookFrom - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);


    // Render
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
}