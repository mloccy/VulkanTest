cmake_minimum_required(VERSION 3.12)


include(cmake/HunterGate.cmake)
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.27.tar.gz"
    SHA1 "70d75a25f895df3da00d8382417e8c2a08c93173"
)


if (WIN32)
    set(GLSLCompiler "glslangValidator.exe")
else()
    set(GLSLCompiler "glslangValidator")
endif()

if (WIN32)
    Set (CopyCommand "copy")
    Set (CopyArgs "/y")
else()
    Set (CopyCommand "cp")
    set (CopyArgs "")

endif()


function (compile_shader Name FileName)


        Set(OutputPath "${CMAKE_CURRENT_SOURCE_DIR}/spv/${Name}.spv")

        add_custom_command(
            TARGET Shaders
            COMMENT "Compihling ${Name}..."
            COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/../hooks/bin/${GLSLCompiler}"
            -V "${FileName}"
            -o ${OutputPath})

        add_custom_command(
            TARGET Shaders
            POST_BUILD
            COMMAND cmake -E copy ${OutputPath} $<TARGET_FILE_DIR:TEST>)

endfunction(compile_shader)


file(GLOB GLSL
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.frag"
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vert"
)


source_group(Shaders ${GLSL})
add_custom_target(Shaders ALL SOURCES ${GLSL})


foreach(shader IN LISTS GLSL)
    get_filename_component(name shader NAME)
    set_source_files_properties(${shader} PROPERTIES HEADER_FILE_ONLY TRUE)
    compile_shader(${name} ${shader})
    

endforeach()


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

                    graphics/graphics_includes.h
                    
                    graphics/shader.h
                    graphics/shader.cpp

                    graphics/vertexShader.h
                    graphics/vertexShader.cpp

                    graphics/fragmentShader.h
                    graphics/fragmentShader.cpp

                    graphics/graphics_backend.h graphics/graphics_backend.cpp
                    ${GLSL}
                    graphics/vulkan/vulkan_backend.h
                    graphics/vulkan/vulkan_backend.cpp)

        
target_link_libraries(TEST ${Vulkan_LIBRARIES} glfw)
include_directories(${Vulkan_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(include)
