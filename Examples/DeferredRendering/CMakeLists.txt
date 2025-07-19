file(GLOB_RECURSE DEFERRED_RENDERER_EXAMPLE_SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

add_executable(deferred_renderer_example ${DEFERRED_RENDERER_EXAMPLE_SRC})

target_compile_definitions(deferred_renderer_example PUBLIC FMT_UNICODE=0)
target_include_directories(deferred_renderer_example PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(deferred_renderer_example PRIVATE glfw glad imgui glm spdlog opengllib)

if (MSVC)
    target_link_options(deferred_renderer_example PRIVATE "/SUBSYSTEM:CONSOLE")
endif()