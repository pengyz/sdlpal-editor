cmake_minimum_required(VERSION 3.12.0)
project(sdlpal-editor VERSION 0.1.0)

# use the lastest standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# include(CTest)
# enable_testing()

set(BUILD_SHARED_LIBS OFF)
set(WITH_GFLAGS OFF)
set(WITH_GTEST OFF)
add_subdirectory(3rd/SDL EXCLUDE_FROM_ALL)
add_subdirectory(3rd/glog EXCLUDE_FROM_ALL)
add_subdirectory(3rd/stb_image EXCLUDE_FROM_ALL)

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

file(GLOB EDITOR_FILES CONFIGURE_DEPENDS "src/editor/*.h" "src/editor/*.cpp")
file(GLOB ENGINE_FILES CONFIGURE_DEPENDS "src/engine/*.h" "src/engine/*.cpp")
file(GLOB RENDER_FILES CONFIGURE_DEPENDS "src/engine/render/*.h" "src/engine/render/*.cpp")
file(GLOB GAME_FILES CONFIGURE_DEPENDS "src/game/*.h" "src/game/*.cpp")


add_executable(sdlpal-editor 
    ${EDITOR_FILES}
    ${ENGINE_FILES}
    ${RENDER_FILES}
    ${GAME_FILES}
    src/main.cpp
)

target_link_libraries(sdlpal-editor PRIVATE
    imgui_sdlrenderer
    glog
    stb_image
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_custom_command(TARGET sdlpal-editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:sdlpal-editor>/bin/resources
)
