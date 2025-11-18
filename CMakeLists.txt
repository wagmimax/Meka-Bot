cmake_minimum_required(VERSION 3.16)
project(CryptoPipeline VERSION 1.0 LANGUAGES CXX)

# ---------------------------
# Use C++20
# ---------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------
# Output directories
# ---------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ---------------------------
# Find Boost (system + thread)
# ---------------------------
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.75 REQUIRED COMPONENTS system thread)

# ---------------------------
# Find nlohmann_json (header-only)
# ---------------------------
find_package(nlohmann_json 3.10 REQUIRED)

# ---------------------------
# Find SQLite3
# ---------------------------
find_package(SQLite3 REQUIRED)

# ---------------------------
# Include directories
# ---------------------------
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

# ---------------------------
# Source files
# ---------------------------
file(GLOB SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

# ---------------------------
# Build executable
# ---------------------------
add_executable(${PROJECT_NAME} ${SOURCES})

# ---------------------------
# Link libraries
# ---------------------------
target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES}
    nlohmann_json::nlohmann_json
    SQLite::SQLite3
)