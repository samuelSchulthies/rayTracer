cmake_minimum_required(VERSION 3.30)
project(rayTracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(rayTracer main.cpp scenes/fushigi.cpp scenes/magentaSphere.cpp scenes/penetration.cpp
        scenes/spiralSpheres.cpp scenes/threeSpheres.cpp hitSphere.cpp hitPolygon.cpp)
