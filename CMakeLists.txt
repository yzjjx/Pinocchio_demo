cmake_minimum_required(VERSION 3.16)
project(pinocchio_demo LANGUAGES CXX)

find_package(pinocchio REQUIRED)

add_executable(ABA_with_urdf src/ABA_with_urdf.cpp)
target_compile_features(ABA_with_urdf PRIVATE cxx_std_17)
target_link_libraries(ABA_with_urdf PRIVATE pinocchio::pinocchio)
