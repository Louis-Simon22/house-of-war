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
    src/model/characters/charactergeneration/charactergenerator.h
    src/model/characters/characterdata.h
    src/model/characters/character.h
    src/model/delaunaygraphtypes.h
    src/model/entities/entity.h
    src/model/entities/graphentity.h
    src/model/entities/movement/entitymovement.h
    src/model/entities/movement/graphmovement.h
    src/model/entities/movement/movementcalculator.h
    src/model/entities/movement/movementmanager.h
    src/model/entities/movement/movementweightcalculator.h
    src/model/entities/movement/progressivemovement.h
    src/model/gamedatamanager.h
    src/model/modeltypes.h
    src/model/pointcomparator.h
    src/model/random/utilsrandom.h
    src/model/random/poissondisksampling.h
    src/model/segmentcomparator.h
    src/model/world/delaunayedge.h
    src/model/world/voronoicell.h
    src/model/world/worlddata.h
    src/model/world/worldgeneration/jcv_voronoi_adapter.h
    src/model/world/worldgeneration/delaunayextrapolator.h
    src/model/world/worldgeneration/worldgenerator.h
    src/ui/wrappers/characterdataqmlwrapper.h
    src/ui/wrappers/gamedatamanagerqmlwrapper.h
    src/ui/wrappers/worlddataqmlwrapper.h
    src/ui/control/modelthreadmanager.h
    src/ui/models/cellsmodel.h
    src/ui/models/charactersmodel.h
    src/ui/painters/segmentspainter.h
    )

set(CPP_FILES
    src/model/characters/charactergeneration/charactergenerator.cpp
    src/model/characters/characterdata.cpp
    src/model/characters/character.cpp
    src/model/entities/entity.cpp
    src/model/entities/graphentity.cpp
    src/model/entities/movement/entitymovement.cpp
    src/model/entities/movement/graphmovement.cpp
    src/model/entities/movement/movementcalculator.cpp
    src/model/entities/movement/movementmanager.cpp
    src/model/entities/movement/movementweightcalculator.cpp
    src/model/entities/movement/progressivemovement.cpp
    src/model/gamedatamanager.cpp
    src/model/pointcomparator.cpp
    src/model/segmentcomparator.cpp
    src/model/world/delaunayedge.cpp
    src/model/world/voronoicell.cpp
    src/model/world/worlddata.cpp
    src/model/world/worldgeneration/jcv_voronoi_adapter.cpp
    src/model/world/worldgeneration/delaunayextrapolator.cpp
    src/model/world/worldgeneration/worldgenerator.cpp
    src/ui/wrappers/characterdataqmlwrapper.cpp
    src/ui/wrappers/gamedatamanagerqmlwrapper.cpp
    src/ui/wrappers/worlddataqmlwrapper.cpp
    src/ui/control/modelthreadmanager.cpp
    src/ui/models/cellsmodel.cpp
    src/ui/models/charactersmodel.cpp
    src/ui/painters/segmentspainter.cpp
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
