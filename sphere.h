#pragma once

#include "vec3.h"
#include "ray.h"
#include "hittable.h"

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
        currentNorm = unit_vector(r.at(t) - center);

        if (discriminant >= 0){
            return true;
        }

        return false;
    }

    vec3 computePhong(const ray& ray, vec3 directionToLight, vec3 ambientLight, vec3 lightColor) override {
        // uncomment to check normals
//        return 0.5*color(normal.x()+1, normal.y()+1, normal.z()+1);

        vec3 directionToCamera = unit_vector(ray.origin() - ray.at(t));

        double n_dot_l = max(dot(normal, unit_vector(directionToLight)), 0.0);
        vec3 reflection = unit_vector((2 * n_dot_l * normal) - unit_vector(directionToLight));

        vec3 ambient = Ka * ambientLight * Od;
        vec3 diffuse = Kd * lightColor * Od * n_dot_l;
        vec3 specular = Ks * lightColor * Os * (pow(max(dot(directionToCamera, reflection), 0.0), Kgls));

        vec3 lightTotal = ambient + diffuse + specular;

        return color(lightTotal);
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