file(GLOB_RECURSE RENDERER_SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

add_executable(renderer ${RENDERER_SRC})

target_compile_definitions(renderer PUBLIC FMT_UNICODE=0)
target_include_directories(renderer PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(renderer PRIVATE glfw glad imgui glm spdlog)

if (MSVC)
    target_link_options(renderer PRIVATE "/SUBSYSTEM:CONSOLE")
endif()