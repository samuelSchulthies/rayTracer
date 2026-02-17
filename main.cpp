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
            auto r = double(i) / (imageWidth - 1);
            auto g = double(j) / (imageHeight - 1);
            auto b = 1.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            cout << ir << ' ' << ig << ' ' << ib << "\n";
        }
    }

    clog << "\rDone.                   \n";


}