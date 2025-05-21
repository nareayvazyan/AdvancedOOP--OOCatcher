cmake_minimum_required(VERSION 3.16)
project(OOCatcher)

set(CMAKE_CXX_STANDARD 17)

set(RAYLIB_DIR "C:/Libraries/raylib")  

include_directories(${RAYLIB_DIR}/include)
link_directories(${RAYLIB_DIR}/lib)

add_executable(OOCatcher
        main.cpp
        point.cpp
        base_line.cpp
        line1.cpp
        line2.cpp
        limb.cpp
        body.cpp
        config.h
)

target_link_libraries(OOCatcher
        raylib
        opengl32
        gdi32
        winmm
        kernel32  
        user32    
)
