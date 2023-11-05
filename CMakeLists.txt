cmake_minimum_required(VERSION 3.5)

project(gsl_operations)

# Список всех файлов .cpp в папке src/source
file(GLOB SOURCE_FILES_CPP src/source/*.cpp)

# Список всех файлов .h в папке src/include
file(GLOB HEADER_FILES_H src/include/*.h)

include_directories(src/include)
aux_source_directory(src/source SOURCES)

find_package(GSL REQUIRED)

find_package(Python3 COMPONENTS Development NumPy)

include_directories(${GSL_INCLUDE_DIR})
include_directories(/src/include)

add_library(lacunarity SHARED ${SOURCE_FILES_CPP} ${HEADER_FILES_H})

target_include_directories(lacunarity PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})

target_link_libraries(lacunarity PRIVATE Python3::Python Python3::NumPy)

target_link_libraries(lacunarity PRIVATE ${GSL_LIBRARY})

