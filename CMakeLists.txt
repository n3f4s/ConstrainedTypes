cmake_minimum_required(VERSION 2.6)
project(ConstrainedTypes)

#TODO : faire les tests
#TODO : changer les répertoires de création des bins

set(SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB SRC ${SRCDIR}/*.cpp)
#message("srcs : ${SRC}")

include_directories("${PROJECT_BINARY_DIR}/include")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wshadow -std=c++1y -pipe -fdiagnostics-color=auto")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -g -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -O2 -DNDEBUG")

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES *.o)
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES *.so)

add_executable(${PROJECT_NAME} ${SRC})

set(LIBS)
set(EXEC_NAME ${PROJECT_NAME})
if(CMAKE_BUILD_TYPE EQUAL Debug)
    set(EXEC_NAME "${EXEC_NAME}_debug")
endif(CMAKE_BUILD_TYPE EQUAL Debug)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)

target_link_libraries(${PROJECT_NAME} ${LIBS})
target_link_libraries(${PROJECT_NAME} ${LIBS})

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
