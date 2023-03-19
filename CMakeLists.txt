cmake_minimum_required(VERSION 3.23)
project(raytracing)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
    src/main.cpp
	src/colour.cpp
	src/sphere.cpp
	src/hittable_group.cpp
	src/camera.cpp
	src/constants.cpp
	src/lambertian.cpp
	src/metal.cpp
	src/dielectric.cpp
	src/solid_texture.cpp
	src/plane.cpp
)
