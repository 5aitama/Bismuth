cmake_minimum_required (VERSION 3.8)

project ("Bismuth")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE S_FILES ${CMAKE_SOURCE_DIR}/src/**.cc)
file(GLOB_RECURSE H_FILES ${CMAKE_SOURCE_DIR}/src/**.h)

# Search the Vulkan package...
find_package(Vulkan REQUIRED)

find_program(GLSLC glslc REQUIRED)

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

file(GLOB_RECURSE GLSL_SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/src/shaders/*.frag"
    "${CMAKE_SOURCE_DIR}/src/shaders/*.vert"
)

file(GLOB_RECURSE OLD_SPIRV "${PROJECT_BINARY_DIR}/shaders/*.spv")

foreach(OLD_SPIRV_FILE ${OLD_SPIRV})
    message(${OLD_SPIRV_FILE})
    file(REMOVE ${OLD_SPIRV_FILE})
endforeach()

foreach(GLSL ${GLSL_SOURCE_FILES})
    get_filename_component(FILE_NAME ${GLSL} NAME)
    message("${FILE_NAME}")
    set(SPIRV "${PROJECT_BINARY_DIR}/shaders/${FILE_NAME}.spv")
    add_custom_command(
        OUTPUT ${SPIRV}
        COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/shaders/"
        COMMAND ${GLSLC} ${GLSL} -o ${SPIRV}
        DEPENDS ${GLSL}
    )
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    Shaders 
    DEPENDS ${SPIRV_BINARY_FILES}
)

add_dependencies(${PROJECT_NAME} Shaders)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders/"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_BINARY_DIR}/shaders"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders"
)