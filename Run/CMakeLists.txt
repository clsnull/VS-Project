cmake_minimum_required(VERSION 3.28)

project("Run" LANGUAGES CXX)

set(ENV{http_proxy} "http://127.0.0.1:7890")  # Clash/V2Ray默认端口
set(ENV{https_proxy} "http://127.0.0.1:7890")
set(ENV{HTTP_PROXY} "http://127.0.0.1:7890")
set(ENV{HTTPS_PROXY} "http://127.0.0.1:7890")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)

FetchContent_MakeAvailable(SFML)

# 如果有头文件目录
include_directories(src)

file(GLOB SOURCES "src/*.cpp")

add_executable(main ${SOURCES})

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)