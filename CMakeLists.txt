cmake_minimum_required(VERSION 3.27)
project(A_Bugs_Life_Jake_O_Reilly_CA2)

set(CMAKE_CXX_STANDARD 17)

add_executable(A_Bugs_Life_Jake_O_Reilly_CA2 main.cpp
        Bug.cpp
        Bug.h
        Crawler.cpp
        Crawler.h
        Hopper.cpp
        Hopper.h
        Direction.cpp
        main.h
        conversion_utils.cpp
        conversion_utils.h
        Board.cpp
        Board.h
        Indecisus.cpp
        Indecisus.h)

# Setting up SFML
# Used: https://youtu.be/4oh-tmxtIrA?si=zSUEYXgaqDvDl4Sd
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(C:/SFML/include)
target_link_libraries(A_Bugs_Life_Jake_O_Reilly_CA2 sfml-audio sfml-graphics sfml-window sfml-system)
