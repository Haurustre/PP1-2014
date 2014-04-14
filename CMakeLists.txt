cmake_minimum_required(VERSION 2.6)

project(TSP)

find_package(PkgConfig)

pkg_check_modules(GTK gtk+-2.0)

set(LIBRARY_OUTPUT_PATH lib)

link_directories(${GTK_LIBRARY_DIRS})

include_directories(include
                    ${GTK_INCLUDE_DIRS})

add_library(matrice SHARED src/matrice/matrice.c)
add_library(graphe SHARED src/graphe/graphe.c)

add_executable(src/testTSP 
               src/testTSP.c
               src/heuristique/heuristiqueMatrice.c
	       src/mst/mst.c
	       src/brutForce/brutForce.c)
	       #src/rechercheExhaustive/rechercheExhaust.c


TARGET_LINK_LIBRARIES(src/testTSP matrice graphe ${GTK_LIBRARIES})



# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)