cmake_minimum_required(VERSION 3.8)

project(house-of-war LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC O N)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADER_FILES
        src/model/gamemodel.h
        src/utils/algo/poissondisksampling.h
        src/control/gamemanager.h
        src/model/world/cell.h
        src/model/world/worldmodel.h
        src/model/world/worldgeneration/worldbuilder.h
        src/model/world/worldgeneration/worldloader.h
        )

set(CPP_FILES
        src/model/gamemodel.cpp
        src/control/gamemanager.cpp
        src/model/world/cell.cpp
        src/model/world/worldmodel.cpp
        src/model/world/worldgeneration/worldbuilder.cpp
        src/model/world/worldgeneration/worldloader.cpp
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
