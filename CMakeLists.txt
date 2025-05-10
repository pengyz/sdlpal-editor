cmake_minimum_required(VERSION 3.12.0)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/deps/vcpkg/scripts/buildsystems/vcpkg.cmake)
project(sdlpal-editor VERSION 0.1.0)

find_package(glog CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Stb REQUIRED)

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

# add_library(imgui_sdlrenderer STATIC
#     ${CMAKE_SOURCE_DIR}/3rd/imgui/backends/imgui_impl_sdlrenderer.cpp
#     ${CMAKE_SOURCE_DIR}/3rd/imgui/backends/imgui_impl_sdlrenderer.h
#     ${CMAKE_SOURCE_DIR}/3rd/imgui/backends/imgui_impl_sdl.cpp
#     ${CMAKE_SOURCE_DIR}/3rd/imgui/backends/imgui_impl_sdl.h
    
#     ${CMAKE_SOURCE_DIR}/3rd/imgui/misc/cpp/imgui_stdlib.cpp
#     ${CMAKE_SOURCE_DIR}/3rd/imgui/misc/cpp/imgui_stdlib.h
#     ${CMAKE_SOURCE_DIR}/3rd/imgui/imgui.h
#     ${CMAKE_SOURCE_DIR}/3rd/imgui/imgui.cpp
#     ${CMAKE_SOURCE_DIR}/3rd/imgui/imgui_draw.cpp
#     ${CMAKE_SOURCE_DIR}/3rd/imgui/imgui_tables.cpp
#     ${CMAKE_SOURCE_DIR}/3rd/imgui/imgui_widgets.cpp
#     ${CMAKE_SOURCE_DIR}/3rd/imgui/imgui_demo.cpp
# )

# target_include_directories(imgui_sdlrenderer PUBLIC
#     ${CMAKE_SOURCE_DIR}/3rd/imgui/backends/
#     ${CMAKE_SOURCE_DIR}/3rd/imgui/
#     ${CMAKE_SOURCE_DIR}/3rd/imgui/misc/cpp/
# )

# target_link_libraries(imgui_sdlrenderer PUBLIC
#     $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
#     $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
# )

file(GLOB EDITOR_FILES CONFIGURE_DEPENDS "src/editor/*.h" "src/editor/*.cpp")
file(GLOB ENGINE_FILES CONFIGURE_DEPENDS "src/engine/*.h" "src/engine/*.cpp")
file(GLOB RENDER_FILES CONFIGURE_DEPENDS "src/engine/render/*.h" "src/engine/render/*.cpp")
file(GLOB GAME_FILES CONFIGURE_DEPENDS "src/game/*.h" "src/game/*.cpp")


add_executable(${PROJECT_NAME}
    ${EDITOR_FILES}
    ${ENGINE_FILES}
    ${RENDER_FILES}
    ${GAME_FILES}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glog::glog
    imgui::imgui
)

target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/bin/resources
)
