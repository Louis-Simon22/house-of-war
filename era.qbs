import qbs

Project {
    minimumQbsVersion: "1.7.1"

    property pathList header_files: [
        "src/model/gamemodel.h",
        "src/utils/utils.h",
        "src/control/gamemanager.h",
        "src/model/geography/poissondisksamplingpointsgenerator.h",
        "src/model/geography/worldbuilder.h",
        "src/model/geography/cell.h",
        "src/model/geography/worldmodel.h"
    ]

    property pathList cpp_files: [
        "src/main.cpp",
        "src/model/gamemodel.cpp",
        "src/utils/utils.cpp",
        "src/control/gamemanager.cpp",
        "src/model/geography/poissondisksamplingpointsgenerator.cpp",
        "src/model/geography/worldbuilder.cpp",
        "src/model/geography/cell.cpp",
        "src/model/geography/worldmodel.cpp"
    ]

    property pathList qml_files: ["qml.qrc"]

    CppApplication {
        Depends {
            name: "Qt.core"
        }
        Depends {
            name: "Qt.gui"
        }
        Depends {
            name: "Qt.quick"
        }
        Depends {
            name: "Qt.qml"
        }

        // Additional import path used to resolve QML modules in Qt Creator's code model
        property pathList qmlImportPaths: []

        cpp.cxxLanguageVersion: "c++11"

        cpp.defines: [// The following define makes your compiler emit warnings if you use
            // any feature of Qt which as been marked deprecated (the exact warnings
            // depend on your compiler). Please consult the documentation of the
            // deprecated API in order to know how to port your code away from it.
            "QT_DEPRECATED_WARNINGS" // You can also make your code fail to compile if you use deprecated APIs.// In order to do so, uncomment the following line.// You can also select to disable deprecated APIs only up to a certain version of Qt.
            //"QT_DISABLE_DEPRECATED_BEFORE=0x060000" // disables all the APIs deprecated before Qt 6.0.0
        ]

        files: {
            var src_files = cpp_files.concat(header_files);
            return qml_files.concat(src_files);
        }

        Group {
            // Properties for the produced executable
            fileTagsFilter: "application"
            qbs.install: true
        }
    }
}
