cmake_minimum_required(VERSION 2.6)

project(TSP)

set(LIBRARY_OUTPUT_PATH lib)
include_directories(include)

add_library(matrice SHARED src/matrice/matrice.c)
add_library(graphe SHARED src/graphe/graphe.c)

add_executable(src/testTSP 
               src/testTSP.c
               src/heuristique/heuristiqueMatrice.c)

TARGET_LINK_LIBRARIES(src/testTSP matrice graphe)