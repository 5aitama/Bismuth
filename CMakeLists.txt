cmake_minimum_required (VERSION 3.8)

project ("Bismuth")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE S_FILES ${CMAKE_SOURCE_DIR}/src/**.cc)
file(GLOB_RECURSE H_FILES ${CMAKE_SOURCE_DIR}/src/**.h)

# Search the Vulkan package...
find_package(Vulkan REQUIRED)

# Add the GLM package...
add_subdirectory(submodules/glm)

# Add the GLFW package...
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(submodules/glfw)

add_executable(${PROJECT_NAME} ${S_FILES} ${H_FILES})

add_definitions(
    -DAPP_VERSION="${PROJECT_VERSION}"
    -DAPP_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    -DAPP_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    -DAPP_VERSION_PATCH=${PROJECT_VERSION_PATCH}
    -DAPP_VERSION_VARIANT=0
)

target_include_directories (${PROJECT_NAME} 
    PUBLIC ${GLFW_INCLUDE_DIRS}
    PUBLIC ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC glm
    PUBLIC glfw
    PUBLIC ${Vulkan_LIBRARIES}
)