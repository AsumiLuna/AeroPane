cmake_minimum_required(VERSION 3.29)

project(AeroPane)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(AeroPane main.cpp resource.rc)

set_target_properties(AeroPane PROPERTIES WIN32_EXECUTABLE ON)


target_link_libraries(AeroPane
        dwmapi
        )



