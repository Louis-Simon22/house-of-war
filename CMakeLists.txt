cmake_minimum_required(VERSION 3.8)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "-O0")

project(house-of-war LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADER_FILES
        src/control/gamemanager.h
        src/model/graphtypes.h
        src/model/modeltypes.h
        src/model/pointcomparator.h
        src/model/segmentcomparator.h
        src/model/world/delaunayedge.h
        src/model/world/voronoicell.h
        src/model/world/worldloader.h
        src/model/world/worlddata.h
        src/model/world/worldgeneration/jcv_voronoi_adapter.h
        src/model/world/worldgeneration/delaunayextrapolator.h
        src/model/world/worldgeneration/worldbuilder.h
        src/utils/algo/poissondisksampling.h
        src/bind/gamemanagerqmlbindings.h
        src/bind/models/worldmodel.h
        src/bind/painters/celloutlinepainter.h
        )

set(CPP_FILES
        src/control/gamemanager.cpp
        src/model/pointcomparator.cpp
        src/model/segmentcomparator.cpp
        src/model/world/delaunayedge.cpp
        src/model/world/voronoicell.cpp
        src/model/world/worldloader.cpp
        src/model/world/worlddata.cpp
        src/model/world/worldgeneration/jcv_voronoi_adapter.cpp
        src/model/world/worldgeneration/delaunayextrapolator.cpp
        src/model/world/worldgeneration/worldbuilder.cpp
        src/bind/gamemanagerqmlbindings.cpp
        src/bind/models/worldmodel.cpp
        src/bind/painters/celloutlinepainter.cpp
        )

find_package(Qt5 REQUIRED COMPONENTS Core Quick)
# Puts the files in the qml.qrc in the QML_FILES variable
qt5_add_resources(QML_FILES qml.qrc)

find_package(Boost REQUIRED COMPONENTS graph)

add_executable(${PROJECT_NAME} src/main.cpp ${HEADER_FILES} ${CPP_FILES} ${QML_FILES})

target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick)

# Boost_INCLUDE_DIRS was set by find_package(Boost ...) command. This directory contains the header files
target_include_directories(${PROJECT_NAME} INTERFACE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::graph)
