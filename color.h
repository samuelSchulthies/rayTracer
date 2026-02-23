#pragma once

#include "vec3.h"

#include <iostream>

using namespace std;
using color = vec3;

void write_color(ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // translate from 0-1 to 0-255
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // write pixel color components
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}