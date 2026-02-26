#pragma once

#include "vec3.h"

class sphere {
public:
    sphere() {}
    sphere(const vec3& center, const double& radius,
           const double& Kd, const double& Ks, const double& Ka,
           const vec3& Od, const vec3& Os,
           const double& Kgls)
           :
           center(center), radius(radius), Kd(Kd), Ks(Ks), Ka(Ka), Od(Od), Os(Os), Kgls(Kgls) {}

    vec3 getCenter() const{
        return center;
    }
    double getRadius() const{
        return radius;
    }
    double getKd() const{
        return Kd;
    }
    double getKs() const{
        return Ks;
    }
    double getKa() const{
        return Ka;
    }
    vec3 getOd() const{
        return Od;
    }
    vec3 getOs() const{
        return Os;
    }
    double getKgls() const{
        return Kgls;
    }
private:
    vec3 center;
    double radius;
    double Kd;
    double Ks;
    double Ka;
    vec3 Od;
    vec3 Os;
    double Kgls;
};