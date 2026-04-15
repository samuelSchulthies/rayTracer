#pragma once

#include "vec3.h"
#include "vec2.h"
#include "hittable.h"

class polygon : public hittable{
public:
    polygon() {}
    polygon(const vector<vec3>& vertices,
           const double& Kd, const double& Ks, const double& Ka,
           const vec3& Od, const vec3& Os,
           const double& Kgls,
           const double& Refl,
           const double& refractIndex)
           :
           vertices(vertices), Kd(Kd), Ks(Ks), Ka(Ka), Od(Od), Os(Os), Kgls(Kgls), Refl(Refl), refractIndex(refractIndex) {}

    vector<vec3> getVertices() const{
        return vertices;
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

    double getRefl() override {
        return Refl;
    }

    virtual double getRefractIndex() override {
        return refractIndex;
    }

    string getType() override {
        return type;
    }


    vec3 shade(const ray& r, vec3 directionToLight, vec3 ambientLight, vec3 lightColor, double newT, vec3 newNorm) override {
        return shading().computePhong(type, r, directionToLight, ambientLight, lightColor, newT, newNorm, Kd, Ks, Ka, Od, Os, Kgls);
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) override {
        bool hitPoly = hitPolygon(r);

        if (t <= 0) {
            return false;
        }
        if (hitPoly) {
            return true;
        }
        return false;
    }

    aabb bounding_box() const override {
        return bbox;
    }

private:
    vector<vec3> vertices;
    double radius;
    double Kd;
    double Ks;
    double Ka;
    vec3 Od;
    vec3 Os;
    double Kgls;
    double Refl;
    double refractIndex;
    double t;
    vec3 normal;
    string type = "polygon";
    aabb bbox;

    bool hitPolygon(const ray& r) {
        // get vectors of 2 sides
        vec3 vector1 = vertices[0] - vertices[1];
        vec3 vector2 = vertices[1] - vertices[2];

        // get plane normal
        normal = unit_vector(cross(vector1, vector2));
        // get plane intersection
        double d = -(vertices[0].x() * normal.x() + vertices[0].y() * normal.y() + vertices[0].z() * normal.z());
        auto planeDotRay = dot(normal, r.direction());
        t = -(dot(normal, r.origin()) + d) / planeDotRay;

        // if ray is parallel or normal is pointing away, cull face. Excludes shadow rays
        if (planeDotRay >= 0 && !r.shadowRay()){
            return false;
        }

        // If intersection is behind ray, don't draw face
        if (t <= 0){
            return false;
        }

        vec3 P = r.at(t);

        vec3 edge0 = vertices[1] - vertices[0];
        vec3 edge1 = vertices[2] - vertices[1];
        vec3 edge2 = vertices[0] - vertices[2];

        vec3 C0 = P - vertices[0];
        vec3 C1 = P - vertices[1];
        vec3 C2 = P - vertices[2];

        if(dot(normal, cross(edge0, C0)) > 0 &&
           dot(normal, cross(edge1, C1)) > 0 &&
           dot(normal, cross(edge2, C2)) > 0) {
            return true;
        }
        else {
            return false;
        }
    }
};