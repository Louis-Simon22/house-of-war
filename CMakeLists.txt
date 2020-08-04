cmake_minimum_required(VERSION 3.14)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "-O0")

project(house-of-war LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

file(GLOB_RECURSE CPP_FILES "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "src/*.h")

set (INCLUDE_DIRS "")
foreach (_headerFile ${HEADER_FILES})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

find_package(LibNoise REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Boost REQUIRED COMPONENTS graph)

# Puts the files in the qml.qrc in the QML_FILES variable
qt5_add_resources(QML_FILES qml.qrc)

add_executable(${PROJECT_NAME} ${CPP_FILES} ${QML_FILES})

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

message(${Boost_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${LIBNOISE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core Qt5::Quick Boost::graph ${LIBNOISE_LIBRARIES})
