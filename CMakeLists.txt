cmake_minimum_required(VERSION 2.6)

project(TSP)

find_package(PkgConfig)

pkg_check_modules(GTK+ gtk+-2.0)

set(LIBRARY_OUTPUT_PATH lib)

link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(include
                    ${GTKMM_INCLUDE_DIRS})

add_library(matrice SHARED src/matrice/matrice.c)
add_library(graphe SHARED src/graphe/graphe.c)

add_executable(src/testTSP 
               src/testTSP.c
               src/heuristique/heuristiqueMatrice.c)

TARGET_LINK_LIBRARIES(src/testTSP matrice graphe ${GTKMM_LIBRARIES})