
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(opengllib STATIC ${SOURCES})

option(GLIB_USE_IMGUI "Enable ImGui support" ON)
option(GLIB_USE_LOG "Enable spdlog logging support" ON)

target_include_directories(opengllib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(opengllib PUBLIC cxx_std_17)
target_link_libraries(opengllib PUBLIC glfw glad glm)

if (GLIB_USE_LOG)
    target_link_libraries(opengllib PUBLIC spdlog)
    target_compile_definitions(opengllib PUBLIC USE_LOG)
endif()

if (GLIB_USE_IMGUI)
    target_link_libraries(opengllib PUBLIC imgui)
    target_compile_definitions(opengllib PUBLIC USE_IMGUI)
endif()