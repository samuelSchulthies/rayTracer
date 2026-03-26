#pragma once

#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "shading.h"

#include <algorithm>

class sphere : public hittable{
public:
    sphere() {}
    sphere(const vec3& center, const double& radius,
           const double& Kd, const double& Ks, const double& Ka,
           const vec3& Od, const vec3& Os,
           const double& Kgls,
           const double& Refl)
           :
           center(center), radius(radius), Kd(Kd), Ks(Ks), Ka(Ka), Od(Od), Os(Os), Kgls(Kgls), Refl(Refl) {}

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
    double getRefl() const{
        return Refl;
    }

    double getT() override{
        return t;
    }

    vec3 getNormal() override {
        return normal;
    }

    virtual double getRefl() override {
        return Refl;
    }

    virtual string getType() override {
        return type;
    }
    double getCurrentT() override {
        return currentT;
    }
    vec3 getCurrentNorm () override {
        return currentNorm;
    }


    bool hit(const ray& r) override {
        vec3 rayToSphere = center - r.origin();
        auto a = dot(r.direction(), r.direction());
        auto b = -2.0 * dot(r.direction(), rayToSphere);
        auto c = dot(rayToSphere, rayToSphere) - radius*radius;
        auto discriminant = b*b - 4*a*c;

        double tFromHit = (-b - sqrt(discriminant)) / (2.0 * a);

        if (tFromHit <= 0){
            return false;
        }

        if (!r.shadowRay() && !r.reflectionRay()) {
            t = tFromHit;
            normal = unit_vector(r.at(t) - center);
        }
        currentT= tFromHit;
        currentNorm = unit_vector(r.at(currentT) - center);

        if (discriminant >= 0){
            return true;
        }

        return false;
    }

    vec3 shade(const ray& r, vec3 directionToLight, vec3 ambientLight, vec3 lightColor, double newT, vec3 newNorm) override {
        return shading().computePhong(type, r, directionToLight, ambientLight, lightColor, newT, newNorm, Kd, Ks, Ka, Od, Os, Kgls);
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
    double Refl;
    double t;
    vec3 normal;
    string type = "sphere";
    bool isInShadow = false;
    double currentT;
    vec3 currentNorm;
};