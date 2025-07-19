file(GLOB_RECURSE TRIANGLE_SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

add_executable(triangle_example ${TRIANGLE_SRC})

target_compile_definitions(triangle_example PUBLIC FMT_UNICODE=0)
target_include_directories(triangle_example PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(triangle_example PRIVATE glfw glad imgui glm spdlog opengllib)

if (MSVC)
    target_link_options(triangle_example PRIVATE "/SUBSYSTEM:CONSOLE")
endif()