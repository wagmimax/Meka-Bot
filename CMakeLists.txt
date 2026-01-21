cmake_minimum_required(VERSION 3.16)
project(CryptoPipeline VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/include)

# --- Boost Beast ---
find_package(Boost CONFIG REQUIRED beast)

# --- nlohmann_json ---
find_package(nlohmann_json CONFIG REQUIRED)

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

# --- Source files ---
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# --- Executable ---
add_executable(${PROJECT_NAME} ${SOURCES})

# --- Set output directory (AFTER target creation) ---
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

# --- Link libraries ---
target_link_libraries(${PROJECT_NAME} 
    Boost::beast
    nlohmann_json::nlohmann_json
    unofficial::sqlite3::sqlite3
    OpenSSL::SSL
    OpenSSL::Crypto
    tabulate::tabulate
    ws2_32
)

#cmake -B build -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -G "Visual Studio 17 2022" -A x64 (to init)
#cmake --build build --config Release (to compile)