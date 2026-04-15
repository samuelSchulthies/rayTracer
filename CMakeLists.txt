cmake_minimum_required(VERSION 3.30)
project(rayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rayTracer main.cpp scenes/fushigi.cpp scenes/magentaSphere.cpp scenes/penetration.cpp
        scenes/spiralSpheres.cpp scenes/threeSpheres.cpp scenes/tryforce.cpp scenes/refraction.cpp tinyobjloader/tiny_obj_loader.cpp)
