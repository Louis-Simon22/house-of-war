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
    src/model/clockwisepointcomparator.h
    src/model/delaunaygraphtypes.h
    src/model/easingfunctions.h
    src/model/entities/characters/charactergeneration/charactergenerator.h
    src/model/entities/characters/characterdata.h
    src/model/entities/characters/character.h
    src/model/entities/entity.h
    src/model/entities/entitychange.h
    src/model/entities/entitychangemanager.h
    src/model/entities/graphentity.h
    src/model/entities/movement/graphmovement.h
    src/model/entities/movement/movementcalculator.h
    src/model/gamedatamanager.h
    src/model/modeltypes.h
    src/model/pointcomparator.h
    src/model/random/utilsrandom.h
    src/model/random/poissondisksampling.h
    src/model/segmentcomparator.h
    src/model/world/celldata.h
    src/model/world/delaunayedge.h
    src/model/world/graphoperations.h
    src/model/world/voronoicell.h
    src/model/world/worlddata.h    
    src/model/world/worldgeneration/celldatagenerator.h
    src/model/world/worldgeneration/celldataoperations.h
    src/model/world/worldgeneration/delaunayextrapolator.h
    src/model/world/worldgeneration/elevationgenerator.h
    src/model/world/worldgeneration/heightmap.h
    src/model/world/worldgeneration/jcv_voronoi_adapter.h
    src/model/world/worldgeneration/poissondisksamplingadapter.h
    src/model/world/worldgeneration/worldgenerator.h
    src/ui/control/characterscontroller.h
    src/ui/control/modelthreadmanager.h
    src/ui/conversion/converter.h
    src/ui/models/charactersmodel.h
    src/ui/models/entitymodel.h
    src/ui/models/voronoicellsmodel.h
    src/ui/painters/cellspainter.h
    src/ui/painters/paintingsutils.h
    src/ui/painters/segmentspainter.h
    src/ui/wrappers/characterdataqmlwrapper.h
    src/ui/wrappers/gamedatamanagerqmlwrapper.h
    src/ui/wrappers/worlddataqmlwrapper.h
    )

set(CPP_FILES
    src/model/clockwisepointcomparator.cpp
    src/model/easingfunctions.cpp
    src/model/entities/characters/charactergeneration/charactergenerator.cpp
    src/model/entities/characters/characterdata.cpp
    src/model/entities/characters/character.cpp
    src/model/entities/entity.cpp
    src/model/entities/entitychange.cpp
    src/model/entities/entitychangemanager.cpp
    src/model/entities/graphentity.cpp
    src/model/entities/movement/graphmovement.cpp
    src/model/entities/movement/movementcalculator.cpp
    src/model/gamedatamanager.cpp
    src/model/pointcomparator.cpp
    src/model/segmentcomparator.cpp
    src/model/world/celldata.cpp
    src/model/world/delaunayedge.cpp
    src/model/world/graphoperations.cpp
    src/model/world/voronoicell.cpp
    src/model/world/worlddata.cpp
    src/model/world/worldgeneration/celldatagenerator.cpp
    src/model/world/worldgeneration/celldataoperations.h
    src/model/world/worldgeneration/delaunayextrapolator.cpp
    src/model/world/worldgeneration/elevationgenerator.cpp
    src/model/world/worldgeneration/heightmap.cpp
    src/model/world/worldgeneration/jcv_voronoi_adapter.cpp
    src/model/world/worldgeneration/poissondisksamplingadapter.cpp
    src/model/world/worldgeneration/worldgenerator.cpp
    src/ui/control/characterscontroller.cpp
    src/ui/control/modelthreadmanager.cpp
    src/ui/conversion/converter.cpp
    src/ui/models/charactersmodel.cpp
    src/ui/models/entitymodel.cpp
    src/ui/models/voronoicellsmodel.cpp
    src/ui/painters/cellspainter.cpp
    src/ui/painters/paintingsutils.cpp
    src/ui/painters/segmentspainter.cpp
    src/ui/wrappers/characterdataqmlwrapper.cpp
    src/ui/wrappers/gamedatamanagerqmlwrapper.cpp
    src/ui/wrappers/worlddataqmlwrapper.cpp
    )

find_package(Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Boost REQUIRED COMPONENTS graph)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
find_package(LibNoise REQUIRED)

# Puts the files in the qml.qrc in the QML_FILES variable
qt5_add_resources(QML_FILES qml.qrc)

add_executable(${PROJECT_NAME} src/main.cpp ${HEADER_FILES} ${CPP_FILES} ${QML_FILES})

target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick)

target_include_directories(${PROJECT_NAME} INTERFACE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::graph)

target_include_directories(${PROJECT_NAME} INTERFACE ${LIBNOISE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBNOISE_LIBRARIES})
