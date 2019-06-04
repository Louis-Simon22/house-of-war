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
    src/model/entities/army.h
    src/model/entities/character.h
    src/model/entities/circularinfluencezone.h
    src/model/entities/delaunayedge.h
    src/model/entities/entity.h
    src/model/entities/entitychange.h
    src/model/entities/entitypositionchange.h
    src/model/entities/interactiveentity.h
    src/model/entities/influencezone.h
    src/model/entities/tile.h
    src/model/entities/voronoicell.h
    src/model/graphtypes.h
    src/model/managers/delaunayvoronoigraph.h
    src/model/managers/entitychangemanager.h
    src/model/managers/entitiesmanager.h
    src/model/managers/modelmanager.h
    src/model/modeltypes.h
    src/model/operations/celldataoperations.h
    src/model/generation/celldatagenerator.h
    src/model/generation/delaunayextrapolator.h
    src/model/generation/elevationgenerator.h
    src/model/generation/entitygenerator.h
    src/model/generation/graphgenerator.h
    src/model/generation/jcv_voronoi_adapter.h
    src/model/generation/poissondisksamplingadapter.h
    src/model/generation/walkingdistancescalculator.h
    src/model/generation/worldgenerationconfig.h
    src/model/operations/armiesiterator.h
    src/model/operations/graphoperations.h
    src/model/operations/pathfindingoperations.h
    src/model/operations/polygonindexoperations.h
    src/model/operations/tilesiterator.h
    src/model/random/utilsrandom.h
    src/model/utils/clockwisepointcomparator.h
    src/model/utils/easingfunctions.h
    src/model/utils/pointcomparator.h
    src/model/utils/segmentcomparator.h
    src/ui/control/entitiescontroller.h
    src/ui/control/modelcontroller.h
    src/ui/control/selectionmanager.h
    src/ui/conversion/converter.h
    src/ui/items/armyitem.h
    src/ui/items/entityitem.h
    src/ui/items/influencezoneitem.h
    src/ui/items/interactiveentityitem.h
    src/ui/items/voronoicellitem.h
    src/ui/painters/circlepainter.h
    src/ui/painters/painteritem.h
    src/ui/painters/rectanglepainter.h
    src/ui/painters/polygonpainter.h
    src/ui/painters/segmentspainter.h
    src/ui/threading/iterationtimermanager.h
    src/ui/threading/modelthreadmanager.h
    )

set(CPP_FILES
    src/model/entities/army.cpp
    src/model/entities/character.cpp
    src/model/entities/circularinfluencezone.cpp
    src/model/entities/delaunayedge.cpp
    src/model/entities/entity.cpp
    src/model/entities/entitychange.cpp
    src/model/entities/entitypositionchange.cpp
    src/model/entities/interactiveentity.cpp
    src/model/entities/influencezone.cpp
    src/model/entities/tile.cpp
    src/model/entities/voronoicell.cpp
    src/model/managers/delaunayvoronoigraph.cpp
    src/model/managers/entitychangemanager.cpp
    src/model/managers/entitiesmanager.cpp
    src/model/managers/modelmanager.cpp
    src/model/generation/celldatagenerator.cpp
    src/model/generation/delaunayextrapolator.cpp
    src/model/generation/elevationgenerator.cpp
    src/model/generation/entitygenerator.cpp
    src/model/generation/graphgenerator.cpp
    src/model/generation/jcv_voronoi_adapter.cpp
    src/model/generation/poissondisksamplingadapter.cpp
    src/model/generation/walkingdistancescalculator.cpp
    src/model/generation/worldgenerationconfig.cpp
    src/model/operations/armiesiterator.cpp
    src/model/operations/graphoperations.cpp
    src/model/operations/pathfindingoperations.cpp
    src/model/operations/polygonindexoperations.cpp
    src/model/operations/tilesiterator.cpp
    src/model/utils/clockwisepointcomparator.cpp
    src/model/utils/easingfunctions.cpp
    src/model/utils/pointcomparator.cpp
    src/model/utils/segmentcomparator.cpp
    src/ui/control/entitiescontroller.cpp
    src/ui/control/modelcontroller.cpp
    src/ui/control/selectionmanager.cpp
    src/ui/conversion/converter.cpp
    src/ui/items/armyitem.cpp
    src/ui/items/entityitem.cpp
    src/ui/items/influencezoneitem.cpp
    src/ui/items/interactiveentityitem.cpp
    src/ui/items/voronoicellitem.cpp
    src/ui/painters/circlepainter.cpp
    src/ui/painters/painteritem.cpp
    src/ui/painters/rectanglepainter.cpp
    src/ui/painters/polygonpainter.cpp
    src/ui/painters/segmentspainter.cpp
    src/ui/threading/modelthreadmanager.cpp
    src/ui/threading/iterationtimermanager.cpp
    )

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
find_package(LibNoise REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Boost REQUIRED COMPONENTS graph)

# Puts the files in the qml.qrc in the QML_FILES variable
qt5_add_resources(QML_FILES qml.qrc)

add_executable(${PROJECT_NAME} src/main.cpp ${HEADER_FILES} ${CPP_FILES} ${QML_FILES})

target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick)

target_include_directories(${PROJECT_NAME} INTERFACE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::graph)

target_include_directories(${PROJECT_NAME} INTERFACE ${LIBNOISE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBNOISE_LIBRARIES})
