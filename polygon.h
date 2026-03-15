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
           const double& Refl)
           :
           vertices(vertices), Kd(Kd), Ks(Ks), Ka(Ka), Od(Od), Os(Os), Kgls(Kgls), Refl(Refl) {}

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

    vec3 computePhong(const ray& r, vec3 directionToLight, vec3 ambientLight, vec3 lightColor) {
        // uncomment to check normals
        // return 0.5*color(normal.x()+1, normal.y()+1, normal.z()+1);

        vec3 directionToCamera = unit_vector(r.origin() - r.at(t));

        double n_dot_l = dot(normal, unit_vector(directionToLight));
        vec3 reflection = unit_vector((2 * n_dot_l * normal) - unit_vector(directionToLight));

        vec3 ambient = Ka * ambientLight * Od;
        vec3 diffuse = Kd * lightColor * Od * n_dot_l;
        vec3 specular = Ks * lightColor * Os * (pow(max(dot(directionToCamera, reflection), 0.0), Kgls));

        vec3 lightTotal = ambient + diffuse + specular;

        return color(lightTotal);
    }

    bool hit(const ray& ray) override {
        tuple<int, double, vec3> hitPoly = hitPolygon(ray);
        int numCrossings = get<0>(hitPoly);
        t = get<1>(hitPoly);
        normal = get<2>(hitPoly);
        if (numCrossings % 2 != 0) {
            return true;
        }
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
    double t;
    vec3 normal;

    tuple<int, double, vec3> hitPolygon(const ray& ray) const {
        int numCrossings = 0;
        int signHolder = 0;
        int nextSignHolder = 0;

        // get vectors of 2 sides
        vec3 vector1 = vertices[0] - vertices[1];
        vec3 vector2 = vertices[1] - vertices[2];

        // get plane normal // TODO: check normals
        vec3 planeNormal = unit_vector(cross(vector1, vector2));

        // get plane intersection
        double d = -(vertices[0].x() * planeNormal.x() + vertices[0].y() * planeNormal.y() + vertices[0].z() * planeNormal.z());
        auto planeDotRay = dot(planeNormal, ray.direction());

        // if ray is parallel or normal is pointing away, cull face. Excludes shadow rays
        if (planeDotRay >= 0 && !ray.shadowRay()){
            return tuple<int, double, vec3>{numCrossings, 0, planeNormal};
        }
        double t = -(dot(planeNormal, ray.origin()) + d) / planeDotRay;

        // If intersection is behind ray, don't draw face
        if (t <= 0){
            return tuple<int, double, vec3>{numCrossings, t, planeNormal};
        }

//    if(vertices.size() == 3){
//        return hitTri(vertices, ray, vector1, vector2);
//    }

        // get dominant axis
        tuple<vec2, char> dominant = dominantProjection(planeNormal, 0);
        char dominantAxis = get<1>(dominant);

        // project vertices and ray to dominant axis
        vector<vec2> projectedVertices;
        for (unsigned int i = 0; i < vertices.size(); i++) {
            projectedVertices.push_back(get<0>(dominantProjection(vertices.at(i), dominantAxis)));
        }
        vec2 projectedRay = get<0>(dominantProjection(ray.at(t), dominantAxis));

        // translate vertices and ray by -ray
        vector<vec2> translatedVertices;
        vec2 translation = projectedRay;
        for (unsigned int i = 0; i < projectedVertices.size(); i++) {
            translatedVertices.push_back(projectedVertices.at(i) - translation);
        }
//    vec2 translatedRay = projectedRay - translation;


        // set initial sign holder and num crossings
        numCrossings = 0;
        if(translatedVertices.at(0).v() < 0){
            signHolder = -1;
        }
        else {
            signHolder = 1;
        }

        // loop over vertices
        for(unsigned int i = 0; i < translatedVertices.size(); i++){
            int i_1;
            if (i == translatedVertices.size() - 1){
                i_1 = 0;
            }
            else{
                i_1 = i + 1;
            }

            if(translatedVertices.at(i_1).v() < 0){
                nextSignHolder = -1;
            }
            else {
                nextSignHolder = 1;
            }
            if(signHolder != nextSignHolder){
                // crosses +U
                if ((translatedVertices.at(i).u() > 0) && (translatedVertices.at(i_1).u() > 0)){
                    numCrossings += 1;
                }
                    // might cross +U
                else if ((translatedVertices.at(i).u() > 0) || (translatedVertices.at(i_1).u() > 0)){
                    double ucross = translatedVertices.at(i).u() - translatedVertices.at(i).v() *
                            ((translatedVertices.at(i_1).u() - translatedVertices.at(i).u()) /
                            (translatedVertices.at(i_1).v() - translatedVertices.at(i).v()));
                    // crosses +U so increment
                    if (ucross > 0){
                        numCrossings += 1;
                    }
                }
            }
            signHolder = nextSignHolder;
        }
        return tuple<int, double, vec3>{numCrossings, t, planeNormal};
    }


};