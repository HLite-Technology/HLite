cmake_minimum_required(VERSION 3.12)
project(HLiteProject CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(exec_name "main")
set(hlite_name_static "hlite")
set(main_code "example/BasicWindow/main.cpp")

set(RAYLIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/raylib")
set(RAYLIB_INCLUDE_DIR "${RAYLIB_DIR}/include")
set(RAYLIB_STATIC_LIB "${RAYLIB_DIR}/libraylib.a")

add_library(${hlite_name_static}
    STATIC
    src/source/Core.cpp
    src/source/File.cpp
    src/source/Graphics2D.cpp
    src/source/HLiteMain.cpp
    src/source/Shader.cpp
    src/source/UserInterface.cpp
)

target_include_directories(${hlite_name_static}
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
    ${RAYLIB_INCLUDE_DIR}
)

target_link_libraries(${hlite_name_static} PRIVATE ${RAYLIB_STATIC_LIB})

if(WIN32)
    target_link_libraries(${hlite_name_static} PUBLIC winmm gdi32 opengl32)
elseif(APPLE)
    target_link_libraries(${hlite_name_static} PUBLIC "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
else()
    find_package(Threads REQUIRED)
    target_link_libraries(${hlite_name_static} PUBLIC GL m pthread dl rt X11)
endif()

add_executable(${exec_name} ${main_code})

target_link_libraries(${exec_name} PRIVATE ${hlite_name_static})