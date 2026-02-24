#include "vec3.h"
#include "color.h"

#include <iostream>

using namespace std;

int main() {
    // Image
    int imageWidth = 256;
    int imageHeight = 256;

    // Render
    cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int i = 0; i < imageHeight; i++){
        clog << "\rScanLines remaining: " << (imageHeight - i) << ' ' << flush;
        for (int j = 0; j < imageWidth; j++){
            auto pixel_color = color(double(i) / (imageWidth - 1), double(j) / (imageHeight - 1), 1);
            write_color(cout, pixel_color);
        }
    }

    clog << "\rDone.                   \n";
}