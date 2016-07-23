cmake_minimum_required(VERSION 2.6)
project(ConstrainedTypes)

include("testing.cmake")

include("compil-option.cmake")

include("doxygen.cmake")

include("config.cmake")

set(SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCDIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SRC ${SRCDIR}/*.cpp)

include_directories("${INCDIR}")

set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} ${LIBS})

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
