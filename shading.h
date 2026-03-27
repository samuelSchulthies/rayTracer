#pragma once

#include "vec3.h"
#include "ray.h"

class shading {
public:
    shading() {}

    vec3 computePhong(string type, const ray& r, vec3 directionToLight, vec3 ambientLight, vec3 lightColor,
                      double newT, vec3 newNorm, double Kd, double Ks, double Ka, vec3 Od, vec3 Os, double Kgls) {        // uncomment to check normals
//        return 0.5*color(normal.x()+1, normal.y()+1, normal.z()+1);

        vec3 directionToCamera = unit_vector(r.origin() - r.at(newT));

        double n_dot_l = 0;
        if (type == "sphere") {
            n_dot_l = max(dot(newNorm, unit_vector(directionToLight)), 0.0);
        }
        else {
            n_dot_l = dot(newNorm, unit_vector(directionToLight));
        }
        vec3 reflection = unit_vector((2 * n_dot_l * newNorm) - unit_vector(directionToLight));

        vec3 ambient = Ka * ambientLight * Od;
        vec3 diffuse = Kd * lightColor * Od * n_dot_l;
        vec3 specular = Ks * lightColor * Os * (pow(max(dot(directionToCamera, reflection), 0.0), Kgls));

        vec3 lightTotal = ambient + diffuse + specular;

        return color(lightTotal);
    }
};