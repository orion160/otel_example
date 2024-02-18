cmake_minimum_required(VERSION 3.28)
project("OTEL EXAMPLE" LANGUAGES CXX)

add_library(base_OTEL INTERFACE)
set_target_properties(base_OTEL PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

find_package(absl CONFIG REQUIRED)
find_package(opentelemetry-cpp CONFIG REQUIRED)

add_executable(OTEL_EXAMPLE)
target_sources(OTEL_EXAMPLE PRIVATE main.cpp)

target_include_directories(OTEL_EXAMPLE PRIVATE ${OPENTELEMETRY_CPP_INCLUDE_DIRS})
target_link_libraries(OTEL_EXAMPLE PRIVATE ${OPENTELEMETRY_CPP_LIBRARIES})
