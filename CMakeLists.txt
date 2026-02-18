cmake_minimum_required(VERSION 3.16)
project(CryptoPipeline VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/include)

# Profiling latency
option(ENABLE_TRACY "Enable Tracy Profiler" OFF)

if(ENABLE_TRACY)
    include(FetchContent)
    FetchContent_Declare(
        tracy
        GIT_REPOSITORY https://github.com/wolfpld/tracy.git
        GIT_TAG v0.13.1
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(tracy)
    message(STATUS "Tracy profiler enabled")
endif()

# --- Boost Beast ---
find_package(Boost CONFIG REQUIRED)

# --- nlohmann_json ---
find_package(nlohmann_json CONFIG REQUIRED)

# --- simdjson ---
find_package(simdjson CONFIG REQUIRED)

# --- SQLite3 ---
find_package(unofficial-sqlite3 CONFIG REQUIRED)

# --- OpenSSL ---
find_package(OpenSSL REQUIRED)

# --- implot ---
find_package(implot CONFIG REQUIRED)

# --- imgui ---
find_package(imgui CONFIG REQUIRED)

# --- tabulate ---
find_package(tabulate CONFIG REQUIRED)

# --- cpp-jwt ---
find_package(cpp-jwt CONFIG REQUIRED)

# --- libcurl wrapper ---
find_package(curlcpp CONFIG REQUIRED)

# --- Source files ---
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# --- Executable ---
add_executable(${PROJECT_NAME} ${SOURCES})

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -O3 -march=native -flto)
    target_link_options(${PROJECT_NAME} PRIVATE -flto)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -O3 -march=native -flto)
    target_link_options(${PROJECT_NAME} PRIVATE -flto)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /O2 /GL)
    target_link_options(${PROJECT_NAME} PRIVATE /LTCG)
endif()


# --- Set output directory ---
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/Release"
)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:CURL::libcurl>"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)

# --- Link libraries ---
target_link_libraries(${PROJECT_NAME} 
    Boost::boost
    nlohmann_json::nlohmann_json
    unofficial::sqlite3::sqlite3
    OpenSSL::SSL
    OpenSSL::Crypto
    tabulate::tabulate
    simdjson::simdjson
    cpp-jwt::cpp-jwt
    curlcpp::curlcpp
    ws2_32
)

if(ENABLE_TRACY)
    target_link_libraries(${PROJECT_NAME} TracyClient)
    target_compile_definitions(${PROJECT_NAME} PRIVATE TRACY_ENABLE)
    target_link_libraries(${PROJECT_NAME} dbghelp)
endif()