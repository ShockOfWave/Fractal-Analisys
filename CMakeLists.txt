cmake_minimum_required(VERSION 3.5)

project(lacunarity)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Список всех файлов .cpp в папке lib/source
file(GLOB SOURCE_FILES_CPP lib/source/*.cpp)

# Список всех файлов .h в папке lib/include
file(GLOB HEADER_FILES_H lib/include/*.h)

include_directories(lib/include)
aux_source_directory(lib/source SOURCES)

find_package(GSL REQUIRED)

include_directories(${GSL_INCLUDE_DIR})
include_directories(/lib/include)

add_library(lacunarity SHARED ${SOURCE_FILES_CPP} ${HEADER_FILES_H})


target_link_libraries(lacunarity PRIVATE ${GSL_LIBRARY})

