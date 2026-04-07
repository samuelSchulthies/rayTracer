#pragma once

#include "vec3.h"

#include <random>

class ray {
public:
    ray() {}

    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

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

    void setIsShadowRay(bool shadow){
        isShadowRay = shadow;
    }

    void setIsReflectionRay(bool reflection){
        isReflectionRay = reflection;
    }

    void setIsTransmissionRay(bool transmission){
        isTransmissionRay = transmission;
    }

private:
    point3 orig;
    vec3 dir;
    bool isShadowRay = false;
    bool isReflectionRay = false;
    bool isTransmissionRay = false;
};