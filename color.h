#pragma once

#include "vec3.h"

#include <iostream>
#include <fstream>

using namespace std;
using color = vec3;

inline void write_color(ofstream& image, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // clamp values
    if (pixel_color.x() > 1){
        r = 1;
    }
    if (pixel_color.x() < 0){
        r = 0;
    }

    if (pixel_color.y() > 1){
        g = 1;
    }
    if (pixel_color.y() < 0){
        g = 0;
    }

    if (pixel_color.z() > 1){
        b = 1;
    }
    if (pixel_color.z() < 0){
        b = 0;
    }

    // translate from 0-1 to 0-255
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // write pixel color components

    image << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}