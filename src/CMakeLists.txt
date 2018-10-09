cmake_minimum_required(VERSION 3.12)


include(cmake/HunterGate.cmake)
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.27.tar.gz"
    SHA1 "70d75a25f895df3da00d8382417e8c2a08c93173"
)

project(TEST)

hunter_add_package(glfw)

find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan)

if (WIN32)

    add_compile_options("/std:c++latest")
    add_compile_options("/ZI")
endif()

add_executable(TEST 
                    main.cpp 
                    app.cpp app.h 
                    util/logging/logger.h
                    util/logging/logger.cpp
                    graphics/graphics_backend.h graphics/graphics_backend.cpp
                    graphics/vulkan/vulkan_backend.h
                    graphics/vulkan/vulkan_backend.cpp)

target_link_libraries(TEST ${Vulkan_LIBRARIES} glfw)
include_directories(${Vulkan_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(include)
