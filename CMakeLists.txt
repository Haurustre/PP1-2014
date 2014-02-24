cmake_minimum_required(VERSION 2.8)

project(TSP)

set(LIBRARY_OUTPUT_PATH lib)
include_directories(include)

add_library(matrice STATIC src/matrice/matrice.c)
add_library(graphe STATIC src/graphe/graphe.c)

add_subdirectory(src)