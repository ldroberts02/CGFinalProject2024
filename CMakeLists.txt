cmake_minimum_required(VERSION 3.18)
project(learnopengl)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/GL)
add_subdirectory(external/glm)
add_subdirectory(external/SDL)
add_subdirectory(external/stb)

file(GLOB_RECURSE SRC_SOURCES src/*.c*)
file(GLOB_RECURSE SRC_HEADERS src/*.h*)

add_executable(${PROJECT_NAME} ${SRC_SOURCES} ${SRC_HEADERS})


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glm
        stb
        libglew_static
        SDL2main
        SDL2-static
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        glm
        stb
        SDL2main
        SDL2-static
)

# This command will copy your assets folder to your running directory, in order to have access to your shaders, textures, etc
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
