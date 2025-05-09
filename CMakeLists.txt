cmake_minimum_required(VERSION 3.28)
project(Game LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Подключение SFML 3.0
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Подключение tmxlite
add_subdirectory(external/tmxlite/tmxlite)
include_directories(external/tmxlite/tmxlite/include)

# Подключение nlohmann/json
add_subdirectory(external/json)
include_directories(external/json/include)

file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.hpp")
add_executable(main ${SOURCES})

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE tmxlite SFML::Graphics SFML::Audio nlohmann_json::nlohmann_json)