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
            COMMENT "Compiling ${Name}..."
            COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/../hooks/bin/${GLSLCompiler}"
            -V "${FileName}"
            -o ${OutputPath})

        add_custom_command(
            TARGET Shaders
            POST_BUILD
            COMMAND cmake -E make_directory $<TARGET_FILE_DIR:TEST>/Shaders
            COMMAND cmake -E copy ${OutputPath} $<TARGET_FILE_DIR:TEST>/Shaders)

endfunction(compile_shader)


file(GLOB GLSL
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.frag"
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vert"
)


file(GLOB GraphicsFolder
    "${CMAKE_CURRENT_SOURCE_DIR}/Graphics/*")

file(GLOB InputFolder
    "${CMAKE_CURRENT_SOURCE_DIR}/Input/*")

file(GLOB EventsFolder
    "${CMAKE_CURRENT_SOURCE_DIR}/Events/*")

file(GLOB UtilsFolder
    "${CMAKE_CURRENT_SOURCE_DIR}/Utils/*")

source_group(Graphics FILES ${GraphicsFolder})
source_group(Input FILES ${InputFolder})
source_group(Events FILES ${EventsFolder})
source_group(Utils FILES ${UtilsFolder})

source_group(Shaders ${GLSL})
add_custom_target(Shaders ALL SOURCES ${GLSL})


foreach(shader IN LISTS GLSL)
    get_filename_component(name ${shader} NAME)
    get_filename_component(extension ${shader} EXT)
    set_source_files_properties(${shader} PROPERTIES HEADER_FILE_ONLY TRUE)
    compile_shader(${name}${ext} ${shader})
endforeach()


project(TEST)

hunter_add_package(glfw)

find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan)

if (WIN32)

    add_compile_options("/std:c++latest")
    add_compile_options("/ZI")
endif()




add_executable(TEST WIN32
    main.cpp 
    app.cpp app.h

    ${GraphicsFolder}
    ${InputFolder}
    ${EventsFolder}
    ${UtilsFolder})


if (WIN32)
    set_target_properties(TEST PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Build/Debug/" )
endif()
        
target_link_libraries(TEST ${Vulkan_LIBRARIES} glfw)
include_directories(${Vulkan_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(include)
