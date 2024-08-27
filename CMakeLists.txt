cmake_minimum_required(VERSION 3.29)
project(Kuesto)

set(CMAKE_CXX_STANDARD 20)

add_executable(Kuesto run.cpp
        external/miniz/miniz.c external/miniz/miniz.h
        external/tinyxml2/tinyxml2.cpp external/tinyxml2/tinyxml2.h
        src/files/excel/XLSXtraction.cpp src/headers/excel/XLSXtraction.h
        src/files/excel/DataXLSXtraction.cpp src/headers/excel/DataXLSXtraction.h
        src/files/ListRandomizer.cpp src/headers/ListRandomizer.h
)
