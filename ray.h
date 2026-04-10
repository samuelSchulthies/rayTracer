#pragma once

#include "vec3.h"

#include <random>

class ray {
public:
    ray() {}

    ray(const point3& origin, const vec3& direction, const double& refractIndex)
    :
    orig(origin), dir(direction), refractIndex(refractIndex) {}

    const point3& origin() const {
        return orig;
    }
    const vec3& direction() const {
        return dir;
    }

    point3 at(double t) const {
        return orig + t*dir;
    }

    bool shadowRay() const {
        return isShadowRay;
    }

    bool reflectionRay() const {
        return isReflectionRay;
    }

    bool transmissionRay() const {
        return isTransmissionRay;
    }

    double getRefractIndex() const {
        return refractIndex;
    }

    void setIsShadowRay(bool shadow){
        isShadowRay = shadow;
    }

    void setIsReflectionRay(bool reflection){
        isReflectionRay = reflection;
    }

    void setIsTransmissionRay(bool transmission){
        isTransmissionRay = transmission;
    }

    void setRefractIndex(bool index){
        refractIndex = index;
    }

private:
    point3 orig;
    vec3 dir;
    bool isShadowRay = false;
    bool isReflectionRay = false;
    bool isTransmissionRay = false;
    double refractIndex;
};