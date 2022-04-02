cmake_minimum_required(VERSION 3.12.0)
project(sdlpal-editor VERSION 0.1.0)

# use the lastest standard
set(CMAKE_CXX_STANDARD 20)

# include(CTest)
# enable_testing()

set(BUILD_SHARED_LIBS OFF)
set(WITH_GFLAGS OFF)
set(WITH_GTEST OFF)
add_subdirectory(3rd/SDL EXCLUDE_FROM_ALL)
add_subdirectory(3rd/glog EXCLUDE_FROM_ALL)

add_library(imgui_sdlrenderer STATIC
    ${CMAKE_SOURCE_DIR}/3rd/imgui/backends/imgui_impl_sdlrenderer.cpp
    ${CMAKE_SOURCE_DIR}/3rd/imgui/backends/imgui_impl_sdlrenderer.h
    ${CMAKE_SOURCE_DIR}/3rd/imgui/backends/imgui_impl_sdl.cpp
    ${CMAKE_SOURCE_DIR}/3rd/imgui/backends/imgui_impl_sdl.h
    
    ${CMAKE_SOURCE_DIR}/3rd/imgui/misc/cpp/imgui_stdlib.cpp
    ${CMAKE_SOURCE_DIR}/3rd/imgui/misc/cpp/imgui_stdlib.h
    ${CMAKE_SOURCE_DIR}/3rd/imgui/imgui.h
    ${CMAKE_SOURCE_DIR}/3rd/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/3rd/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/3rd/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/3rd/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/3rd/imgui/imgui_demo.cpp
)

target_include_directories(imgui_sdlrenderer PUBLIC
    ${CMAKE_SOURCE_DIR}/3rd/imgui/backends/
    ${CMAKE_SOURCE_DIR}/3rd/imgui/
    ${CMAKE_SOURCE_DIR}/3rd/imgui/misc/cpp/
)

target_link_libraries(imgui_sdlrenderer PUBLIC
    SDL2-static
    SDL2main
)

file(GLOB ENGINE_FILES CONFIGURE_DEPENDS "src/engine/*.h" "src/engine/*.cpp")

file(GLOB FRAMEWORK_FILES CONFIGURE_DEPENDS "src/framework/*.h" "src/framework/*.cpp")

file(GLOB GUI_FILES CONFIGURE_DEPENDS "src/gui/*.h" "src/gui/*.cpp")


add_executable(sdlpal-editor 
    ${FRAMEWORK_FILES}
    ${GUI_FILES}
    ${ENGINE_FILES}
    src/main.cpp
)

target_link_libraries(sdlpal-editor PRIVATE
    imgui_sdlrenderer
    glog
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
