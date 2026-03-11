#include "hittable.h"

tuple<int, vec3> hitPolygon(const vector<vec3>& vertices, const ray& ray) {
    int numCrossings;
    int signHolder;
    int nextSignHolder;

    // get vectors of 2 sides
    vec3 vector1 = vertices[0] - vertices[1];
    vec3 vector2 = vertices[2] - vertices[1];

    // get plane normal
    vec3 planeNormal = cross(vector1, vector2);
    double d = -(vertices[0].x() * planeNormal.x() + vertices[0].y() * planeNormal.y() + vertices[0].z() * planeNormal.z());
    double t = -(dot(planeNormal, ray.origin()) + d) / dot(planeNormal, ray.direction());

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
                double ucross = (translatedVertices.at(i).u() - translatedVertices.at(i_1).v()) *
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
    return tuple<int, vec3>{numCrossings, planeNormal};
}
