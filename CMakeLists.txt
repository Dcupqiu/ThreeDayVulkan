cmake_minimum_required(VERSION 3.10)
project(ThreeDayVulkan)

set(CMAKE_CXX_STANDARD 17)

set(glslangValidator_executable /usr/bin/glslangValidator)

include(${CMAKE_SOURCE_DIR}/cmake/ShaderCompile.cmake)


find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Vulkan REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "./vulkan/*.cpp")

add_executable(ThreeDayVulkan main.cpp ${SOURCE_FILES})
target_link_libraries(ThreeDayVulkan Vulkan::Vulkan glfw)
target_include_directories(ThreeDayVulkan PRIVATE ./stb ./generated)
target_include_directories(ThreeDayVulkan PUBLIC ./vulkan)

target_include_directories(
        ThreeDayVulkan
        PUBLIC ./vulkanmemoryallocator/include
)

set(GENERATED_SHADER_FOLDER "generated")
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER})
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER})
endif()
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER}/spv)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER}/spv)
endif()
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER}/cpp)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER}/cpp)
endif()

set(SHADER_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SHADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/glsl/*.vert"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/*.frag"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/*.comp"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/*.geom"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/*.tesc"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/*.tese"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/*.mesh"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/*.task"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/*.rgen"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/*.rchit"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/*.rmiss"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/*.rcall")

file(GLOB_RECURSE TEXTURES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets/image/*.jpg")
file(COPY ${TEXTURES} DESTINATION ${CMAKE_BINARY_DIR}/textures)

file(GLOB_RECURSE MESH CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets/mesh/*.obj"
        "${CMAKE_CURRENT_SOURCE_DIR}/assets/mesh/*.png")
file(COPY ${MESH} DESTINATION ${CMAKE_BINARY_DIR}/mesh)

compile_shader(
        "${SHADER_FILES}"
        ThreeDayVulkan_shader
        "${SHADER_INCLUDE_FOLDER}"
        "${GENERATED_SHADER_FOLDER}"
        "${glslangValidator_executable}")

add_dependencies (ThreeDayVulkan ThreeDayVulkan_shader)