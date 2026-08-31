cmake_minimum_required(VERSION 3.12)
project(HLiteProject CXX) # Your main project name;

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(exec_name "main") # Your main executable name.
set(main_code "example/Graphics2D/HBrickSample/main.cpp") # Your main source code.

set(hlite_name_static "hlite")
set(HLITE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/HLITE/sources")
set(RAYLIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/HLITE/lib/raylib")
set(RAYLIB_INCLUDE_DIR "${RAYLIB_DIR}/include")
set(RAYLIB_STATIC_LIB "${RAYLIB_DIR}/lib/libraylib.a")

add_library(${hlite_name_static}
    STATIC
    "${HLITE_DIR}/src/Core.cpp"
    "${HLITE_DIR}/src/Utility.cpp"
    "${HLITE_DIR}/src/File.cpp"
    "${HLITE_DIR}/src/Graphics2D.cpp"
    "${HLITE_DIR}/src/HLiteMain.cpp"
    "${HLITE_DIR}/src/Shader.cpp"
    "${HLITE_DIR}/src/UserInterface.cpp"
)

target_include_directories(${hlite_name_static}
    PUBLIC 
    "${HLITE_DIR}/include"
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